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
/*!        \file  CanTp_Priv.h
 *        \brief  CanTp internal definitions
 *
 *      \details  CanTp internal constants, macros, types and consistency checks
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
#if !defined (CANTP_PRIV_H)
#define CANTP_PRIV_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* --- Protocol Definitions ---------------------------------------------------------------------------------------- */
/* protocol information frame types */
#define CANTP_PCI_TYPE_SF                        (0x00u)
#define CANTP_PCI_TYPE_FF                        (0x10u)
#define CANTP_PCI_TYPE_CF                        (0x20u)
#define CANTP_PCI_TYPE_FC                        (0x30u)
#define CANTP_PCI_TYPE_INVALID                   (0xFFu)

/* protocol information bit masks */
#define CANTP_PCI_TYPE_MASK                      (0xF0u)
#define CANTP_PCI_SN_MASK                        (0x0Fu)

/* protocol information lengths */
#define CANTP_PCI_LENGTH_SF                      1u
#define CANTP_PCI_LENGTH_FF                      2u
#define CANTP_PCI_LENGTH_CF                      1u
#define CANTP_PCI_LENGTH_FC                      3u
#define CANTP_PCI_LENGTH_LSF                     2u
#define CANTP_PCI_LENGTH_LFF                     6u

/* common length values */
#define CANTP_CAN20_FRAME_LENGTH                 8u         /* CAN 2.0 frame length                                  */
#define CANTP_FF_DL_12BIT                        4095u      /* max message length for FF with 12Bit DL               */
#define CANTP_FF_DL_16BIT                        65535u     /* max message length for FF with PduLengthType = uint16 */

/* bit masks for frame parsing */
#define CANTP_MASK_SF_LENGTH                     (0x0Fu)
#define CANTP_MASK_FF_LENGTH                     (0x0Fu)
#define CANTP_MASK_FRAMETYPE                     (0xF0u)
#define CANTP_MASK_FS                            (0x0Fu)

/* flow status codes */
#define CANTP_FLOWSTATUS_CTS                     (0x00u)
#define CANTP_FLOWSTATUS_WT                      (0x01u)
#define CANTP_FLOWSTATUS_OVFL                    (0x02u)

/* STmin values */
#define CANTP_STMIN_MILLISEC_MAX                 (0x7Fu)
#define CANTP_STMIN_MICROSEC_MIN                 (0xF1u)
#define CANTP_STMIN_MICROSEC_MAX                 (0xF9u)

/* sequence number handling */
#define CANTP_SN_FIRST_CF                        (0x01u)   /* SN of first CF */

/* Application notification state */
#define CANTP_APPL_NOT_INFORMED                  (0x00u)
#define CANTP_APPL_INFORMED                      (0x01u)

/* frame data handling */
#define CANTP_FRAME_OFFSET_FC_BS                 1u         /* block size is stored in FC byte 1          */
#define CANTP_FRAME_OFFSET_FC_STMIN              2u         /* separation time is stored in FC byte 2     */
#if (CANTP_CAN20_PADDING_ACTIVE == STD_OFF)
# define CANTP_FRAME_FC_MAX_LENGTH               4u         /* TA + FS + BS + STMIN = 4 byte              */
#else
# define CANTP_FRAME_FC_MAX_LENGTH               8u         /* TA + FS + BS + STMIN + padding = 8 byte    */
#endif


/* --- Helper Switches --------------------------------------------------------------------------------------------- */
/* handling of reserved STmin */
#if ((CANTP_IGNORE_FC_WITH_RES_STMIN == STD_ON) || (CANTP_REJECT_FC_WITH_RES_STMIN == STD_ON))                         /* COV_CANTP_EXCLUDED_FEATURES TF xf tf */
# define CANTP_MODIFIED_RES_STMIN_HANDLING       STD_ON                  /* reserved STmin is either ignored or terminates the reception */
#else
# define CANTP_MODIFIED_RES_STMIN_HANDLING       STD_OFF                 /* reserved STmin is accepted an interpreted as 127ms */
#endif

/* padding support */
#if ((CANTP_CAN20_PADDING_ACTIVE == STD_ON) || \
     (CANTP_SUPPORT_CANFD        == STD_ON))
/* padding for CAN2.0 only required when activated; for CAN-FD it is always required */
# define CANTP_PADDING_SUPPORT_REQUIRED          STD_ON
#else
# define CANTP_PADDING_SUPPORT_REQUIRED          STD_OFF
#endif


/* --- SDU Count Specific Optimization ----------------------------------------------------------------------------- */
#define CANTP_OPT_ZERO_SDU       0         /* no Rx/Tx N-SDU configured */
#define CANTP_OPT_SINGLE_SDU     1         /* only one Rx/Tx N-SDU configured */
#define CANTP_OPT_MULTI_SDU      2         /* multiple Rx/Tx N-SDUs configured and/or optimization is disabled */

#if ((CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_PRECOMPILE) && (CANTP_POSTBUILD_VARIANT_SUPPORT == STD_OFF))
# if (CANTP_NUM_RX_SDUS == 0)                                                                                          /* COV_CANTP_ROBUSTNESS_CASE XF */
#  define CANTP_RX_OPTIMIZATION                  CANTP_OPT_ZERO_SDU       /* Pre-Compile without any RxSdu */
# else
#  if (CANTP_NUM_RX_SDUS == 1)
#   define CANTP_RX_OPTIMIZATION                 CANTP_OPT_SINGLE_SDU     /* Pre-Compile with one RxSdu */
#  else
#   define CANTP_RX_OPTIMIZATION                 CANTP_OPT_MULTI_SDU      /* Pre-Compile with multiple RxSdus */
#  endif
# endif
# if (CANTP_NUM_TX_SDUS == 0)                                                                                          /* COV_CANTP_ROBUSTNESS_CASE XF */
#  define CANTP_TX_OPTIMIZATION                  CANTP_OPT_ZERO_SDU       /* Pre-Compile without any TxSdu */
# else
#  if (CANTP_NUM_TX_SDUS == 1)
#   define CANTP_TX_OPTIMIZATION                 CANTP_OPT_SINGLE_SDU     /* Pre-Compile with one TxSdu */
#  else
#   define CANTP_TX_OPTIMIZATION                 CANTP_OPT_MULTI_SDU      /* Pre-Compile with multiple TxSdus */
#  endif
# endif
#else
# define CANTP_RX_OPTIMIZATION                   CANTP_OPT_MULTI_SDU      /* PostBuild Loadable or PostBuild Selectable */
# define CANTP_TX_OPTIMIZATION                   CANTP_OPT_MULTI_SDU      /* PostBuild Loadable or PostBuild Selectable */
#endif


