
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsHw_Ports.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Renesas RH850

  \brief Description:  This header file contains the information for the evalboard specific port settings,
                       supported by this Brs implementation.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Manuel Rettig                 visrgm        Vector Informatik GmbH
  Sherif Elsabbahy              vissey        Vector Informatik GmbH
  Anja Unnasch                  visuna        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2016-07-05  visbwa  Initial creation, for TCM-support only
  01.01.00  2016-11-07  visrgm  Added Derivative/Group Specific Ports for Port Groups A to D
            2017-03-07  visbwa  Review according to Brs_Template 2.01.00
  01.01.01  2017-03-08  vissey  Added PIN configuration for alive LED support, added CAN pins for HSR_1502
  01.01.02  2017-03-10  visbwa  Reduced brsHw_Port_AlternativeType to 0-7, as more is not supported by platform
  01.01.03  2017-03-10  visuna  Added TCM pins for Port Group B, added alive LED support for HSR_1421
  01.01.04  2017-04-13  visivg  Added alive LED support for HSR_1382
  01.01.05  2017-04-28  visbwa  Generalized BRSHW_PORT_CONF_ETH0MDIO
  01.01.06  2017-05-05  visivg  Added alive LED support for HSR_1875
  01.01.07  2017-05-16  visbwa  Added support for BRS_EVA_BOARD_F1X_176PIN (LED+TCM)
  01.01.08  2017-05-18  visivg  Adapted LED and TCM support for F1X_144PIN, F1X_064PIN, P1XC_292PIN, F1X_176PIN,
                                P1X_144PIN, F1X_100PIN and P1X_100PIN
  01.01.09  2017-08-30  visbwa  Added BRSHW_PORT_LOGIC_HIGH and BRSHW_PORT_LOGIC_LOW, fixed Can transceiver pin setup
  01.01.10  2018-01-03  visbwa  Fixed Can0_Tx and Can0_Rx alternative functions for PORT_GROUP_D
  01.01.11  2018-01-05  visbwa  Fixed DrvLin channel port names for PORT_GROUP_D
  01.01.12  2018-02-07  vismaa  Added FBL support (BRSHW_PORT_TOGGLE_CUSTOM and  BRSHW_PORT_TOGGLE_WD)
  01.01.13  2018-04-30  vismaa  Added third CAN channel for BRSHW_PORT_GROUP_B
**********************************************************************************************************************/

#ifndef _BRSHW_PORTS_H_
#define _BRSHW_PORTS_H_

/*******************************************************************************
  Generic PORT definition types
********************************************************************************/
typedef enum
{
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTGROUP_6,
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTGROUP_9,
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTGROUP_12,
  BRSHW_PORT_PORTGROUP_13,
  BRSHW_PORT_PORTGROUP_14,
  BRSHW_PORT_PORTGROUP_15,
  BRSHW_PORT_PORTGROUP_16,
  BRSHW_PORT_PORTGROUP_17,
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTGROUP_19,
  BRSHW_PORT_PORTGROUP_20
}brsHw_Port_PortGroupType;

typedef enum
{
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_PORTNUMBER_16
}brsHw_Port_PortNumberType;

typedef enum
{
  BRSHW_PORT_ALT_0,
  BRSHW_PORT_ALT_1,
  BRSHW_PORT_ALT_2,
  BRSHW_PORT_ALT_3,
  BRSHW_PORT_ALT_4,
  BRSHW_PORT_ALT_5,
  BRSHW_PORT_ALT_6,
  BRSHW_PORT_ALT_7
}brsHw_Port_AlternativeType;

typedef enum
{
  PORT_PULL_UP_DISABLED,
  PORT_PULL_UP_ENABLED
}brsHw_Port_PullUpOption;

typedef enum
{
  PORT_DRIVE_STRENGTH_CONTROL_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_ENABLED
}brsHw_Port_PortDriveStrength;

typedef enum
{
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_OPEN_DRAIN_CONTROL_ENABLED
}brsHw_Port_PortOpenDrainControl;

typedef enum
{
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_ENABLED
}brsHw_Port_InputBufferSelect;

