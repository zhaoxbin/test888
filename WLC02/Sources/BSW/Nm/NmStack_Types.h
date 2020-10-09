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
/*!        \file  NmStack_Types.h
 *        \brief  AUTOSAR NM Interface header file
 *
 *      \details  Type definitions of AUTOSAR Generic Network Management Interface
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
 *  Refer to the NM_STACKTYPES_x_VERSION version defines below.
 *********************************************************************************************************************/

#if !defined (NM_STACK_TYPES_H)
# define NM_STACK_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"                                                                     /* Include standard types */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* AUTOSAR Specification Version Information (decimal coded) */
# define NM_STACKTYPES_MAJOR_VERSION   (12u)
# define NM_STACKTYPES_MINOR_VERSION   (0u)
# define NM_STACKTYPES_PATCH_VERSION   (0u)

/* Sleep Bit in the Control Bit Vector */
# define NM_COORD_BIT_SLEEP            (0x08u)
/* Inverse Sleep Bit Mask in the Control Bit Vector */
# define NM_COORD_BIT_INV_SLEEP        (0xF7u)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! States of the network management state machine */
typedef uint8 Nm_StateType;
/*! Uninitialized State */
# define NM_STATE_UNINIT                               (0x00u)
/*! Bus Sleep State */
# define NM_STATE_BUS_SLEEP                            (0x01u)
/*! Prepare Bus Sleep State */
# define NM_STATE_PREPARE_BUS_SLEEP                    (0x02u)
/*! Ready Sleep State */
# define NM_STATE_READY_SLEEP                          (0x03u)
/*! Normal Operation State */
# define NM_STATE_NORMAL_OPERATION                     (0x04u)
/*! Repeat Message State */
# define NM_STATE_REPEAT_MESSAGE                       (0x05u)
/*! Synchronized State */
# define NM_STATE_SYNCHRONIZE                          (0x06u)
/*! Offline State */
# define NM_STATE_OFFLINE                              (0x07u)
/*! Check Wake-up State */ /* \trace DSGN-Nm22898 */
# define NM_STATE_CHECK_WAKEUP                         (0x08u)
/*! Wait Start-up State */ /* \trace DSGN-Nm22898 */
# define NM_STATE_WAIT_STARTUP                         (0x09u)
/*! Wait Start-up and gateway messages already activated */
# define NM_STATE_WAIT_NETWORK_GW_MSG_ACTIVE           (0x0Au)
/*! Wait Start-up and gateway plus event triggered messages already activated */
# define NM_STATE_WAIT_NETWORK_GW_AND_EVENT_MSG_ACTIVE (0x0Bu)
/*! BusOff */
# define NM_STATE_BUS_OFF                              (0x0Cu)

/*! Number of state defines */
# define NM_STATE_NUMBER_OF_STATES                     (0x0Du)

/*! Modes of the network management state machine */
typedef uint8 Nm_ModeType;
/*! Bus-Sleep Mode */
# define NM_MODE_BUS_SLEEP                             (0x00u)
/*! Prepare Bus-Sleep Mode */
# define NM_MODE_PREPARE_BUS_SLEEP                     (0x01u)
/*! Synchronized Mode */
# define NM_MODE_SYNCHRONIZE                           (0x02u)
/*! Network Mode */
# define NM_MODE_NETWORK                               (0x03u)



/*! BusNm Type */
typedef uint8 Nm_BusNmType;
/*! CAN NM type */
# define NM_BUSNM_CANNM                                (0x00u)
/*! FR NM type */
# define NM_BUSNM_FRNM                                 (0x01u)
/*! LIN NM type */
# define NM_BUSNM_LINNM                                (0x02u)
/*! UDP NM type */
# define NM_BUSNM_UDPNM                                (0x03u)
/*! SAE J1939 NM type (address claiming) */
# define NM_BUSNM_J1939NM                              (0x04u)
/*! Generic NM type */
# define NM_BUSNM_GENERICNM                            (0x05u)
/*! NM type undefined */
# define NM_BUSNM_UNDEF                                (0xFFu)

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* NM_STACK_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: NmStack_Types.h
 *********************************************************************************************************************/