/* --- Constant Parameter Checking --------------------------------------------------------------------------------- */
/* If a struct element in a config table is optimized away, any if-statements in code which access this parameter
 * is obsolete as the conditional expression will be invariant.
 * Thereto, for each affected parameter, the following helper switches have been defined:
 *   CANTP_X_CHECK_Y   STD_ON:  parameter is variable, if-statement is needed
 *                     STD_OFF: parameter is constant, if-statement is obsolete
 *   CANTP_X_HAS_Y     STD_ON:  one of the possible values may occur; the respective if/else branch is required
 *                     STD_OFF: one of the possible values can't occur; the respective if/else branch is obsolete
 */

/* ChannelMode */
/* ----------- */
/* half duplex is only applicable if an opposite direction exist; otherwise, treat all connections as full duplex */
#if ((CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFRXSDUCFG == STD_ON) && (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU))      /* COV_CANTP_ROBUSTNESS_CASE TF tf tx */
# define CANTP_RX_HAS_HALF_DUPLEX                STD_ON
#else
# define CANTP_RX_HAS_HALF_DUPLEX                STD_OFF
#endif
#if ((CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG == STD_ON) || (CANTP_TX_OPTIMIZATION == CANTP_OPT_ZERO_SDU))      /* COV_CANTP_ROBUSTNESS_CASE TF tf xf */
# define CANTP_RX_HAS_FULL_DUPLEX                STD_ON
#else
# define CANTP_RX_HAS_FULL_DUPLEX                STD_OFF
#endif
#if ((CANTP_RX_HAS_HALF_DUPLEX == STD_ON) && (CANTP_RX_HAS_FULL_DUPLEX == STD_ON))
# define CANTP_RX_CHECK_HALF_DUPLEX              STD_ON
#else
# define CANTP_RX_CHECK_HALF_DUPLEX              STD_OFF
#endif

#if ((CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFTXSDUCFG == STD_ON) && (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU))      /* COV_CANTP_ROBUSTNESS_CASE TF tf tx */
# define CANTP_TX_HAS_HALF_DUPLEX                STD_ON
#else
# define CANTP_TX_HAS_HALF_DUPLEX                STD_OFF
#endif
#if ((CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG == STD_ON) || (CANTP_RX_OPTIMIZATION == CANTP_OPT_ZERO_SDU))      /* COV_CANTP_ROBUSTNESS_CASE TF tf xf */
# define CANTP_TX_HAS_FULL_DUPLEX                STD_ON
#else
# define CANTP_TX_HAS_FULL_DUPLEX                STD_OFF
#endif
#if ((CANTP_TX_HAS_HALF_DUPLEX == STD_ON) && (CANTP_TX_HAS_FULL_DUPLEX == STD_ON))
# define CANTP_TX_CHECK_HALF_DUPLEX              STD_ON
#else
# define CANTP_TX_CHECK_HALF_DUPLEX              STD_OFF
#endif

/* TA-Type */
/* ------- */
/* For TA-Type it is assumed that always a physical connection is present, so checking the TA-Type is only required */
/* if also a functional connection is configured. For the unusual case that there are only functional connections,  */
/* the compiler warning for invariant condition is accepted.                                                        */
#define CANTP_RX_HAS_TATYPE_FUNCTIONAL           CANTP_EXISTS_FUNCTIONAL_RXTATYPEOFRXSDUCFG
#define CANTP_TX_HAS_TATYPE_FUNCTIONAL           CANTP_EXISTS_FUNCTIONAL_TXTATYPEOFTXSDUCFG

/* CanType */
/* ------- */
/* CAN-FD can be activated by global switch; CAN2.0 is always possible */
#if ((CANTP_EXISTS_CANFD_CANTYPEOFRXSDUCFG == STD_ON) && (CANTP_SUPPORT_CANFD == STD_ON))
# define CANTP_RX_HAS_CANFD                      STD_ON
#else
# define CANTP_RX_HAS_CANFD                      STD_OFF
#endif
#define CANTP_RX_HAS_CAN20                       CANTP_EXISTS_CAN20_CANTYPEOFRXSDUCFG
#if ((CANTP_RX_HAS_CANFD == STD_ON) && (CANTP_RX_HAS_CAN20 == STD_ON))
# define CANTP_RX_CHECK_CANTYPE                  STD_ON
#else
# define CANTP_RX_CHECK_CANTYPE                  STD_OFF
#endif

#if ((CANTP_EXISTS_CANFD_CANTYPEOFTXSDUCFG == STD_ON) && (CANTP_SUPPORT_CANFD == STD_ON))
# define CANTP_TX_HAS_CANFD                      STD_ON
#else
# define CANTP_TX_HAS_CANFD                      STD_OFF
#endif
#define CANTP_TX_HAS_CAN20                       CANTP_EXISTS_CAN20_CANTYPEOFTXSDUCFG
#if ((CANTP_TX_HAS_CANFD == STD_ON) && (CANTP_TX_HAS_CAN20 == STD_ON))
# define CANTP_TX_CHECK_CANTYPE                  STD_ON
#else
# define CANTP_TX_CHECK_CANTYPE                  STD_OFF
#endif

/* Addressing Format */
/* ----------------- */
/* The global pre-compile switches limit the available addressing formats - even in post-build configurations */
/* In pre-compile configurations, the availability may also be limited by ComStackLib specific optimizations  */
/* --- Rx addressing format usage --- */
#if ((CANTP_EXISTS_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG == STD_ON) && (CANTP_STANDARD_ADDRESSING == STD_ON))
# define CANTP_RX_HAS_STANDARD_ADDRESSING        STD_ON    /* Rx standard addressing format active and used */
#else
# define CANTP_RX_HAS_STANDARD_ADDRESSING        STD_OFF   /* Rx standard addressing format not needed */
#endif
#if ((CANTP_EXISTS_EXTENDED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG == STD_ON) && (CANTP_EXTENDED_ADDRESSING == STD_ON))
# define CANTP_RX_HAS_EXTENDED_ADDRESSING        STD_ON    /* Rx extended Addressing active and used */
#else
# define CANTP_RX_HAS_EXTENDED_ADDRESSING        STD_OFF   /* Rx extended addressing format not needed */
#endif
#if ((CANTP_EXISTS_MIXED11_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG  == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))
# define CANTP_RX_HAS_MIXED11_ADDRESSING         STD_ON    /* Rx mixed11 addressing format active and used */
#else
# define CANTP_RX_HAS_MIXED11_ADDRESSING         STD_OFF   /* Rx mixed11 addressing format not needed */
#endif
#if ((CANTP_EXISTS_MIXED29_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG  == STD_ON) && (CANTP_MIXED29_ADDRESSING == STD_ON))
# define CANTP_RX_HAS_MIXED29_ADDRESSING         STD_ON    /* Rx mixed29 addressing format active and used */
#else
# define CANTP_RX_HAS_MIXED29_ADDRESSING         STD_OFF   /* Rx mixed29 addressing format not needed */
#endif
#if ((CANTP_EXISTS_NORMALFIXED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG  == STD_ON) && (CANTP_NORMALFIXED_ADDRESSING == STD_ON))
# define CANTP_RX_HAS_NORMALFIXED_ADDRESSING     STD_ON    /* Rx normal fixed addressing format active and used */
#else
# define CANTP_RX_HAS_NORMALFIXED_ADDRESSING     STD_OFF   /* Rx normal fixed addressing format not needed */
#endif
#if ( ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON))     || \
      ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)  && (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON)) )