typedef enum
{
  PORT_PROTECTION_COMMAND_DISABLED,
  PORT_PROTECTION_COMMAND_ENABLED
}brsHw_Port_PortProtectionCommand;

typedef enum
{
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_PROTECTION_STATUS_ENABLED
}brsHw_Port_PortProtectionStatus;

typedef enum
{
  PORT_IP_CONTROL_DISABLED,
  PORT_IP_CONTROL_ENABLED
}brsHw_Port_PortIPControl;

typedef enum
{
  PORT_BIDIRECTIONAL_MODE_DISABLED,
  PORT_BIDIRECTIONAL_MODE_ENABLED
}brsHw_Port_BidirectionalMode; 

typedef struct
{
  brsHw_Port_PortGroupType   portGroup;
  brsHw_Port_PortNumberType  portNumber;
  brsHw_Port_AlternativeType portAlternative;
}brsHw_Port_PortType;

typedef struct
{
  brsHw_Port_PullUpOption           PortPullUp;
  brsHw_Port_PortDriveStrength      PortDriveStrength;
  brsHw_Port_PortOpenDrainControl   PortOpenDrain;
  brsHw_Port_InputBufferSelect      PortInputBuffer;
  brsHw_Port_PortProtectionCommand  PortProtectionCMD;
  brsHw_Port_PortProtectionStatus   PortProtectionStatus;
  brsHw_Port_PortIPControl          PortIPControl;
  brsHw_Port_BidirectionalMode      PortBidirectionalMode;
}brsHw_Port_ConfType;

#define BRSHW_PORT_LOGIC_HIGH (uint8)1
#define BRSHW_PORT_LOGIC_LOW  (uint8)0

/*******************************************************************************
  PIN configuration for TCM support
********************************************************************************/
#if defined (BRS_ENABLE_TCC_TCM_SUPPORT)
# if defined (BRS_PORT_GROUP_A)
#  if defined (BRS_EVA_BOARD_F1X_176PIN) || defined (BRS_EVA_BOARD_F1X_144PIN) || \
      defined (BRS_EVA_BOARD_F1X_064PIN) || defined (BRS_EVA_BOARD_F1X_100PIN)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType  BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};

#  else
/* 701502 */
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0};

#   if 0
/* Placeholder, not supported yet */
const brsHw_Port_PortType BRSHW_PORT_TCM_INTA_IN = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_INTB_IN = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_5};
#   endif
#  endif /*BRS_EVA_BOARD_x*/

# elif defined (BRS_PORT_GROUP_B)
#  if defined (BRS_EVA_BOARD_P1X_144PIN) || defined (BRS_EVA_BOARD_P1X_100PIN)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType  BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0};

#  else
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType  BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
#  endif /*BRS_EVA_BOARD_x*/

# elif defined (BRS_PORT_GROUP_B2)
#  if defined (BRS_EVA_BOARD_P1XC_292PIN)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType  BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0};
#  endif /*BRS_EVA_BOARD_x*/

# else
  #error "TCM-Ports for your environment not yet configured within BrsHw_Ports.h. Configure them or disable BRS_ENABLE_TCM_SUPPORT."
# endif /*BRS_PORT_GROUP_x*/
#endif /*BRS_ENABLE_TCC_TCM_SUPPORT*/

/*******************************************************************************
  PIN configuration for alive LED support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_LEDS)
# if defined (BRS_EVA_BOARD_DEFAULT)
/* Supported by all controllers of the uC family */
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_VEN001092)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_11
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_VEN001099) || defined (BRS_EVA_BOARD_MANGO)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_16,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_VEBN01283)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_VEBN01326)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_VEN001220) || defined (BRS_EVA_BOARD_VEN001243)
/*LED 8*/
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_6,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_F1X_176PIN) || defined (BRS_EVA_BOARD_F1X_144PIN) || \
       defined (BRS_EVA_BOARD_F1X_064PIN) || defined (BRS_EVA_BOARD_F1X_100PIN)
