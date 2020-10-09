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
/*!        \file  Nm_Cbk.h
 *        \brief  AUTOSAR NM Interface header file
 *
 *      \details  Callback header of AUTOSAR Generic Network Management Interface
 *                AUTOSAR Release 4
 *        \trace  SPEC-19592
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 * 
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the NM_CBK_x_VERSION version defines below.
 *********************************************************************************************************************/

#if !defined (NM_CBK_H)
# define NM_CBK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Nm_Cfg.h"                                                           /* Include NM Interface Configuration */
# if ( NM_MACRO_LAYER_ENABLED == STD_ON )
#  include "ComM_Nm.h"                                                               /* Include ComM callback header */
# endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Component Version Information (decimal coded) */
# define NM_CBK_MAJOR_VERSION    (12u)
# define NM_CBK_MINOR_VERSION    (0u)
# define NM_CBK_PATCH_VERSION    (0u)

/* Definition of Callback API-Ids. */
# define NM_SID_NETWORKSTARTINDICATION        (0x11u)
# define NM_SID_NETWORKMODE                   (0x12u)
# define NM_SID_PREPAREBUSSLEEPMODE           (0x13u)
# define NM_SID_BUSSLEEPMODE                  (0x14u)
# define NM_SID_PDURXINDICATION               (0x15u)
# define NM_SID_STATECHANGENOTIFICATION       (0x16u)
# define NM_SID_REMOTESLEEPINDICATION         (0x17u)
# define NM_SID_REMOTESLEEPCANCELLATION       (0x18u)
# define NM_SID_SYNCHRONIZATIONPOINT          (0x19u)
# define NM_SID_REPEATMESSAGEINDICATION       (0x1Au)
# define NM_SID_TXTIMEOUTEXCEPTION            (0x1Bu)
# define NM_SID_BUSNMSPECIFICPDURXINDICATION  (0x1Cu)
# define NM_SID_CARWAKEUPINDICATION           (0x1Du)
# define NM_SID_COORDREADYTOSLEEPINDICATION   (0x1Eu)
# define NM_SID_COORDREADYTOSLEEPCANCELLATION (0x1Fu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

# if ( NM_MACRO_LAYER_ENABLED == STD_ON )
/* \trace SPEC-4135 */
/* \trace DSGN-Nm22902 */

#  define Nm_NetworkStartIndication( nmNetworkHandle )     (ComM_Nm_NetworkStartIndication( (nmNetworkHandle) )) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Nm_NetworkMode( nmNetworkHandle )                (ComM_Nm_NetworkMode( (nmNetworkHandle) )) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  if ( NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE == STD_OFF )
#   define Nm_PrepareBusSleepMode( nmNetworkHandle )       (ComM_Nm_PrepareBusSleepMode( (nmNetworkHandle) )) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

#  define Nm_BusSleepMode( nmNetworkHandle )               (ComM_Nm_BusSleepMode( (nmNetworkHandle) )) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#   if defined ( UL_Nm_StateChangeNotification )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#    define Nm_StateChangeNotification( nmNetworkHandle, prevState, currState ) \
           UL_Nm_StateChangeNotification( nmNetworkHandle, prevState, currState )
#   else
#    define Nm_StateChangeNotification( nmNetworkHandle, prevState, currState )
#   endif
#  endif

#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#   if defined ( UL_Nm_RemoteSleepIndication )
#    define Nm_RemoteSleepIndication( nmNetworkHandle )    UL_Nm_RemoteSleepIndication( nmNetworkHandle ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define Nm_RemoteSleepIndication( nmNetworkHandle )
#   endif
#   if defined ( UL_Nm_RemoteSleepCancellation )
#    define Nm_RemoteSleepCancellation( nmNetworkHandle )  UL_Nm_RemoteSleepCancellation( nmNetworkHandle ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define Nm_RemoteSleepCancellation( nmNetworkHandle )
#   endif
#  endif

#  if ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
#   if defined ( UL_Nm_PduRxIndication )
#    define Nm_PduRxIndication( nmNetworkHandle )          UL_Nm_PduRxIndication( nmNetworkHandle ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define Nm_PduRxIndication( nmNetworkHandle )
#   endif
#  endif

#  if ( NM_REPEAT_MSG_IND_ENABLED == STD_ON )
#   if defined ( UL_Nm_RepeatMessageIndication )
#    define Nm_RepeatMessageIndication( nmNetworkHandle )  UL_Nm_RepeatMessageIndication( nmNetworkHandle ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define Nm_RepeatMessageIndication( nmNetworkHandle )
#   endif
#  endif