# define CANTP_RX_CHECK_ADDRESSING_FORMAT         STD_ON   /* multiple Rx addressing formats are active and used */
#else
# define CANTP_RX_CHECK_ADDRESSING_FORMAT         STD_OFF  /* only one Rx addressing format is needed */
#endif

/* --- Tx addressing format usage --- */
#if ((CANTP_EXISTS_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG == STD_ON) && (CANTP_STANDARD_ADDRESSING == STD_ON))
# define CANTP_TX_HAS_STANDARD_ADDRESSING        STD_ON    /* Tx standard addressing format active and used */
#else
# define CANTP_TX_HAS_STANDARD_ADDRESSING        STD_OFF   /* Tx standard addressing format not needed */
#endif
#if ((CANTP_EXISTS_EXTENDED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG == STD_ON) && (CANTP_EXTENDED_ADDRESSING == STD_ON))
# define CANTP_TX_HAS_EXTENDED_ADDRESSING        STD_ON    /* Tx extended addressing format active and used */
#else
# define CANTP_TX_HAS_EXTENDED_ADDRESSING        STD_OFF   /* Tx extended addressing format not needed */
#endif
#if ((CANTP_EXISTS_MIXED11_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG  == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))
# define CANTP_TX_HAS_MIXED11_ADDRESSING         STD_ON    /* Tx mixed11 addressing format active and used */
#else
# define CANTP_TX_HAS_MIXED11_ADDRESSING         STD_OFF   /* Tx mixed11 addressing format not needed */
#endif
#if ((CANTP_EXISTS_MIXED29_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG  == STD_ON) && (CANTP_MIXED29_ADDRESSING == STD_ON))
# define CANTP_TX_HAS_MIXED29_ADDRESSING         STD_ON    /* Tx mixed29 addressing format active and used */
#else
# define CANTP_TX_HAS_MIXED29_ADDRESSING         STD_OFF   /* Tx mixed29 addressing format not needed */
#endif
#if ((CANTP_EXISTS_NORMALFIXED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG  == STD_ON) && (CANTP_NORMALFIXED_ADDRESSING == STD_ON))
# define CANTP_TX_HAS_NORMALFIXED_ADDRESSING     STD_ON    /* Tx normal fixed addressing format active and used */
#else
# define CANTP_TX_HAS_NORMALFIXED_ADDRESSING     STD_OFF   /* Tx normal fixed addressing format not needed */
#endif
#if ( ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON))     || \
      ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))      || \
      ((CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON)  && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))  || \
      ((CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)  && (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON)) )
# define CANTP_TX_CHECK_ADDRESSING_FORMAT        STD_ON   /* multiple Tx addressing formats are active and used */
#else
# define CANTP_TX_CHECK_ADDRESSING_FORMAT        STD_OFF  /* only one Tx addressing format is needed */
#endif

/* --- direction independent addressing format usage --- */
#if ((CANTP_RX_CHECK_ADDRESSING_FORMAT == STD_ON) || (CANTP_TX_CHECK_ADDRESSING_FORMAT == STD_ON))
# define CANTP_SUPPORT_MULTIPLE_ADDRESSING       STD_ON   /* multiple addressing formats are active and used */
#else
# define CANTP_SUPPORT_MULTIPLE_ADDRESSING       STD_OFF  /* only one addressing format is needed */
#endif
#if ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) || (CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON))
# define CANTP_SUPPORT_STANDARD_ADDRESSING       STD_ON    /* standard addressing format active and used */
#else
# define CANTP_SUPPORT_STANDARD_ADDRESSING       STD_OFF   /* standard addressing format not needed */
#endif
#if ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON))
# define CANTP_SUPPORT_EXTENDED_ADDRESSING       STD_ON    /* extended addressing format active and used */
#else
# define CANTP_SUPPORT_EXTENDED_ADDRESSING       STD_OFF   /* extended addressing format not needed */
#endif
#if ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))
# define CANTP_SUPPORT_MIXED11_ADDRESSING       STD_ON    /* mixed11 addressing format active and used */
#else
# define CANTP_SUPPORT_MIXED11_ADDRESSING       STD_OFF   /* mixed11 addressing format not needed */
#endif
#if ((CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))
# define CANTP_SUPPORT_MIXED29_ADDRESSING       STD_ON    /* mixed29 addressing format active and used */
#else
# define CANTP_SUPPORT_MIXED29_ADDRESSING       STD_OFF   /* mixed29 addressing format not needed */
#endif
#if ((CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))
# define CANTP_SUPPORT_NORMALFIXED_ADDRESSING   STD_ON    /* normal fixed addressing format active and used */
#else
# define CANTP_SUPPORT_NORMALFIXED_ADDRESSING   STD_OFF   /* normal fixed addressing format not needed */
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 MACROS */ /* MD_MSR_FctLikeMacro */

/* --- Configuration Array Sizes ----------------------------------------------------------------------------------- */
#define CanTp_Cfg_GetNumRxChannels()                   ((PduIdType)(CanTp_GetSizeOfRxState()))  /* returns: Number of Rx Channels */
#define CanTp_Cfg_GetNumRxHdls()                       ((PduIdType)(CanTp_GetSizeOfRxSduCfg()))  /* returns: Number of Rx Handle Ids */
#define CanTp_Cfg_GetNumRxPdus()                       ((PduIdType)(CanTp_GetSizeOfRxPduMap()))  /* returns: Number of RxPdus */
#if defined (CanTp_GetSizeOfRxSduSnv2Hdl)                                                                              /* COV_CANTP_ROBUSTNESS_CASE TX */
# define CanTp_Cfg_GetNumRxSduIds()                    ((PduIdType)(CanTp_GetSizeOfRxSduSnv2Hdl()))  /* returns: Number of RxSdus */
#else
# define CanTp_Cfg_GetNumRxSduIds()                    ((PduIdType)0)  /* returns: Number of RxSdus */
#endif