/* LED 10, CN55.1, DIGIO_0 */
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_P1XC_292PIN)
/*LED 10*/
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_6,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_HSR_715) || defined (BRS_EVA_BOARD_F1X_STARTERKIT_V2)
/*LED DBG_LED_GRN*/ /*LED 1*/
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_P1X_144PIN)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};

# elif defined (BRS_EVA_BOARD_P1X_100PIN)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_0};

# else
  #error "Your chosen EvaBoard ist not yet supported for LED support. Feel free to add your EvaBoard on top, or disable BRS LED support."
# endif /*BRS_EVA_BOARD_x*/
#endif /*BRS_ENABLE_SUPPORT_LEDS*/

/*******************************************************************************
  PIN configuration for toggle WD pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif

  #error "Please configure here the needed WD-toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_WD = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
#endif /*BRS_ENABLE_SUPPORT_WD_PIN*/

/*******************************************************************************
  PIN configuration for toggle CUSTOM pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "Please configure here the needed custom toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_CUSTOM = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};
#endif /*BRS_ENABLE_SUPPORT_CUSTOM_PIN*/

/*******************************************************************************
  ------------------------------------------------------------
  COMMUNICATION DRIVER SPECIFIC PORT SETTINGS
  ------------------------------------------------------------
********************************************************************************/
/*******************************************************************************
  GENERAL COMMUNICATION DRIVER SPECIFIC SETTINGS
********************************************************************************/
#if defined (BRS_ENABLE_LIN_SUPPORT)
const brsHw_Port_ConfType BRSHW_PORT_CONF_LIN = {
  PORT_PULL_UP_ENABLED,
  PORT_DRIVE_STRENGTH_CONTROL_DISABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_DISABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_DISABLED,
  PORT_BIDIRECTIONAL_MODE_DISABLED};
#endif /*BRS_ENABLE_LIN_SUPPORT*/

#if defined (BRS_ENABLE_ETHERNET_SUPPORT)
const brsHw_Port_ConfType BRSHW_PORT_CONF_ETH0TXD = {
  PORT_PULL_UP_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_ENABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_ENABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_DISABLED,
  PORT_BIDIRECTIONAL_MODE_DISABLED};
const brsHw_Port_ConfType BRSHW_PORT_CONF_ETH0TXEN = {
  PORT_PULL_UP_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_ENABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_ENABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_DISABLED,
  PORT_BIDIRECTIONAL_MODE_DISABLED};
const brsHw_Port_ConfType BRSHW_PORT_CONF_ETH0TXERR = {
  PORT_PULL_UP_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_ENABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_ENABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_DISABLED,
  PORT_BIDIRECTIONAL_MODE_DISABLED};
const brsHw_Port_ConfType BRSHW_PORT_CONF_ETH0MDC = {
  PORT_PULL_UP_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_ENABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_ENABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_DISABLED,
  PORT_BIDIRECTIONAL_MODE_DISABLED};
const brsHw_Port_ConfType BRSHW_PORT_CONF_ETH0MDIO = {
  PORT_PULL_UP_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_ENABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_DISABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_ENABLED,
  PORT_BIDIRECTIONAL_MODE_DISABLED};
#endif /*BRS_ENABLE_ETHERNET_SUPPORT*/

/*******************************************************************************
  SETTINGS FOR PORT GROUP A
********************************************************************************/
#if defined (BRS_PORT_GROUP_A)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (BRS_ENABLE_CAN_SUPPORT)
#  if defined (BRS_EVA_BOARD_HSR_1502)

const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN0_TRCV_EN
const brsHw_Port_PortType BRSHW_PORT_CAN0_TRCV_EN = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0};  

const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_CAN1_TRCV_EN
const brsHw_Port_PortType BRSHW_PORT_CAN1_TRCV_EN = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0};  

#  else
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_2};

const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};
#  endif /*else BRS_EVA_BOARD_HSR_1502*/

const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1};

const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};

const brsHw_Port_PortType BRSHW_PORT_CAN4_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN4_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_5};