#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
#   if defined ( UL_Nm_TxTimeoutException )
#    define Nm_TxTimeoutException( nmNetworkHandle )       UL_Nm_TxTimeoutException( nmNetworkHandle ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define Nm_TxTimeoutException( nmNetworkHandle )
#   endif
#  endif

#  if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
#   if defined ( UL_Nm_CarWakeUpIndication )
#    define Nm_CarWakeUpIndication( nmNetworkHandle )      UL_Nm_CarWakeUpIndication( nmNetworkHandle ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define Nm_CarWakeUpIndication( nmNetworkHandle )
#   endif
#  endif

# endif /* ( NM_MACRO_LAYER_ENABLED == STD_ON ) */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# if ( NM_MACRO_LAYER_ENABLED == STD_ON )
# else

#  define NM_START_SEC_CODE
#  include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*---------------- NM Interface callback functions ----------------*/
/**********************************************************************************************************************
 *  Nm_NetworkStartIndication()
 *********************************************************************************************************************/
/*! \brief       Notification that a NM-message has been received in the Bus-Sleep Mode
 *  \details     Forward call to the ComM, invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-638
 *  \trace       SPEC-4109, SPEC-4125, SPEC-4196, SPEC-4173
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_NetworkStartIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );


/**********************************************************************************************************************
 *  Nm_NetworkMode()
 *********************************************************************************************************************/
/*! \brief       Notification that the network management has entered Network Mode.
 *  \details     Forward call to the ComM, invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF
 *               Only for different channel handles: if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-639
 *  \trace       SPEC-4109, SPEC-4125, SPEC-4157, SPEC-4163, SPEC-31367
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_NetworkMode( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );


/**********************************************************************************************************************
 *  Nm_BusSleepMode()
 *********************************************************************************************************************/
/*! \brief       Notification that the network management has entered Bus-Sleep Mode.
 *  \details     Forward call to the ComM, invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF
 *               Only for different channel handles: if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-640
 *  \trace       SPEC-4109, SPEC-4125, SPEC-4169, SPEC-4178
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_BusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );


/**********************************************************************************************************************
 *  Nm_PrepareBusSleepMode()
 *********************************************************************************************************************/
/*! \brief       Notification that the network management has entered Prepare Bus-Sleep Mode.
 *  \details     Forward call to the ComM, invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF
 *               Only for different channel handles: if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE == STD_OFF )
 *  \trace       CREQ-641
 *  \trace       SPEC-4109, SPEC-4125, SPEC-4151, SPEC-4201, SPEC-31369
 *********************************************************************************************************************/
#  if ( NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE == STD_OFF )
extern FUNC( void, NM_CODE ) Nm_PrepareBusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif



#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )

/**********************************************************************************************************************
 *  Nm_RemoteSleepIndication()
 *********************************************************************************************************************/
/*! \brief       Notification that the network management has detected that all other nodes are ready to sleep.
 *  \details     Invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF
 *               Only for different channel handles: if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
 *  \trace       CREQ-642
 *  \trace       SPEC-4109, SPEC-4253
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_RemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );


/**********************************************************************************************************************
 *  Nm_RemoteSleepCancellation()
 *********************************************************************************************************************/
/*! \brief       Notification that the network management has detected that not all
 *               other nodes are ready to sleep anymore.
 *  \details     Invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF
 *               Only for different channel handles: if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
 *  \trace       CREQ-643
 *  \trace       SPEC-4109, SPEC-4252
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_RemoteSleepCancellation( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif


/**********************************************************************************************************************
 *  Nm_SynchronizationPoint()
 *********************************************************************************************************************/
/*! \brief       Notification that this is a suitable point in time to initiate the NM coordination algorithm.
 *               Function triggers the start of the coordinated shutdown.
 *  \details     Invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
 *  \trace       CREQ-644
 *  \trace       SPEC-4109, SPEC-4147, SPEC-4162, SPEC-4219
 *********************************************************************************************************************/
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_SynchronizationPoint( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif


/*---------------- NM Interface extra callback functions ----------------*/


/**********************************************************************************************************************
 *  Nm_PduRxIndication()
 *********************************************************************************************************************/
/*! \brief       Notification that a NM message has been received.
 *  \details     Notification is optionally forwarded to an upper layer by a configurable notification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
 *  \trace       CREQ-647
 *  \trace       SPEC-4109, SPEC-4113, SPEC-4159
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
#  if ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_PduRxIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif

/**********************************************************************************************************************
 *  Nm_BusNmSpecificPduRxIndication()
 *********************************************************************************************************************/
/*! \brief       Notification that a NM message has been received by a specific BusNm on a channel.
 *  \details     Notification is optionally forwarded to an upper layer by a configurable notification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   busNmIndex            Index of the BusNm on the NM-channel
 *  \param[in]   pduInfo               Pointer to the received PDU data
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && (NM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED == STD_ON)
 *  \trace       CREQ-1093
 *  \trace       SPEC-4109
 *  \trace       DSGN-Nm23140, DSGN-Nm22902
 *********************************************************************************************************************/
#  if (NM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED == STD_ON)
extern FUNC( void, NM_CODE ) Nm_BusNmSpecificPduRxIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
#   if (NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF)
                                                              CONST( uint8, AUTOMATIC ) busNmIndex,
#   endif
                                                              CONSTP2CONST( PduInfoType, AUTOMATIC, AUTOMATIC) pduInfo );