#define CanTp_Cfg_GetNumTxChannels()                   ((PduIdType)(CanTp_GetSizeOfTxState()))  /* returns: Number of Tx Channels */
#define CanTp_Cfg_GetNumTxConfPdus()                   ((PduIdType)(CanTp_GetSizeOfTxSemaphores()))  /* returns: Number of Tx Confirmation Pdus */
#define CanTp_Cfg_GetNumTxHdls()                       ((PduIdType)(CanTp_GetSizeOfTxSduCfg()))  /* returns: Number of Tx Handle Ids */
#if defined (CanTp_GetSizeOfTxSduSnv2Hdl)                                                                              /* COV_CANTP_ROBUSTNESS_CASE TX */
# define CanTp_Cfg_GetNumTxSduIds()                    ((PduIdType)(CanTp_GetSizeOfTxSduSnv2Hdl()))  /* returns: Number of TxSdus */
#else
# define CanTp_Cfg_GetNumTxSduIds()                    ((PduIdType)0)  /* returns: Number of RxSdus */
#endif


/* --- Configuration Access Interface ------------------------------------------------------------------------------ */
#define CanTp_Cfg_GetAddressingTypeByRxPdu(RxPduId)    ((CanTp_AddressingFormatType)(CanTp_GetAddressingFormatOfRxPduMap((RxPduId))))  /* returns: AddressingFormat of RxPduMap */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_Cfg_IsGenericConnectionByRxPdu(RxPduId)  ((CanTp_IsGenericConnectionOfRxPduMap((RxPduId))))  /* returns: GenericConnection */
#define CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId) ((uint8)(CanTp_GetPduMetadataLengthOfRxPduMap((RxPduId))))  /* returns: PduMetadataLength */
#define CanTp_Cfg_GetTaskCycle()                       ((CANTP_TASK_CYCLE))  /* returns: CANTP_TASK_CYCLE */
#define CanTp_RxCfg_GetAddressingFormat(Index)         ((CanTp_GetRxAddressingFormatOfRxSduCfg((Index))))  /* returns: RxAddressingFormat */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetBS(Index)                       ((uint8)(CanTp_GetBlockSizeOfRxSduCfg((Index))))  /* returns: BlockSize */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetLoLayerTxFcPduId(Index)         ((PduIdType)(CanTp_GetLoLayerTxFcPduIdOfRxSduCfg((Index))))  /* returns: LoLayerTxFcPduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetCanType(Index)                  ((CanTp_GetCanTypeOfRxSduCfg((Index))))  /* returns: CanType */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetChannelMode(Index)              ((CanTp_GetChannelModeOfRxSduCfg((Index))))  /* returns: ChannelMode */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetLoLayerIdx(Index)               ((uint8)(CanTp_GetLoLayerFctsIdxOfRxSduCfg((Index))))  /* returns: LoLayerFctsIdx */
#define CanTp_RxCfg_GetMaxPayload(Index)               ((uint8)(CanTp_GetRxMaxPayloadLengthOfRxSduCfg((Index))))  /* returns: RxMaxPayloadLength */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetNAr(Index)                      ((uint16)(CanTp_GetNArOfRxSduCfg((Index))))  /* returns: NAr */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetNBr(Index)                      ((uint16)(CanTp_GetNBrOfRxSduCfg((Index))))  /* returns: NBr */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetNCr(Index)                      ((uint16)(CanTp_GetNCrOfRxSduCfg((Index))))  /* returns: NCr */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_HasPaddingActivation(Index)        ((CanTp_IsRxPaddingActivationOfRxSduCfg((Index))))  /* returns: RxPaddingActivation */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetPduRRxSduId(Index)              ((PduIdType)(CanTp_GetPduRRxSduIdOfRxSduCfg((Index))))  /* returns: PduRRxSduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetRxAddress(Index)                ((uint8)(CanTp_GetRxAddressOfRxSduCfg((Index))))  /* returns: RxAddress */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetRxPduId(Index)                  ((PduIdType)(CanTp_GetRxPduIdOfRxSduCfg((Index))))  /* returns: RxPduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetSTmin(Index)                    ((uint8)(CanTp_GetSTminOfRxSduCfg((Index))))  /* returns: STmin */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetSduHdlBySNV(SymbolNameValue)    ((PduIdType)(CanTp_GetRxSduCfgIdxOfRxSduSnv2Hdl((SymbolNameValue))))  /* returns: RxSduHdl */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetTAType(Index)                   ((CanTp_GetRxTaTypeOfRxSduCfg((Index))))  /* returns: RxTaType */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetTxFcAddress(Index)              ((uint8)(CanTp_GetTxFcAddressOfRxSduCfg((Index))))  /* returns: TxFcAddress */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetTxFcConfPduId(Index)            ((PduIdType)(CanTp_GetTxFcPduConfirmationPduIdOfRxSduCfg((Index))))  /* returns: TxFcPduConfirmationPduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetTxSduHdl(Index)                 ((PduIdType)(CanTp_GetTxSduCfgIdxOfRxSduCfg((Index))))  /* returns: TxSduHdl */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_GetWFTmax(Index)                   ((uint16)(CanTp_GetRxWftMaxOfRxSduCfg((Index))))  /* returns: RxWftMax */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_RxCfg_PassSduMetadata(Index)             ((CanTp_IsPassSduMetadataOfRxSduCfg((Index))))  /* returns: PassSduMetadata */
#define CanTp_RxCfg_IsGenericConnection(Index)         ((CanTp_IsGenericConnectionOfRxSduCfg((Index))))  /* returns: GenericConnection */
#define CanTp_TxCfg_GetAddressingFormat(Index)         ((CanTp_GetTxAddressingFormatOfTxSduCfg((Index))))  /* returns: TxAddressingFormat */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetLoLayerTxPduId(Index)           ((PduIdType)(CanTp_GetLoLayerTxPduIdOfTxSduCfg((Index))))  /* returns: LoLayerTxPduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetCanType(Index)                  ((CanTp_GetCanTypeOfTxSduCfg((Index))))  /* returns: CanType */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetChannelMode(Index)              ((CanTp_GetChannelModeOfTxSduCfg((Index))))  /* returns: ChannelMode */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetLoLayerIdx(Index)               ((uint8)(CanTp_GetLoLayerFctsIdxOfTxSduCfg((Index))))  /* returns: LoLayerFctsIdx */
#define CanTp_TxCfg_GetMaxPayload(Index)               ((uint8)(CanTp_GetTxMaxPayloadLengthOfTxSduCfg((Index))))  /* returns: TxMaxPayloadLength */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetNAs(Index)                      ((uint16)(CanTp_GetNAsOfTxSduCfg((Index))))  /* returns: NAs */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetNBs(Index)                      ((uint16)(CanTp_GetNBsOfTxSduCfg((Index))))  /* returns: NBs */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetNCs(Index)                      ((uint16)(CanTp_GetNCsOfTxSduCfg((Index))))  /* returns: NCs */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_HasPaddingActivation(Index)        ((CanTp_IsTxPaddingActivationOfTxSduCfg((Index))))  /* returns: TxPaddingActivation */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetPduRTxSduId(Index)              ((PduIdType)(CanTp_GetPduRTxSduIdOfTxSduCfg((Index))))  /* returns: PduRTxSduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetRxFcAddress(Index)              ((uint8)(CanTp_GetRxFcAddressOfTxSduCfg((Index))))  /* returns: RxFcAddress */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetRxFcPduId(Index)                ((PduIdType)(CanTp_GetRxFcPduIdOfTxSduCfg((Index))))  /* returns: RxFcPduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetRxSduHdl(Index)                 ((PduIdType)(CanTp_GetRxSduCfgIdxOfTxSduCfg((Index))))  /* returns: RxSduHdl */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetSduHdlBySNV(SymbolNameValue)    ((PduIdType)(CanTp_GetTxSduCfgIdxOfTxSduSnv2Hdl((SymbolNameValue))))  /* returns: TxSduHdl */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetTAType(Index)                   ((CanTp_GetTxTaTypeOfTxSduCfg((Index))))  /* returns: TxTaType */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetTxAddress(Index)                ((uint8)(CanTp_GetTxAddressOfTxSduCfg((Index))))  /* returns: TxAddress */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_HasTxCancel(Index)                 ((CanTp_IsTransmitCancellationOfTxSduCfg((Index))))  /* returns: TransmitCancellation */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetTxConfPduId(Index)              ((PduIdType)(CanTp_GetTxPduConfirmationPduIdOfTxSduCfg((Index))))  /* returns: TxNPduConfirmationPduId */ /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxCfg_GetSduMetadataLength(Index)        ((uint8)(CanTp_GetSduMetadataLengthOfTxSduCfg((Index))))  /* returns: SduMetadataLength */