const brsHw_Port_PortType BRSHW_PORT_CAN5_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN5_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_5};
# endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (BRS_ENABLE_LIN_SUPPORT)
#  if defined (BRS_ENABLE_LIN_CHANNEL_0)
const brsHw_Port_PortType BRSHW_PORT_LIN2_0_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_LIN2_0_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_2};
#  endif /*BRS_ENABLE_LIN_CHANNEL_0*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_1)
const brsHw_Port_PortType BRSHW_PORT_LIN2_1_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_1_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_1*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_2_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_LIN2_2_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_3};
#  endif /*BRS_ENABLE_LIN_CHANNEL_2*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_3)
const brsHw_Port_PortType BRSHW_PORT_LIN2_3_TX = {
  BRSHW_PORT_PORTGROUP_20,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_3_RX = {
  BRSHW_PORT_PORTGROUP_20,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_3*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_4)
const brsHw_Port_PortType BRSHW_PORT_LIN2_4_TX = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_4_RX = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_4*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_5)
const brsHw_Port_PortType BRSHW_PORT_LIN2_5_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_5_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_5*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_6)
const brsHw_Port_PortType BRSHW_PORT_LIN2_6_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN2_6_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_4};
#  endif /*BRS_ENABLE_LIN_CHANNEL_6*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_7)
const brsHw_Port_PortType BRSHW_PORT_LIN2_7_TX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_7_RX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};
#  endif /*BRS_ENABLE_LIN_CHANNEL_7*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_8)
const brsHw_Port_PortType BRSHW_PORT_LIN2_8_TX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_8_RX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_8*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_9)
const brsHw_Port_PortType BRSHW_PORT_LIN2_9_TX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN2_9_RX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_9*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_10)
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
#  endif /*BRS_ENABLE_LIN_CHANNEL_10*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_11)
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_TX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_RX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_2};
#  endif /*BRS_ENABLE_LIN_CHANNEL_11*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_12)
const brsHw_Port_PortType BRSHW_PORT_LIN3_2_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_2_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_11*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_12)
const brsHw_Port_PortType BRSHW_PORT_LIN3_3_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_3_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_12*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_13)
const brsHw_Port_PortType BRSHW_PORT_LIN3_4_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_4_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_13*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_14)
const brsHw_Port_PortType BRSHW_PORT_LIN3_5_TX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_5_RX = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_LIN_CHANNEL_14*/
# endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_FLX0_A_TX = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_FLX0_A_EN = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX0_A_RX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_2};

const brsHw_Port_PortType BRSHW_PORT_FLX0_B_TX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX0_B_EN = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX0_B_RX = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_6};
# endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
#  if (defined BRS_EVA_BOARD_VEBN00970)
  #define BRSHW_PORT_ETH0_RESET
const brsHw_Port_PortType BRSHW_PORT_ETH0RESET = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0};
#  endif /*BRS_EVA_BOARD_VEBN00970*/
const brsHw_Port_PortType BRSHW_PORT_ETH0TXCLK = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD0 = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD1 = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_TXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD2 = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_TXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD3 = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXEN = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_TXER
const brsHw_Port_PortType BRSHW_PORT_ETH0TXERR = {
  BRSHW_PORT_PORTGROUP_18,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_ETH0_RXCLK
const brsHw_Port_PortType BRSHW_PORT_ETH0RXCLK = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_6};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD0 = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_6};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD1 = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_6};
#define _BRSHW_PORT_ETH0_RXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD2 = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_6};
#define _BRSHW_PORT_ETH0_RXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD3 = {
  BRSHW_PORT_PORTGROUP_10,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_6};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXDV = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXERR = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_ETH0CRS = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_ETH0COL = {
  BRSHW_PORT_PORTGROUP_11,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_ETH0MDIO = {
  BRSHW_PORT_PORTGROUP_12,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_4};
#define _BRSHW_PORT_ETH0_MDC
const brsHw_Port_PortType BRSHW_PORT_ETH0MDC = {
  BRSHW_PORT_PORTGROUP_12,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
# endif /*BRS_ENABLE_ETHERNET_SUPPORT*/
#endif /*BRS_PORT_GROUP_A*/

/*******************************************************************************
  SETTINGS FOR PORT GROUP B
********************************************************************************/
#if defined (BRS_PORT_GROUP_B)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (BRS_ENABLE_CAN_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_1};
# endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (BRS_ENABLE_LIN_SUPPORT)
# if  defined (BRS_ENABLE_LIN_CHANNEL_0)
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_TX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_RX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_3};
#  endif /*BRS_ENABLE_LIN_CHANNEL_0*/
#  if  defined (BRS_ENABLE_LIN_CHANNEL_1)
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_TX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_RX = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_3};
#  endif /*BRS_ENABLE_LIN_CHANNEL_1*/
# endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_FLX0_A_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FLX0_A_EN = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FLX0_A_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FLX0_B_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FLX0_B_EN = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FLX0_B_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_5};
# endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
  #error "Port config for ETHERNET not yet implemented for Port Group B!"