#  endif

/**********************************************************************************************************************
 *  Nm_StateChangeNotification()
 *********************************************************************************************************************/
/*! \brief       Notification that the state of the lower layer BusNm has changed.
 *  \details     Notification is optionally forwarded to an upper layer by a configurable notification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   nmPreviousState       Previous state of the NM-channel 
 *  \param[in]   nmCurrentState        Current (new) state of the NM-channel 
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_ON
 *               Only for different channel handles: if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_OFF
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
 *  \trace       CREQ-652
 *  \trace       SPEC-4109, SPEC-4128, SPEC-4184, SPEC-19564, SPEC-31363
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
#  if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                         CONST( Nm_StateType, AUTOMATIC) nmPreviousState, 
                                                         CONST( Nm_StateType, AUTOMATIC ) nmCurrentState );
#  endif


/**********************************************************************************************************************
 *  Nm_RepeatMessageIndication()
 *********************************************************************************************************************/
/*! \brief       Service to indicate that an NM message with set Repeat Message Request Bit has been received.
 *  \details     Notification is optionally forwarded to an upper layer by a configurable notification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_REPEAT_MSG_IND_ENABLED == STD_ON )
 *  \trace       CREQ-653
 *  \trace       SPEC-4109, SPEC-4212, SPEC-4227
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
#  if ( NM_REPEAT_MSG_IND_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_RepeatMessageIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif


/**********************************************************************************************************************
 *  Nm_TxTimeoutException()
 *********************************************************************************************************************/
/*! \brief       Service to indicate that an attempt to send an NM message failed.
 *  \details     Notification is optionally forwarded to an upper layer by a configurable notification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_PASSIVE_MODE_ENABLED == STD_ON )
 *  \trace       CREQ-654
 *  \trace       SPEC-4109, SPEC-4235
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
extern FUNC( void, NM_CODE ) Nm_TxTimeoutException( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif


/**********************************************************************************************************************
 *  Nm_CarWakeUpIndication()
 *********************************************************************************************************************/
/*! \brief       This function is called by a BusNm to indicate reception of a CWU request
 *  \details     Notification is optionally forwarded to an upper layer by a configurable notification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
 *  \trace       CREQ-657
 *  \trace       SPEC-4109, SPEC-19566, SPEC-19574
 *  \trace       DSGN-Nm22902
 *********************************************************************************************************************/
#  if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_CarWakeUpIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif


#  if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )

/**********************************************************************************************************************
 *  Nm_CoordReadyToSleepIndication()
 *********************************************************************************************************************/
/*! \brief       Sets an indication, when the NM Coordinator Sleep Ready bit in the Control Bit Vector is set.
 *  \details     Invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
 *  \trace       CREQ-645
 *  \trace       SPEC-4109, SPEC-19579, SPEC-19585, SPEC-19598, SPEC-19600
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_CoordReadyToSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );


/**********************************************************************************************************************
 *  Nm_CoordReadyToSleepCancellation()
 *********************************************************************************************************************/
/*! \brief       Cancels an indication, when the NM Coordinator Sleep Ready bit in the Control Bit Vector is
 *               set back to 0.
 *  \details     Invoked by the bus specific NM
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \pre         Block global interrupts, use NM_EXCLUSIVE_AREA_1
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
 *  \trace       CREQ-646
 *  \trace       SPEC-4109, SPEC-19600
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_CoordReadyToSleepCancellation( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif

#  define NM_STOP_SEC_CODE
#  include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

# endif  /* else ( NM_MACRO_LAYER_ENABLED == STD_ON ) */

#endif  /* NM_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: Nm_Cbk.h
 *********************************************************************************************************************/