/* --- Addressing Offset Calculation ------------------------------------------------------------------------------- */
#if (CANTP_RX_CHECK_ADDRESSING_FORMAT == STD_ON)
   /* multiple addressing formats are allowed; addressing offset can be variable */
# define CanTp_RxGetAdrOffset(RxHdl)             (((CanTp_RxCfg_GetAddressingFormat((RxHdl)) == CANTP_ADDRESS_FORMAT_STANDARD)   || \
                                                   (CanTp_RxCfg_GetAddressingFormat((RxHdl)) == CANTP_ADDRESS_FORMAT_NORMALFIXED)  ) ? ((uint8)0) : ((uint8)1))
#else
# if ((CANTP_RX_HAS_STANDARD_ADDRESSING == STD_ON) || (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON))
   /* only standard or normal fixed addressing is used */
#  define CanTp_RxGetAdrOffset(RxHdl)            (uint8)0
# else
   /* only extended, mixed11 or mixed29 addressing is used */
#  define CanTp_RxGetAdrOffset(RxHdl)            (uint8)1
# endif
#endif /* CANTP_RX_CHECK_ADDRESSING_FORMAT  */

#if (CANTP_TX_CHECK_ADDRESSING_FORMAT == STD_ON)
   /* multiple addressing formats are allowed; addressing offset can be variable */
# define CanTp_TxGetAdrOffset(TxHdl)             (((CanTp_TxCfg_GetAddressingFormat((TxHdl)) == CANTP_ADDRESS_FORMAT_STANDARD)   || \
                                                   (CanTp_TxCfg_GetAddressingFormat((TxHdl)) == CANTP_ADDRESS_FORMAT_NORMALFIXED)  ) ? ((uint8)0) : ((uint8)1))
#else
# if ((CANTP_TX_HAS_STANDARD_ADDRESSING == STD_ON) || (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON))
   /* only standard or normal fixed addressing is used */
#  define CanTp_TxGetAdrOffset(TxHdl)            (uint8)0
# else
   /* only extended, mixed11 or mixed 29 addressing is used */
#  define CanTp_TxGetAdrOffset(TxHdl)            (uint8)1
# endif
#endif /* CANTP_MULTIPLE_ADDRESSING  */


/* --- Max Payload Lengths ----------------------------------------------------------------------------------------- */
/* Standard single frames are only possible for 8 byte DLC, so the max payload does not depend on the configured PduLength */
/* The max payload length of all other frames is based on the configured PDU length */
#define CanTp_RxCfg_GetMaxPayloadSF(RxHdl)      ((uint8)(CANTP_CAN20_FRAME_LENGTH - (CanTp_RxGetAdrOffset((RxHdl)) + CANTP_PCI_LENGTH_SF)))
#define CanTp_RxCfg_GetMaxPayloadLSF(RxSduHdl)  ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl)) - 1u)) /* 1 byte less payload than a CF         */
#define CanTp_RxCfg_GetMaxPayloadFF(RxSduHdl)   ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl)) - 1u)) /* 1 byte less payload than a CF         */
#define CanTp_RxCfg_GetMaxPayloadLFF(RxSduHdl)  ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl)) - 5u)) /* 5 byte less payload than a CF         */
#define CanTp_RxCfg_GetMaxPayloadCF(RxSduHdl)   ((uint8)(CanTp_RxCfg_GetMaxPayload((RxSduHdl))))      /* is already the payload length of a CF */