# endif
#endif /*BRS_PORT_GROUP_B*/

/*******************************************************************************
  SETTINGS FOR PORT GROUP B1
********************************************************************************/
#if defined (BRS_PORT_GROUP_B1)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (BRS_ENABLE_CAN_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN0_WAKEUP = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_7};
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN1_WAKEUP = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_7};
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN2_WAKEUP = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_7};
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN3_WAKEUP = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_7};
# endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (BRS_ENABLE_LIN_SUPPORT)
#  if defined (BRS_ENABLE_LIN_CHANNEL_0)
const brsHw_Port_PortType BRSHW_PORT_LIN2_0_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN2_0_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_4};
#  endif /*BRS_ENABLE_LIN_CHANNEL_0*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_1)
const brsHw_Port_PortType BRSHW_PORT_LIN2_1_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN2_1_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_4};
#  endif /*BRS_ENABLE_LIN_CHANNEL_1*/
#  if defined (BRS_ENABLE_LIN_CHANNEL_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_2_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN2_2_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_4};
#  endif /*BRS_ENABLE_LIN_CHANNEL_2*/
# endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
  #error "Port config for FLEXRAY not yet implemented for Port Group B1!"
# endif

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
  #error "Port config for ETHERNET not yet implemented for Port Group B1!"
# endif
#endif /*BRS_PORT_GROUP_B1*/

/*******************************************************************************
  SETTINGS FOR PORT GROUP B2
********************************************************************************/
#if defined (BRS_PORT_GROUP_B2)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (BRS_ENABLE_CAN_SUPPORT)
#  if defined (BRS_EVA_BOARD_VEN001265)
 const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_3};
 const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_3};
#  else /*BRS_EVA_BOARD_VEN001265*/
 const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_3};
 const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_4};
#  endif /*else BRS_EVA_BOARD_VEN001265*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_WAKEUP = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN1_WAKEUP = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN2_WAKEUP = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_9,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_9,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_CAN3_WAKEUP = {
  BRSHW_PORT_PORTGROUP_1,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
# endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (BRS_ENABLE_LIN_SUPPORT)
#   if defined (BRS_ENABLE_LIN_CHANNEL_0)
#    if defined (BRS_EVA_BOARD_VEN001265)
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_3};
#  else
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2};
#   endif /*BRS_ENABLE_LIN_CHANNEL_0*/
#    endif /*BRS_EVA_BOARD_VEN001265*/
# if defined (BRS_ENABLE_LIN_CHANNEL_1)
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_4};
# endif /*BRS_ENABLE_LIN_CHANNEL_1*/
# if defined (BRS_ENABLE_LIN_CHANNEL_2)
const brsHw_Port_PortType BRSHW_PORT_LIN3_2_TX = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN3_2_RX = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_4};
# endif /*BRS_ENABLE_LIN_CHANNEL_2*/
# if defined (BRS_ENABLE_LIN_CHANNEL_3)
const brsHw_Port_PortType BRSHW_PORT_LIN3_3_TX = {
  BRSHW_PORT_PORTGROUP_9,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN3_3_RX = {
  BRSHW_PORT_PORTGROUP_9,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_4};
# endif /*BRS_ENABLE_LIN_CHANNEL_3*/
# endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
/*FlexRay Modul 1*/
/*FLX0 Channel A: */
const brsHw_Port_PortType BRSHW_PORT_FLX0_TX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_FLX0_EN = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_FLX0_RX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_4};
/*FLX0 Channel B: */
const brsHw_Port_PortType BRSHW_PORT_FLX0_TX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_FLX0_EN = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_FLX0_RX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_4};

