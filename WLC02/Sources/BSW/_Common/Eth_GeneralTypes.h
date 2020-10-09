/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Eth_GeneralTypes.h
 *        \brief  General types header for the Ethernet stack
 *
 *      \details  Holds general data types and defines provided to and used by multiple components of the Vector
 *                Ethernet stack.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  David Fessler                 visfer        Vector Informatik GmbH
 *  Martin Heiker                 visnhe        Vector Informatik GmbH 
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  00.01.00  2017-07-14  visfer  -             Initial creation based on merge of Eth_GeneralTypes.h,
 *                                              EthTrcv_GeneralTypes.hand EthSwt_GeneralTypes.h,
 *                                              adaptions for AUTOSAR compliance
 *  00.02.00  2017-10-04  visfer  -             Reorder members of Eth_TimeStampType, added Eth_CounterType and
 *                                              Eth_TxErrorCounterValuesType
 *  03.00.00  2018-11-20  visnhe  STORYC-5875   Release Impl_EthGeneralTypes of CommonAsr__Common
 *  03.00.01  2019-02-25  vismha  ESCAN00102246 Compiler error: EthSwt_GeneralTypes.h missing identifiers
 **********************************************************************************************************************/
#ifndef ETH_GENERAL_TYPES_H
# define ETH_GENERAL_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ETH modes */
# define ETH_MODE_DOWN                           (0x00u)
# define ETH_MODE_ACTIVE                         (0x01u)

/* ETH return type */
# define ETH_OK                                  (0x00u)
# define ETH_E_NOT_OK                            (0x01u)
# define ETH_E_NO_ACCESS                         (0x02u)

/* ETH RX status type */
# define ETH_RECEIVED                            (0x00u)
# define ETH_NOT_RECEIVED                        (0x01u)
# define ETH_RECEIVED_MORE_DATA_AVAILABLE        (0x02u)
# define ETH_RECEIVED_FRAMES_LOST                (0x03u)

/* ETH filter action types */
# define ETH_ADD_TO_FILTER                       (0x00u)
# define ETH_REMOVE_FROM_FILTER                  (0x01u)

/* ETH states */
# define ETH_STATE_UNINIT                        (0x00u)
# define ETH_STATE_INIT                          (0x01u)
# define ETH_STATE_ACTIVE                        (0x02u)
# define ETH_STATE_MODE_DOWN                     (0x03u)
# define ETH_STATE_MODE_ACTIVE                   (0x04u)

/* ETH MII modes */
# define ETH_MII_MODE                            (0x00u)
# define ETH_RMII_MODE                           (0x01u)
# define ETH_GMII_MODE                           (0x02u)
# define ETH_RGMII_MODE                          (0x03u)
# define ETH_SGMII_MODE                          (0x04u)

# define ETH_INVALID_FRAME_ID                    (0x00u)

# define ETH_PHYS_ADDR_LEN_BYTE                  (6u)
# define ETH_ETHER_TYPE_LEN_BYTE                 (2u)
# define ETH_HEADER_LEN_BYTE                     (14u)

/* ETH Timestamp Quality Types */
# define ETH_TIMESTAMP_VALID                     (0u)
# define ETH_TIMESTAMP_INVALID                   (1u)
# define ETH_TIMESTAMP_UNCERTAIN                 (2u)

/*! Value defining that the counter isn't supported */
# define ETH_RXTX_STATS_INV_COUNTER_VAL          (0xFFFFFFFFu)
/*! Value defining that the counter has overflown */
# define ETH_RXTX_STATS_COUNTER_OVERFLOW_VAL     (0xFFFFFFFEu)
/*! Value defining the maximum possible counter value */
# define ETH_RXTX_STATS_MAX_COUNTER_VAL          (0xFFFFFFFDu)

/* Transceiver speeds in [bit/s] */
# define ETH_TRCV_SPEED_10MBITS_IN_BITS          (10000000u)
# define ETH_TRCV_SPEED_100MBITS_IN_BITS         (100000000u)
# define ETH_TRCV_SPEED_1000MBITS_IN_BITS        (1000000000u)
# define ETH_TRCV_SPEED_DONT_CARE                (0xFFFFFFFFu)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8          Eth_ReturnType;
typedef uint8          Eth_ModeType;
typedef uint16         Eth_FrameType;
typedef uint32         Eth_DataType;
typedef uint8          Eth_RxStatusType;
typedef uint8          Eth_FilterActionType;
typedef uint16         Eth_FrameIdType;

typedef uint8          Eth_StateType;

/* ETH Physical Address Type */
typedef uint8 Eth_PhysAddrType[ETH_PHYS_ADDR_LEN_BYTE];

/*! \brief Type defining a time stamp according to AUTOSAR 4.2 */
typedef struct
{
  uint32 nanoseconds;
  uint32 seconds;
  uint16 secondsHi;
} Eth_TimeStampType;

/*! \brief Type defining the quality of a time stamp */
typedef uint8    Eth_TimestampQualityType;

/*! \brief Vector type defining the difference between time stamps */
typedef sint32   Eth_TimediffType;

/*! \brief AUTOSAR type defining the difference between time stamps */
typedef struct
{
  Eth_TimeStampType diff;
  boolean sign;
} Eth_TimeIntDiffType;

/*! \brief Type defining the drift of a clock related to another clock */
typedef float64  Eth_RateRatioType;

/*! \brief Structure holding transmission statistic counters related to the Eth controller. */
typedef struct
{
  uint32 TxNumberOfOctets;
  uint32 TxNUcastPkts;
  uint32 TxUniCastPkts;
} Eth_TxStatsType;

/*! brief Structure holding reception statistic counters related to the Eth controller. */
typedef struct
{
  uint32 RxStatsDropEvents;
  uint32 RxStatsOctets;
  uint32 RxStatsPkts;
  uint32 RxStatsBroadcastPkts;
  uint32 RxStatsMulticastPkts;
  uint32 RxStatsCrcAlignErrors;
  uint32 RxStatsUndersizePkts;
  uint32 RxStatsOversizePkts;
  uint32 RxStatsFragments;
  uint32 RxStatsJabbers;
  uint32 RxStatsCollisions;
  uint32 RxStatsPkts64Octets;
  uint32 RxStatsPkts65to127Octets;
  uint32 RxStatsPkts128to255Octets;
  uint32 RxStatsPkts256to511Octets;
  uint32 RxStatsPkts512to1023Octets;
  uint32 RxStatsPkts1024to1518Octets;
  uint32 RxUnicastFrames;
} Eth_RxStatsType;

# include "EthTrcv_GeneralTypes.h" /* PRQA S 5087 */ /* MD_Eth_General_Types_5087 */
# include "EthSwt_GeneralTypes.h" /* PRQA S 5087 */ /* MD_Eth_General_Types_5087 */

/* module specific MISRA deviations:

  MD_Eth_General_Types_5087:
    Reason:     EthTrcv_GeneralTypes.h and EthSwt_GeneralTypes.h need access to types and defines defined in
                Eth_GeneralTypes.h but AUTOSAR defines Eth_GeneralTypes.h as single entry for the Eth*_GeneralTypes.
                To be able to fulfill this use-case the includes must be done after the typedefintions in
                Eth_GeneralTypes.h so they are available for the other headers before usage.
    Risk:       None.
    Prevention: Compiler will complain when detecting any inconsitency.
*/

#endif /* ETH_GENERAL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_GeneralTypes.h
 *********************************************************************************************************************/