#define CanTp_TxCfg_GetMaxPayloadSF(TxHdl)      ((uint8)(CANTP_CAN20_FRAME_LENGTH - (CanTp_TxGetAdrOffset((TxHdl)) + CANTP_PCI_LENGTH_SF)))
#define CanTp_TxCfg_GetMaxPayloadLSF(TxHdl)     ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl)) - 1u))    /* 1 byte less payload than a CF         */
#define CanTp_TxCfg_GetMaxPayloadFF(TxHdl)      ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl)) - 1u))    /* 1 byte less payload than a CF         */
#define CanTp_TxCfg_GetMaxPayloadLFF(TxHdl)     ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl)) - 5u))    /* 5 byte less payload than a CF         */
#define CanTp_TxCfg_GetMaxPayloadCF(TxHdl)      ((uint8)(CanTp_TxCfg_GetMaxPayload((TxHdl))))         /* is already the payload length of a CF */


/* --- SF / FF Data Length Boundary -------------------------------------------------------------------------------- */
#if ((CANTP_RX_CHECK_CANTYPE == STD_ON) || (CANTP_RX_HAS_CANFD == STD_ON))
/* CAN-FD is possible: calculate the max. SF DL, depending on the received DLC */
/* [ISO]: "The receiving node shall always adapt to the settings of the sender."     */
# define CanTp_RxCfg_GetMaxSFDataLength(RxHdl, DLC)   (((DLC) >  (PduLengthType)CANTP_CAN20_FRAME_LENGTH) ? ((DLC) - (CanTp_RxGetAdrOffset((RxHdl)) + (PduLengthType)CANTP_PCI_LENGTH_LSF)) : (CanTp_RxCfg_GetMaxPayloadSF((RxHdl))))
#else
/* pure CAN2.0 configuration: use always standard SF length */
# define CanTp_RxCfg_GetMaxSFDataLength(RxHdl, DLC)  CanTp_RxCfg_GetMaxPayloadSF((RxHdl))
#endif

#if (CANTP_TX_CHECK_CANTYPE == STD_ON)
/* mixed CAN2.0/CAN-FD configuration: SF DL depends on CAN type and configured PduLength */
# define CanTp_TxCfg_GetMaxSFDataLength(TxHdl)   ((CANTP_CANTYPE_CANFD == CanTp_TxCfg_GetCanType((TxHdl))) ? (CanTp_TxCfg_GetMaxPayloadLSF((TxHdl))) : (CanTp_TxCfg_GetMaxPayloadSF((TxHdl))))
#else
# if (CANTP_TX_HAS_CANFD == STD_ON)
/* pure CAN-FD configuration: SF DL is always the LSF payload */
#  define CanTp_TxCfg_GetMaxSFDataLength(TxHdl)  CanTp_TxCfg_GetMaxPayloadLSF((TxHdl))
# else
/* pure CAN2.0 configuration: SF DL is always the standard SF payload */
#  define CanTp_TxCfg_GetMaxSFDataLength(TxHdl)  CanTp_TxCfg_GetMaxPayloadSF((TxHdl))
# endif
#endif


/* --- Access to RAM Variables and Arrays -------------------------------------------------------------------------- */
#define CanTp_Data_RxState(RxChannel)            CanTp_GetRxState((RxChannel))
#define CanTp_Data_TxState(TxChannel)            CanTp_GetTxState((TxChannel))
#define CanTp_Data_RxChannelMap(RxHdl)           CanTp_GetRxChannelMap((RxHdl))
#define CanTp_Data_TxChannelMap(TxHdl)           CanTp_GetTxChannelMap((TxHdl))
#define CanTp_Data_CalcBS(RxHdl)                 CanTp_GetCalcBS((RxHdl))
#define CanTp_Data_DynFcParam(RxHdl)             CanTp_GetDynFCParameters((RxHdl))
#define CanTp_Data_TxSemaphore(TxPdu)            CanTp_GetTxSemaphores((TxPdu))
#define CanTp_Data_TxQueue(TxPdu)                CanTp_GetTxQueue((TxPdu))
#define CanTp_Data_InitState()                   CanTp_InitState
#define CanTp_Data_CfgPtr()                      CanTp_ConfigDataPtr


/* --- Data Assemble / Disassemble --------------------------------------------------------------------------------- */
#define CanTp_Util_Make16Bit(hiByte, loByte)     ((uint16)((((uint16)(hiByte)) << 8) | ((uint16)(loByte))))
/* compose from byte stream a 32 bit data */
#define CanTp_Util_Make32Bit(hihiByte, hiloByte, lohiByte, loloByte) ((uint32)((((uint32)(hihiByte)) << 24) | (((uint32)(hiloByte)) << 16) | \
                                                                               (((uint32)(lohiByte)) << 8)  | ((uint32)(loloByte))))
/* Parse 16 bit data in byte stream */
#define CanTp_Util_GetHiByte(data)               ((uint8)(((uint16)(data)) >> 8))
#define CanTp_Util_GetLoByte(data)               ((uint8)(data))

/* Parse 32 bit data in byte stream */
#define CanTp_Util_GetHiHiByte(data)             ((uint8)(((uint32)(data)) >> 24))
#define CanTp_Util_GetHiLoByte(data)             ((uint8)(((uint32)(data)) >> 16))
#define CanTp_Util_GetLoHiByte(data)             ((uint8)(((uint32)(data)) >> 8))
#define CanTp_Util_GetLoLoByte(data)             ((uint8)(data))


/* --- SDU Handle Retrieve Macros ---------------------------------------------------------------------------------- */
/* Check availability of SDUs references */
/* Symbolic Name Value --> SduConfig */
#define CanTp_RxSduSnvIsAvailable(CanTpRxSduId)        CanTp_IsRxSduCfgUsedOfRxSduSnv2Hdl((CanTpRxSduId))              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxSduSnvIsAvailable(CanTpTxSduId)        CanTp_IsTxSduCfgUsedOfTxSduSnv2Hdl((CanTpTxSduId))              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* RxSduConfig <--> TxSduConfig */
#define CanTp_RxSdu2TxSduRefIsAvailable(CanTpRxSduId)  CanTp_IsTxSduCfgUsedOfRxSduCfg((CanTpRxSduId))                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CanTp_TxSdu2RxSduRefIsAvailable(CanTpTxSduId)  CanTp_IsRxSduCfgUsedOfTxSduCfg((CanTpTxSduId))                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* RxPduMap --> SduConfig */
#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
# define CanTp_CanIfRxPduHasTxSduRef(CanTpRxPduId)     CanTp_IsTxSduCfgIndUsedOfRxPduMap((CanTpRxPduId))               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
# define CanTp_CanIfRxPduHasTxSduRef(CanTpRxPduId)     FALSE
#endif
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
# define CanTp_CanIfRxPduHasRxSduRef(CanTpRxPduId)     CanTp_IsRxSduCfgIndUsedOfRxPduMap((CanTpRxPduId))               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
# define CanTp_CanIfRxPduHasRxSduRef(CanTpRxPduId)     FALSE
#endif