/*FlexRay Modul 2 - NOT USED!*/
/*FLX1 Channel A:*/
/*const brsHw_Port_PortType BRSHW_PORT_FLX1_TX = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX1_EN = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX1_RX = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};*/
/*FLX1 Channel B:*/
/*const brsHw_Port_PortType BRSHW_PORT_FLX1_TX = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX1_EN = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_FLX1_RX = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};*/
# endif /*BRS_ENABLE_FLEXRAY_SUPPORT*/

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
  #error "Please choose if you want to use ethernet channel 0 or 1"
#  if defined (BRS_EVA_BOARD_VEN001265)
  #define BRSHW_PORT_ETH0_RESET
const brsHw_Port_PortType BRSHW_PORT_ETH0RESET = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};
#  endif

const brsHw_Port_PortType BRSHW_PORT_ETH0TXCLK = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD0 = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD1 = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_TXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD2 = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_TXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD3 = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXEN = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_TXER
const brsHw_Port_PortType BRSHW_PORT_ETH0TXERR = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_RXCLK
const brsHw_Port_PortType BRSHW_PORT_ETH0RXCLK = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD0 = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD1 = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_RXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD2 = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_RXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD3 = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXDV = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXER = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0CRS = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0COL = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0MDIO = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_MDC
const brsHw_Port_PortType BRSHW_PORT_ETH0MDC = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2};

/*Ethernet Modul 1*/
/*
const brsHw_Port_PortType BRSHW_PORT_ETH1TXCLK = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1TXD0 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1TXD1 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1TXD2 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1TXD3 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1TXEN = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1TXERR = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXCLK = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXD0 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXD1 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXD2 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXD3 = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXDV = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_ETH1RXERR = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1CRS = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1COL = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_3};
const brsHw_Port_ConfType BRSHW_PORT_CONF_ETH1MDIO = {
  PORT_PULL_UP_DISABLED,
  PORT_DRIVE_STRENGTH_CONTROL_DISABLED,
  PORT_OPEN_DRAIN_CONTROL_DISABLED,
  PORT_INPUT_BUFFER_CONTROL_DISABLED,
  PORT_PROTECTION_COMMAND_DISABLED,
  PORT_PROTECTION_STATUS_DISABLED,
  PORT_IP_CONTROL_DISABLED,
  PORT_BIDIRECTIONAL_MODE_ENABLED};
const brsHw_Port_PortType BRSHW_PORT_ETH1MDIO = {
  BRSHW_PORT_PORTGROUP_8,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH1MDC = {
  BRSHW_PORT_PORTGROUP_7,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_3};*/
# endif /*BRS_ENABLE_ETHERNET_SUPPORT*/
#endif /*BRS_PORT_GROUP_B2*/

/*******************************************************************************
  SETTINGS FOR PORT GROUP C
********************************************************************************/
#if defined (BRS_PORT_GROUP_C)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (BRS_ENABLE_CAN_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_4};
  const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_4};
# endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (BRS_ENABLE_LIN_SUPPORT)
#   if defined (BRS_ENABLE_LIN_CHANNEL_0)
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_0_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_1};
#   endif /*BRS_ENABLE_LIN_CHANNEL_0*/
#   if defined (BRS_ENABLE_LIN_CHANNEL_1)
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_1_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1};
#   endif /*BRS_ENABLE_LIN_CHANNEL_1*/
#   if defined (BRS_ENABLE_LIN_CHANNEL_2)
const brsHw_Port_PortType BRSHW_PORT_LIN3_2_TX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_LIN3_2_RX = {
  BRSHW_PORT_PORTGROUP_0,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
#   endif /*BRS_ENABLE_LIN_CHANNEL_2*/
#   if defined (BRS_ENABLE_LIN_CHANNEL_3)
const brsHw_Port_PortType BRSHW_PORT_LIN3_3_TX = {
  BRSHW_PORT_PORTGROUP_44,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN3_3_RX = {
  BRSHW_PORT_PORTGROUP_44,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
#   endif /*BRS_ENABLE_LIN_CHANNEL_3*/
# endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
  #error "Port config for FLEXRAY not yet implemented for Port Group C!"
# endif

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
/*Ethernet Channel 0:*/
const brsHw_Port_PortType BRSHW_PORT_ETH0TXCLK = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD0 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD1 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_ETH0_TXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD2 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_ETH0_TXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD3 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXEN = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1};

#  if !defined (BRS_EVA_BOARD_MANGO)
/* Do not set these pins, otherwise the Eth piggy won't work correctly! */
#define _BRSHW_PORT_ETH0_TXER
const brsHw_Port_PortType BRSHW_PORT_ETH0TXERR = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0COL = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0CRS = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXERR = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_1};
#  endif /*!BRS_EVA_BOARD_MANGO*/

#define _BRSHW_PORT_ETH0_RXCLK
const brsHw_Port_PortType BRSHW_PORT_ETH0RXCLK = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD0 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD1 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_ETH0_RXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD2 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_ETH0_RXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD3 = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_1};

/*** ACHTUNG: Hier gibt es einen Fehler im Manual: "D1x_Mango_Main_Board_Manual_Rev0.05" *** */
/*** ATTENTION: Mistake in Manual: "D1x_Mango_Main_Board_Manual_Rev0.05" ******************* */
/*** ETHERNET_0 ETNB0RXDV_0 on P42_14 instead of P42_7 ************************************* */
const brsHw_Port_PortType BRSHW_PORT_ETH0RXDV = {
  BRSHW_PORT_PORTGROUP_42,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1};

#  if defined (BRS_EVA_BOARD_MANGO)
const brsHw_Port_PortType BRSHW_PORT_ETH0MDIO = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2};
#define _BRSHW_PORT_ETH0_MDC
const brsHw_Port_PortType BRSHW_PORT_ETH0MDC = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
#  endif /*BRS_EVA_BOARD_MANGO*/

/*Alternative Port Config for Ethernet Channel 0:  */
/*
const brsHw_Port_PortType BRSHW_PORT_ETH0TXCLK = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD0 = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD1 = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD2 = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXD3 = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXEN = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0TXERR = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXCLK = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD0 = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD1 = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD2 = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXD3 = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXDV = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0RXERR = {
  BRSHW_PORT_PORTGROUP_47,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0COL = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2};
const brsHw_Port_PortType BRSHW_PORT_ETH0CRS = {
  BRSHW_PORT_PORTGROUP_46,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_2};*/
# endif /*BRS_ENABLE_ETHERNET_SUPPORT*/
#endif /*BRS_PORT_GROUP_C*/

/*******************************************************************************
  SETTINGS FOR PORT GROUP D
********************************************************************************/
#if defined (BRS_PORT_GROUP_D)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (BRS_ENABLE_CAN_SUPPORT)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN0_WAKEUP = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_7};
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN1_WAKEUP = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_7};
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_3,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN2_WAKEUP = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_7};
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_4,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_CAN3_WAKEUP = {
  BRSHW_PORT_PORTGROUP_2,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_7};
# endif /*BRS_ENABLE_CAN_SUPPORT*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (BRS_ENABLE_LIN_SUPPORT)
#   if defined (BRS_ENABLE_LIN_CHANNEL_0)
const brsHw_Port_PortType BRSHW_PORT_LIN2_8_TX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_LIN2_8_RX = {
  BRSHW_PORT_PORTGROUP_5,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_4};
#   endif /*BRS_ENABLE_LIN_CHANNEL_0*/
# endif /*BRS_ENABLE_LIN_SUPPORT*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (BRS_ENABLE_FLEXRAY_SUPPORT)
  #error "Port config for FLEXRAY not yet implemented for Port Group D!"
# endif

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (BRS_ENABLE_ETHERNET_SUPPORT)
  #error "Port config for ETHERNET not yet implemented for Port Group D!"
# endif
#endif /*BRS_PORT_GROUP_D*/

#endif /*_BRSHW_PORTS_H_*/