/* Get SduHandle by SduId / SymbolicNameValue */
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
# define CanTp_RxGetSduHdlBySduId(CanTpRxSduId)        (PduIdType)CanTp_GetRxSduCfgIdxOfRxSduSnv2Hdl((CanTpRxSduId))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
# define CanTp_RxGetSduHdlBySduId(CanTpRxSduId)        (PduIdType)0                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
# define CanTp_TxGetSduHdlBySduId(CanTpTxSduId)        (PduIdType)CanTp_GetTxSduCfgIdxOfTxSduSnv2Hdl((CanTpTxSduId))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
# define CanTp_TxGetSduHdlBySduId(CanTpTxSduId)        (PduIdType)0                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

/* --- Channel Access Macros --------------------------------------------------------------------------------------- */
/* By default, for each SDU a separate channel with the according state machine data exists.
 * With dynamic channel assignment, an indirection table is added which maps the SDU handles to channel handles.
 *   GetChannelPtr: pointer to state data of one channel
 *   ChannelIsIdle: with dynamic channel assignment, a channel is idle if it is not mapped to a connection
 *                  with normal channel assignment, there is no mapping, the channel state indicates if a connection is idle
 */
#if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
# define CanTp_RxGetChannelPtr(RxHdl)            &CanTp_Data_RxState(CanTp_Data_RxChannelMap((RxHdl)))
# define CanTp_TxGetChannelPtr(TxHdl)            &CanTp_Data_TxState(CanTp_Data_TxChannelMap((TxHdl)))

# define CanTp_RxChannelIsIdle(RxHdl)            (CanTp_Data_RxChannelMap((RxHdl)) == CANTP_INVALID_HDL)
# define CanTp_TxChannelIsIdle(TxHdl)            (CanTp_Data_TxChannelMap((TxHdl)) == CANTP_INVALID_HDL)
#else
# define CanTp_RxGetChannelPtr(RxHdl)            &CanTp_Data_RxState((RxHdl))
# define CanTp_TxGetChannelPtr(TxHdl)            &CanTp_Data_TxState((TxHdl))

# define CanTp_RxChannelIsIdle(RxHdl)            (CanTp_Data_RxState((RxHdl)).ChannelState == CANTP_RXSTATE_IDLE )
# define CanTp_TxChannelIsIdle(TxHdl)            (CanTp_Data_TxState((TxHdl)).ChannelState == CANTP_TXSTATE_IDLE)
#endif


/* --- Transmit Queue Handling ------------------------------------------------------------------------------------- */
#define CANTP_TX_QUEUE_MASK                      (CANTP_TX_QUEUE_SIZE - 1u)                                                                          /* bit mask for ring buffer handling */
#define CanTp_TxQueueIsEmpty(Id)                 (CanTp_Data_TxQueue(Id).WritePos == CanTp_Data_TxQueue(Id).ReadPos)                                /* empty: read  = write */
#define CanTp_TxQueueIsFull(Id)                  (((CanTp_Data_TxQueue(Id).WritePos + 1u) & CANTP_TX_QUEUE_MASK) == CanTp_Data_TxQueue(Id).ReadPos)  /* full: (write+1) & mask = read */
#define CanTp_TxQueueEntryReadPos(Id)            (CanTp_Data_TxQueue((Id)).Entries[CanTp_Data_TxQueue((Id)).ReadPos])                               /* get queue entry from read position */
#define CanTp_TxQueueEntryWritePos(Id)           (CanTp_Data_TxQueue((Id)).Entries[CanTp_Data_TxQueue((Id)).WritePos])                              /* get queue entry from write position */


/* --- Flow Control Parameters ------------------------------------------------------------------------------------- */
/* BlockSize and STmin are configured statically, but may also be changed during runtime. When the
 * CanTp_ChangeParam API is enabled, the current BS / STmin will have to be read from a RAM array.
 */
#if (CANTP_ENABLE_CHANGE_PARAM == STD_ON)
/* get BS and STmin values from RAM array */
# define CanTp_RxGetCurrentSTmin(RxHdl)          CanTp_Data_DynFcParam((RxHdl)).STmin
# define CanTp_RxGetCurrentBS(RxHdl)             CanTp_Data_DynFcParam((RxHdl)).BS
#else
/* get configured BS and STmin from ROM */
# define CanTp_RxGetCurrentSTmin(RxHdl)          CanTp_RxCfg_GetSTmin((RxHdl))
# define CanTp_RxGetCurrentBS(RxHdl)             CanTp_RxCfg_GetBS((RxHdl))
#endif

/* PRQA L:MACROS */


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* CAN Type */
typedef uint8                                    CanTp_CanType;

/* Transmission result */
typedef uint8                                    CanTp_TxResultType;
#define CANTP_TX_OK                              E_OK                     /* CanIf_Transmit succeeded or N-PDU is queued */
#define CANTP_TX_NOT_OK                          E_NOT_OK                 /* CanIf_Transmit failed */
#define CANTP_TX_BUSY                            (0x0Fu)                  /* transmission in progress, retry is required */

/* control commands to reset dynamic channel assignment mapping */
typedef uint8                                    CanTp_ResetControlType;
#define CANTP_RESET_BUT_KEEP_MAPPING             (CanTp_ResetControlType)(0x00u)   /* reset only state data of a channel, but keep channel mapping */
#define CANTP_RESET_ALL                          (CanTp_ResetControlType)(0x01u)   /* reset state data and channel mapping                         */

/*! N-PDU Transmit Information */
typedef struct sCanTp_PduTxInfoType
{
  CanTp_DirectionType    SduDirection;           /*!< direction of SDU which request N-PDU transmission */
  PduIdType              SduHdl;                 /*!< handle of SDU which request N-PDU transmission */
  PduIdType              TxPduId;                /*!< CanIf Id of N-PDU to be transmitted */
  PduIdType              TxConfPduId;            /*!< TxConf Id of N-PDU to be transmitted */
#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
  uint8                  PaddingLength;          /*!< final length of N-PDU after padding settings have been applied */
#endif
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8*                 PduMetadata;            /*!< buffer with metadata to be passed to the lower layer */
  uint8                  PduMetadataLength;      /*!< length of the metadata to be passed to the lower layer */
#endif
} CanTp_PduTxInfoType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * CONSISTENCY CHECKS
 *********************************************************************************************************************/
/* At least one addressing format must be enabled */
#if ((CANTP_STANDARD_ADDRESSING != STD_ON) && \
     (CANTP_EXTENDED_ADDRESSING != STD_ON) && \
     (CANTP_MIXED11_ADDRESSING != STD_ON)  && \
     (CANTP_MIXED29_ADDRESSING != STD_ON)  && \
     (CANTP_NORMALFIXED_ADDRESSING != STD_ON))
# error "No Addressing Format is configured!"
#endif

/* Separation of DET check and reporting */
#if ((CANTP_DEV_ERROR_REPORT == STD_ON) && (CANTP_DEV_ERROR_DETECT == STD_OFF))
# error "DET reporting is only allowed if DET checks are enabled!"
#endif

#if (CANTP_USE_INIT_POINTER != STD_ON)
# if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
/* dynamic channel assignment: more SDUs than channels must be defined */
#  if ((CANTP_NUM_RX_CHANNELS > CANTP_NUM_RX_SDUS) || \
       (CANTP_NUM_TX_CHANNELS > CANTP_NUM_TX_SDUS))
#   error "Inconsistent setting for number of channels; with dynamic channel assignment, more SDUs than channels are expected"
#  endif
# else

/* no dynamic channel assignment:                                 */
/* - no SDU defined: number of channels must be 1                 */
/* - SDU defined: number of channels must be equal number of SDUs */
#  if (CANTP_NUM_RX_SDUS == 0)                                                                                         /* COV_CANTP_ROBUSTNESS_CASE XF */
#   if (CANTP_NUM_RX_CHANNELS != 1)                                                                                    /* COV_CANTP_ROBUSTNESS_CASE XX */
#    error "Inconsistent setting for number of channels; even if no SDU is configured, the config tool should generate at least one dummy channel"
#   endif
#  else
#   if (CANTP_NUM_RX_CHANNELS != CANTP_NUM_RX_SDUS)
#    error "Inconsistent setting for number of channels; in the current configuration, it is expected that for each SDU a separate channel exists"
#   endif
#  endif

#  if (CANTP_NUM_TX_SDUS == 0)                                                                                         /* COV_CANTP_ROBUSTNESS_CASE XF */
#   if (CANTP_NUM_TX_CHANNELS != 1)                                                                                    /* COV_CANTP_ROBUSTNESS_CASE XX */
#    error "Inconsistent setting for number of channels; even if no SDU is configured, the config tool should generate at least one dummy channel"
#   endif
#  else
#   if (CANTP_NUM_TX_CHANNELS != CANTP_NUM_TX_SDUS)
#    error "Inconsistent setting for number of channels; in the current configuration, it is expected that for each SDU a separate channel exists"
#   endif
#  endif
# endif /* (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON) */
#endif /* else: post-build configuration; number of channels and SDUs may change */


/* Consistency check for if-else optimization switches  */
/*             switch setting               |         resulting code        | check result
 * -----------------------------------------+-------------------------------+-------------
 * CHECK_X == OFF  HAS_X = OFF, HAS_Y = OFF |                               |  error
 * CHECK_X == OFF, HAS_X = OFF, HAS_Y = ON  |                      { do Y } |  ok
 * CHECK_X == OFF, HAS_X = ON,  HAS_Y = OFF |        { do X }               |  ok
 * CHECK_X == OFF, HAS_X = ON,  HAS_Y = ON  |        { do X }      { do Y } |  error
 * CHECK_X == ON,  HAS_X = OFF, HAS_Y = OFF | if (X)          else          |  error
 * CHECK_X == ON,  HAS_X = OFF, HAS_Y = ON  | if (X)          else { do Y } |  error
 * CHECK_X == ON,  HAS_X = ON,  HAS_Y = OFF | if (X) { do X } else          |  error
 * CHECK_X == ON,  HAS_X = ON,  HAS_Y = ON  | if (X) { do X } else { do Y } |  ok
 *
 * Rules:
 * if CHECK_X == OFF: HAS_X must be unequal to HAS_Y
 * if CHECK_X == ON:  HAS_X and HAS_Y must be enabled
 */
/* Channel Mode: consistency in case of XX_CHECK_HALF_DUPLEX = STD_ON is already given by its definition */
#if ((CANTP_RX_CHECK_HALF_DUPLEX == STD_OFF) && (CANTP_RX_HAS_HALF_DUPLEX == CANTP_RX_HAS_FULL_DUPLEX))
# error "Inconsistent Rx channel mode configuration; either half or full duplex must be configured!"
#endif
#if ((CANTP_TX_CHECK_HALF_DUPLEX == STD_OFF) && (CANTP_TX_HAS_HALF_DUPLEX == CANTP_TX_HAS_FULL_DUPLEX))
# error "Inconsistent Tx channel mode configuration; either half or full duplex must be configured!"
#endif

/* CAN Type: consistency in case of XX_CHECK_CANTYPE = STD_ON is already given by its definition */
#if ((CANTP_RX_CHECK_CANTYPE == STD_OFF) && (CANTP_RX_HAS_CANFD == CANTP_RX_HAS_CAN20))
# error "Inconsistent Rx CanType configuration; either CAN-FD or CAN2.0 must be configured!"
#endif
#if ((CANTP_TX_CHECK_CANTYPE == STD_OFF) && (CANTP_TX_HAS_CANFD == CANTP_TX_HAS_CAN20))
# error "Inconsistent Rx CanType configuration; either CAN-FD or CAN2.0 must be configured!"
#endif

/* special handling for reserved STmin:                         */
/* only one of the two available switches must be active;       */
/* otherwise the CanTp might not behave as desired              */
#if ((CANTP_IGNORE_FC_WITH_RES_STMIN == STD_ON) && \
     (CANTP_REJECT_FC_WITH_RES_STMIN == STD_ON))
# error "Inconsistent setting for handling of reserved STmin"
#endif

/* PDU metadata is available only for normal fixed and mixed29 addressing modes */
#if ((CANTP_MAX_PDU_METADATA_LENGTH != 0) && (CANTP_NORMALFIXED_ADDRESSING == STD_OFF) && (CANTP_MIXED29_ADDRESSING == STD_OFF))
# error "Inconsistent PDU metadata configuration. Only the normal fixed and mixed29 addressing modes use PDU metadata!"
#endif

#endif /* CANTP_PRIV_H */

/**********************************************************************************************************************
 *  END OF FILE: CanTp_Priv.h
 *********************************************************************************************************************/
