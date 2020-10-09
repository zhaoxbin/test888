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
/*!        \file
 *        \brief  CanTp source file
 *
 *      \details  Implementation of the CAN Transport Protocol.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Thomas Dedler                 visdth        Vector Informatik GmbH
 *  Anthony Thomas                visath        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id      Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-06-12  visdth  ESCAN00057161: implementation of CanTp module according to AR 4.0.3.
 *  01.01.00  2013-01-15  visdth  ESCAN00062137: synchronous CanTp_Transmit removed (incompatible with AR4 PduR)
 *                        visdth  ESCAN00061697: AR4-220: Remove STATIC
 *                        visdth  ESCAN00064160: Reception timeout will not occur / Array out of bounds access resulting in unexpected behavior
 *  01.02.00  2013-04-05  visdth  ESCAN00061899: refactoring of Rx buffer handling
 *                        visdth  ESCAN00061907: refactoring of Tx buffer handling
 *                        visdth  ESCAN00065205: inconsistent parameter naming resolved
 *                        visdth  ESCAN00065208: Compiler warning: Unreferenced local variable 'pTpTxState'
 *                        visdth  ESCAN00064308: AR4-325: Implement Post-Build Loadable
 *  01.03.00  2013-09-27  visdth  ESCAN00066720: Rework CAN frame transmission to reduce superfluous code
 *                        visdth  ESCAN00067750: minor optimizations after code coverage analysis
 *                        visdth  ESCAN00066738: DataLength parameter removed
 *                        visdth  ESCAN00070025: obsolete feature "DCM Request Detection" removed
 *                        visdth  ESCAN00074928: AR4-450: Usage of section PBCFG in PB files
 *                        visdth  ESCAN00070726: inclusion of v_ver.h removed
 *  01.04.00  2014-04-10  visdth  ESCAN00071899: AR4-619: Support the StartOfReception API (with the PduInfoType), TxConfirmation and RxIndication according ASR4.1.2
 *                        visdth  ESCAN00072826: support synchronous CanTp_Transmit
 *                        visdth  ESCAN00074912: Compiler error: Missing "const" keyword in optional application callouts
 *                        visdth  ESCAN00074795: Improvement for handling of inverted order of RxIndication and TxConfirmation
 *                        visdth  ESCAN00075227: reset state data without MemSet
 *                        visdth  ESCAN00075832: FC.WAIT is transmitted, although WFTmax is configured as 0
 *                        visdth  ESCAN00076167: Compiler error: identifier "pRxNsduCfg" is undefined in CanTp_ReadParameter API
 *  02.00.00  2014-09-01  visdth  ESCAN00076289: Support of multi-frames with more than 4095 Byte
 *                        visdth  ESCAN00076496: AR4-720: Support CAN FD Mode 2 for communication and diagnostics
 *                        visdth  ESCAN00076618: AR4-698: Post-Build Selectable (Identity Manager)
 *                        visdth  ESCAN00077446: Upper Layer is notified of functional first frame reception, although not required
 *                        visdth  ESCAN00077423: Refactoring of application notification call-outs
 *                        visdth  ESCAN00078333: CanTp does not continue after FC.WAIT although sufficient buffer is provided
 *  02.01.00  2015-01-26  visdth  ESCAN00079259: Compiler warning: variable is possibly unset at this point.
 *                        visdth  ESCAN00079350: Compiler warning: statement will never be executed
 *                        visdth  ESCAN00079403: Rx connection should not be terminated by the reception of an invalid SF or FF
 *                        visdth  ESCAN00079584: CanTp should be able to send FC.WAIT in case of insufficient buffer for SF or FF
 *                        visdth  ESCAN00079796: FEAT-63: Support CAN-FD Mode 2 for communication and diagnostics
 *                        visdth  ESCAN00079960: Initialization of CanTp causes DET in CanIf
 *                        visdth  ESCAN00080150: Improve robustness of half duplex check
 *                        visdth  ESCAN00080293: FEAT-427: SafeBSW Step I
 *                        visdth  ESCAN00080488: Compiler error: undeclared identifier 'lTxSduHdl'
 *                        visdth  ESCAN00080652: Compiler error: CanTp_GetTxSduCfgInd* not defined
 *  02.01.01  2015-04-09  visdth  ESCAN00082219: STmin by Application prototype implementation
 *                        visdth  ESCAN00082309: Compiler error: too many parameters in function call for CanTp_TxInit
 *                        visdth  ESCAN00082331: N_Cs handling not according to ISO 15765-2
 *  02.02.00  2015-07-01  visdth  ESCAN00082667: Add Generator Version Check
 *                        visdth  ESCAN00081781: FEAT-1275: SafeBSW Step 2
 *                        visdth  ESCAN00082374: FEAT-1367: Support STmin by application
 *                        visdth  ESCAN00083175: Length of Flow Control frames may be shorter than required by ISO
 *  03.00.00  2015-11-16  visdth  ESCAN00081135: Remove Notify Always features
 *                        visdth  ESCAN00084793: Add DET error for deleted Rx N-PDUs
 *                        visdth  ESCAN00084889: Missing check for minimum data length of extended single frames
 *                        visdth  ESCAN00085932: Compiler warning: cantp.c: warning: '<=' : signed/unsigned mismatch
 *                        visdth  ESCAN00085148: FEAT-1527: SafeBSW Step 3
 *                        visdth  ESCAN00086136: FEAT-1431: Optimization of CanTp_MainFunction runtime
 *                        visdth  ESCAN00086701: Transmitted Flow Control messages are not cancelled in case of N_Ar timeout
 *  03.01.00  2016-02-24  visdth  ESCAN00087799: FEAT-1688: SafeBSW Step 4
 *  03.02.00  2016-04-06  visdth  ESCAN00089070: Introduce pointer based connection identification for internal functions
 *                        visath  ESCAN00089390: FEAT-1734: SafeBSW Step 5
 *  03.03.00  2017-02-27  visath  ESCAN00092715: Fixed MISRA deviations
 *                        visath  FEATC-667:     FEAT-2144: Mixed11 Addressing Prioritization
 *  03.03.01  2017-04-12  visath  ESCAN00091493: Modified the DET error reporting for extended and mixed11 addressing
 *  03.03.02  2018-02-23  visath  ESCAN00097375: Compiler warning: 'lTxHdl' : local variable is initialized but not referenced
 *                        visath  ESCAN00097790: Compiler warning:  'CanTpTxSduId' : unreferenced formal parameter
 *                        visath  ESCAN00097950: Compiler error: 'CanTp_GetRxSduCfgInd' undefined
 *                        visath  ESCAN00094451: CanTp_ApplStartSeparationTime is now called with the SDU's SNV
 *                        visath  ESCAN00098595: The main functions now always check if the module has been initialized
 *  03.03.03  2018-08-10  visath  ESCAN00100333: Always initialize all the Rx and Tx channel structures
 *  03.04.00  2018-12-13  visath  STORYC-6491:   Support the PduR as lower layer
 *  03.05.00  2019-03-12  visath  STORYC-7040:   Support metadata according to AR 4.2.2
 *********************************************************************************************************************/
#define CANTP_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CanTp.h"
#include "CanTp_Cbk.h"

/* interface to upper and lower layer */
#include "PduR_CanTp.h"
#if (CANTP_LOLAYER_CANIF == STD_ON)
# include "CanIf.h"
#endif

#if (CANTP_DCM_REQUEST_DETECT == STD_ON)
# include "Dcm_Cbk.h"
#endif

/* critical sections handled by SchM */
#include "SchM_CanTp.h"

#if (CANTP_DEV_ERROR_REPORT == STD_ON)
/* development error reporting */
# include "Det.h"
#endif

#if (CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
/* post-build error reporting */
# include "EcuM_Error.h"
#endif

/* CanTp internal definitions */
#include "CanTp_Priv.h"


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of CanTp header files */
#if (  (CANTP_SW_MAJOR_VERSION != (3u)) \
    || (CANTP_SW_MINOR_VERSION != (5u)) \
    || (CANTP_SW_PATCH_VERSION != (0u)) )
# error "Version numbers of CanTp.c and CanTp.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (CANTP_CFG_GEN_MAJOR_VERSION != (4u)) \
    || (CANTP_CFG_GEN_MINOR_VERSION != (4u)) )
# error "Version numbers of CanTp.c and CanTp_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* --- Compiler Keywords ------------------------------------------------------------------------------------------- */
#if !defined (CANTP_LOCAL)                                                                                             /* COV_CANTP_UNIT_TEST XF */
# define CANTP_LOCAL                   static
#endif

#if !defined (CANTP_LOCAL_INLINE)                                                                                      /* COV_CANTP_UNIT_TEST TX */
# define CANTP_LOCAL_INLINE            LOCAL_INLINE
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 MACROS */ /* MD_MSR_FctLikeMacro */
/* --- API Calls to other BSW Modules ------------------------------------------------------------------------------ */
/* All calls are mapped to the according default AUTOSAR API. By providing a macro or function with the name of the  */
/* internal macro, the calls can be mapped to a user defined function (e.g. when using the CanTp in another stack).  */
/* --- PduR --- */
#if !defined (CanTp_PduRRxIndication)                                                                                  /* COV_MSR_COMPATIBILITY TX */
# define CanTp_PduRRxIndication(CanTpRxPduId, Result)                               (PduR_CanTpRxIndication( (CanTpRxPduId), (Result) ))
#endif
#if !defined (CanTp_PduRTxConfirmation)                                                                                /* COV_MSR_COMPATIBILITY TX */
# define CanTp_PduRTxConfirmation(CanTpTxPduId, Result)                             (PduR_CanTpTxConfirmation( (CanTpTxPduId), (Result) ))
#endif
#if !defined (CanTp_PduRStartOfReception)                                                                              /* COV_MSR_COMPATIBILITY TX */
# if (CANTP_PDUR_API_403_ENABLED == STD_ON)                                                                            /* COV_MSR_COMPATIBILITY XF */
#  define CanTp_PduRStartOfReception(CanTpRxPduId, PduInfoPtr, SduLength, RxBufSizePtr)     (CanTp_BufferStateType)(PduR_CanTpStartOfReception( (CanTpRxPduId), (SduLength), (RxBufSizePtr) ))
# else
#  if (CANTP_GENERIC_CONNECTIONS == STD_ON)
#   define CanTp_PduRStartOfReception(CanTpRxPduId, PduInfoPtr, SduLength, RxBufSizePtr)    (CanTp_BufferStateType)(PduR_CanTpStartOfReception( (CanTpRxPduId), (PduInfoPtr), (SduLength), (RxBufSizePtr) ))
#  else
#   define CanTp_PduRStartOfReception(CanTpRxPduId, PduInfoPtr, SduLength, RxBufSizePtr)    (CanTp_BufferStateType)(PduR_CanTpStartOfReception( (CanTpRxPduId), NULL_PTR,     (SduLength), (RxBufSizePtr) ))   
#  endif
# endif
#endif
#if !defined (CanTp_PduRCopyRxData)                                                                                    /* COV_MSR_COMPATIBILITY TX */
# define CanTp_PduRCopyRxData(CanTpRxPduId, PduInfoPtr, RxBufSizePtr)               (CanTp_BufferStateType)(PduR_CanTpCopyRxData( (CanTpRxPduId), (PduInfoPtr), (RxBufSizePtr) ))
#endif
#if !defined (CanTp_PduRCopyTxData)                                                                                    /* COV_MSR_COMPATIBILITY TX */
# define CanTp_PduRCopyTxData(CanTpRxPduId, PduInfoPtr, RetryInfoPtr, RxBufSizePtr) (CanTp_BufferStateType)(PduR_CanTpCopyTxData( (CanTpRxPduId), (PduInfoPtr), NULL_PTR, (RxBufSizePtr) ))
#endif

/* --- Det --- */
#if !defined (CanTp_DetReportError)                                                                                    /* COV_MSR_COMPATIBILITY TX */
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
#  define CanTp_DetReportError(ApiId, ErrorId)                       ((void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID_DET, (ApiId), (ErrorId) ));
# else
#  define CanTp_DetReportError(ApiId, ErrorId)
# endif
#endif

/* --- EcuM --- */
#if !defined (CanTp_EcuMReportBswError)                                                                                /* COV_MSR_COMPATIBILITY TX */
# if (CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
#  define CanTp_EcuMReportBswError(EcuMErrorId)                      (EcuM_BswErrorHook((uint16) CANTP_MODULE_ID, (EcuMErrorId)));
# else
#  define CanTp_EcuMReportBswError(EcuMErrorId)
# endif
#endif

/* --- Dcm --- */
#if !defined (CanTp_DcmForwardNAE)                                                                                     /* COV_MSR_COMPATIBILITY TX */
# if ((CANTP_DCM_REQUEST_DETECT == STD_ON))
#  define CanTp_DcmForwardNAE(CanTpRxPduId, N_AE)                  (Dcm_OnRequestDetection( (CanTpRxPduId), (N_AE) ))
# else
#  define CanTp_DcmForwardNAE(CanTpRxPduId, N_AE)
# endif
#endif


/* --- User Defined Notifications ----------------------------------------------------------------------------------- */
#if (CANTP_APPL_RX_SF_INDICATION == STD_ON)
# define CanTp_ApplRxSFIndication(PduRRxPduId, PduInfo)              (Appl_CanTpRxSFIndication( (PduRRxPduId), (PduInfo)));
#else
# define CanTp_ApplRxSFIndication(PduRRxPduId, PduInfo)
#endif

#if (CANTP_APPL_RX_FF_INDICATION == STD_ON)
# define CanTp_ApplRxFFIndication(PduRRxPduId, PduInfo)              (Appl_CanTpRxFFIndication( (PduRRxPduId), (PduInfo)));
#else
# define CanTp_ApplRxFFIndication(PduRRxPduId, PduInfo)
#endif

#if (CANTP_APPL_RX_CF_INDICATION == STD_ON)
# define CanTp_ApplRxCFIndication(PduRRxPduId, PduInfo)              (Appl_CanTpRxCFIndication( (PduRRxPduId), (PduInfo)));
#else
# define CanTp_ApplRxCFIndication(PduRRxPduId, PduInfo)
#endif

#if (CANTP_APPL_FRAME_TRANSMISSION == STD_ON)
# define CanTp_ApplFrameTransmission(CanIfTxPduId, PduInfo)          (Appl_CanTpFrameTransmission((CanIfTxPduId), (PduInfo)));
#else
# define CanTp_ApplFrameTransmission(CanIfTxPduId, PduInfo)
#endif

#if (CANTP_APPL_FRAME_CONFIRMATION == STD_ON)
# define CanTp_ApplFrameTxConfirmation(CanIfTxPduId)                 (Appl_CanTpFrameTxConfirmation((CanIfTxPduId)));
#else
# define CanTp_ApplFrameTxConfirmation(CanIfTxPduId)
#endif


/* --- Internal Function Calls ------------------------------------------------------------------------------------- */
#if (CANTP_TX_FC_FROM_ISR == STD_ON)                                                                                   /* COV_CANTP_EXCLUDED_FEATURES TX */
/* FC transmission is started immediately within ISR context */
# define CanTp_RxTransmitFrame_ISR(ptr)                              (CanTp_RxTransmitFrame( (ptr) ));
#else
/* FC is not transmitted in ISR context but on task level */
# define CanTp_RxTransmitFrame_ISR(ptr)
#endif

#if (CANTP_RX_GET_BUFFER_FROM_ISR == STD_ON)                                                                           /* COV_CANTP_EXCLUDED_FEATURES TX */
/* buffer request is performed immediately within ISR context */
# define CanTp_RxGetBuffer_ISR(ptr)                                  (CanTp_RxGetBuffer( (ptr) ));
#else
/* buffer is not requested in ISR context but on task level */
# define CanTp_RxGetBuffer_ISR(ptr)
#endif

#if (CANTP_TX_GET_BUFFER_FROM_ISR == STD_ON)                                                                           /* COV_CANTP_EXCLUDED_FEATURES TX */
/* buffer request is performed immediately within ISR context */
# define CanTp_TxGetBuffer_ISR(ptr)                                  (CanTp_TxGetBuffer( (ptr) ));
#else
/* buffer is not requested in ISR context but on task level */
# define CanTp_TxGetBuffer_ISR(ptr)
#endif


/* --- Error Reporting and Assertions ------------------------------------------------------------------------------ */
/* Assertions (only when DET is active) */
#if !defined (CanTp_DetAssert)
# if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_CANTP_DET_CHECK TX */
#  define CanTp_DetAssert(Check, ApiId, ErrorId)                     { if (!(Check)) {CanTp_DetReportError( (ApiId), (ErrorId) ) }}
# else
#  define CanTp_DetAssert(Check, ApiId, ErrorId)
# endif
#endif


/* --- Critical Section Handling ----------------------------------------------------------------------------------- */
/* critical section in interrupt context */
#define CanTp_EnterCritical()                                        SchM_Enter_CanTp_CANTP_EXCLUSIVE_AREA_0()
#define CanTp_LeaveCritical()                                        SchM_Exit_CanTp_CANTP_EXCLUSIVE_AREA_0()

/* PRQA L:MACROS */


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* --- Initialization State ---------------------------------------------------------------------------------------- */
#define CANTP_START_SEC_VAR_INIT_8BIT
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */
CANTP_LOCAL VAR(CanTp_InitStatusType, CANTP_VAR_INIT) CanTp_InitState = CANTP_STATUS_NOT_INITIALIZED;
#define CANTP_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* --- Dynamic Channel Assignment Resources ------------------------------------------------------------------------ */
#if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
# define CANTP_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h"                                                                                                   /* PRQA S 5087 */ /* MD_MSR_MemMap */
CANTP_LOCAL VAR(PduIdType, CANTP_VAR_NOINIT) CanTp_NumRxChannelsAvail;
CANTP_LOCAL VAR(PduIdType, CANTP_VAR_NOINIT) CanTp_NumTxChannelsAvail;
# define CANTP_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h"                                                                                                   /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif


/* --- Global Config Pointer --------------------------------------------------------------------------------------- */
#if (CANTP_USE_INIT_POINTER == STD_ON)
# define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"                                                                                                   /* PRQA S 5087 */ /* MD_MSR_MemMap */
CANTP_LOCAL P2CONST(CanTp_ConfigType, CANTP_VAR_NOINIT, CANTP_INIT_DATA) CanTp_ConfigDataPtr;
# define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"                                                                                                   /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* --- Direction Specific Main Functions --------------------------------------------------------------------------- */
#if (CANTP_RXTX_MAINFUNCTION_API != STD_ON)
/**********************************************************************************************************************
  CanTp_MainFunctionRx()
**********************************************************************************************************************/
/*! \brief         Handles timing tasks and asynchronous operations of all Rx connections
 *  \details       This function handles scheduling and timeout supervision of active receive connections.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \config        If CANTP_RXTX_MAINFUNCTION_API = STD_ON, this function is externally visible and the prototype is
 *                 provided by the SchM.
 *  \pre           -
 *  \trace         DSGN-CanTp23053
 *********************************************************************************************************************/
FUNC(void,  CANTP_CODE)   CanTp_MainFunctionRx(void);                                                                  /* PRQA S 3447 */ /* MD_CanTp_3447 */

/**********************************************************************************************************************
  CanTp_MainFunctionTx()
**********************************************************************************************************************/
/*! \brief         Handles timing tasks and asynchronous operations of all Tx connections
 *  \details       This function handles scheduling and timeout supervision of active transmit connections.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
 *  \config        If CANTP_RXTX_MAINFUNCTION_API = STD_ON, this function is externally visible and the prototype is
 *                 provided by the SchM.
 *  \trace         DSGN-CanTp23083
 *********************************************************************************************************************/
FUNC(void,  CANTP_CODE)   CanTp_MainFunctionTx(void);                                                                  /* PRQA S 3447 */ /* MD_CanTp_3447 */
#endif


/* --- Internal Reset Functions ------------------------------------------------------------------------------------ */
/**********************************************************************************************************************
  CanTp_RxInitState()
**********************************************************************************************************************/
/*! \brief         Resets an Rx channel
 *  \details       Reset the internal state data of an Rx channel to default.
 *  \param[in]     RxStatePtr           Pointer to channel data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects that pTpRxState references a valid channel state
 *  \trace         DSGN-CanTp23076
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxInitState(CanTp_RxStatePtrType pTpRxState);

/**********************************************************************************************************************
  CanTp_TxInitState()
**********************************************************************************************************************/
/*! \brief         Resets a Tx channel
 *  \details       Reset the internal state data of a Tx channel to default.
 *  \param[in]     pTpTxState           Pointer to channel data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects that pTpTxState references a valid channel state
 *  \trace         DSGN-CanTp23076
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_TxInitState(CanTp_TxStatePtrType pTpTxState);

/**********************************************************************************************************************
  CanTp_RxInit()
**********************************************************************************************************************/
/*! \brief         Resets an Rx connection
 *  \details       Initialize Tx channel data, notify other modules and release used resources.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \param[in]     NotifyCode             Result for upper layer notification
 *  \param[in]     DetError               Error code for DET reporting
 *  \param[in]     ResetRequest           Reset command for dynamic channel assignment (state only / state and channel mapping)
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23076
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxInit(CanTp_RxStatePtrType pTpRxState, CanTp_NotificationType NotifyCode, uint8 DetError, CanTp_ResetControlType ResetRequest);

/**********************************************************************************************************************
  CanTp_TxInit()
**********************************************************************************************************************/
/*! \brief         Resets a Tx connection
 *  \details       Initialize Tx channel data, notify other modules and release used resources.
 *  \param[in]     pTpTxState             Reference to Tx channel state object
 *  \param[in]     NotifyCode             Result for upper layer notification
 *  \param[in]     DetError               Error code for DET reporting
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects that pTpTxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23076
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxInit(CanTp_TxStatePtrType pTpTxState, CanTp_NotificationType NotifyCode, uint8 DetError);

/**********************************************************************************************************************
  CanTp_ResetChannels()
**********************************************************************************************************************/
/*! \brief         Resets all channels of the CanTp
 *  \details       Initialize all channel related data to default.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           -
 *  \trace         DSGN-CanTp23076
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_ResetChannels(void);


/* --- Interface Functions to CanIf -------------------------------------------------------------------------------- */
/**********************************************************************************************************************
  CanTp_CanIfRxIndicationSF()
**********************************************************************************************************************/
/*! \brief         Handles reception of a single frame
 *  \details       Check validity and start processing of a received single frame.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \param[in]     pPdu                   Pointer to received N-PDU data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23053
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationSF(CanTp_RxStatePtrType pTpRxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

/**********************************************************************************************************************
  CanTp_CanIfRxIndicationFF()
**********************************************************************************************************************/
/*! \brief         Handles reception of a first frame
 *  \details       Check validity and start processing of a received first frame
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \param[in]     pPdu                   Pointer to received N-PDU data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23053, DSGN-CanTp23316
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFF(CanTp_RxStatePtrType pTpRxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

/**********************************************************************************************************************
  CanTp_CanIfRxIndicationCF()
**********************************************************************************************************************/
/*! \brief         Handles reception of a consecutive frame
 *  \details       Check validity and start processing of a received consecutive frame.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \param[in]     pPdu                   Pointer to received N-PDU data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23053
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationCF(CanTp_RxStatePtrType pTpRxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

/**********************************************************************************************************************
  CanTp_CanIfRxIndicationFC()
**********************************************************************************************************************/
/*! \brief         Handles reception of a flow control frame
 *  \details       Check validity and start processing of a received flow control frame.
 *  \param[in]     pTpTxState             Reference to Tx channel state object
 *  \param[in]     pPdu                   Pointer to received N-PDU data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects that pTpTxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23083, DSGN-CanTp23294
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFC(CanTp_TxStatePtrType pTpTxState, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu);

/**********************************************************************************************************************
  CanTp_CanIfRxIndication()
**********************************************************************************************************************/
/*! \brief         Handles reception of a CanTp frame
 *  \details       Start processing of a received CanTp frame and dispatch according to the frame type.
 *  \param[in]     SduHdl                 Rx or Tx connection handle (depends on frame type)
 *  \param[in]     FrameType              Protocol frame type (SF, FF, CF or FC)
 *  \param[in]     pPayloadInfo           Pointer to the received N-PDU payload
 *  \param[in]     pMetadataInfo          Pointer to the received N-PDU metadata
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that SduHdl is a valid TxHdl if FrameType is FC (< CanTp_Cfg_GetNumTxHdls),
 *                 otherwise it must be a valid RxHdl (< CanTp_Cfg_GetNumRxHdls)
 *  \trace         DSGN-CanTp23053, DSGN-CanTp23083
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfRxIndication(PduIdType SduHdl,
                                                           uint8 FrameType,
                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
/**********************************************************************************************************************
  CanTp_CanIfTxConfirmation()
**********************************************************************************************************************/
/*! \brief         Handles confirmation of a transmitted CanTp frame
 *  \details       Continue processing of a Tx connection after successful transmission of a SF, FF or CF.
 *  \param[in]     pTpTxState             Reference to Tx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpTxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23083, DSGN-CanTp24743
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmation(CanTp_TxStatePtrType pTpTxState);
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */

#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
/**********************************************************************************************************************
  CanTp_CanIfTxConfirmationFC()
**********************************************************************************************************************/
/*! \brief         Handles confirmation of a transmitted flow control frame
 *  \details       Continue processing of an Rx connection after successful transmission of a flow control frame.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23053
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmationFC(CanTp_RxStatePtrType pTpRxState);
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */

/**********************************************************************************************************************
  CanTp_CanIfTransmitFrame()
**********************************************************************************************************************/
/*! \brief         Transmits a CanTp frame
 *  \details       Pass a prepared CanTp frame to the CanIf and handle TxSemaphore.
 *  \param[in]     pPduTxData             Pointer to connection specific Tx data (SDU/PDU IDs, Padding Length)
 *  \param[in]     pTpData                Pointer to N-PDU data to be transmitted
 *  \return        CANTP_TX_OK            Transmit request successful
 *  \return        CANTP_TX_NOT_OK        Transmit request failed
 *  \return        CANTP_TX_BUSY          Transmission already in progress; retry later
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           The following parameters are expected to be valid:
 *                 - pTpData and pTpData->SduDataPtr are valid pointers
 *                 - pTpData->SduLength is less or equal pPduTxData->PaddingLength
 *                 - pPduTxData->PaddingLength must not exceed the size of the array referenced by pTpData->SduDataPtr
 *                 - pPduTxData->TxConfPduId is a valid CanTp TxConfPduId (< CanTp_Cfg_GetNumTxConfPdus)
 *                 - pPduTxData->SduHdl and pPduTxData->SduDirection must refer to a valid Rx / Tx handle.
 *  \trace         DSGN-CanTp23060
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(CanTp_TxResultType, CANTP_CODE) CanTp_CanIfTransmitFrame(P2CONST(CanTp_PduTxInfoType, AUTOMATIC, CANTP_APPL_DATA) pPduTxData,
                                                                          P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData);


/* --- Tx Processing Functions ------------------------------------------------------------------------------------- */
/**********************************************************************************************************************
  CanTp_TxStartConnection()
**********************************************************************************************************************/
/*! \brief         Starts a new Tx connection
 *  \details       Perform initial checks and start a new CanTp transmission.
 *  \param[in]     TxSduSnv               Symbolic name value of the Tx connection
 *  \param[in]     TxHdl                  Tx connection handle
 *  \param[in]     SduLength              Length of message to be transmitted
 *  \param[in]     CanTpTxInfoPtr         Pointer to a PduInfo struct. The SduLength member contains the total length
 *                                        of the message to be transmitted and the SduDataPtr member points to metadata
 *                                        if the Tx N-SDU has been configured with it.
 *  \return        E_OK                   Transmission successfully started
 *  \return        E_NOT_OK               Transmission request rejected
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that TxHdl is valid (< CanTp_Cfg_GetNumTxHdls)
 *  \note          The SduDataPtr member of CanTpTxInfoPtr shall not be used for Tx SDUs configured without metadata.
 *  \trace         CREQ-102804
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxStartConnection(PduIdType TxSduSnv,
                                                                            PduIdType TxHdl,
                                                                            PduLengthType SduLength,
                                                                            P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);

#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
/**********************************************************************************************************************
  CanTp_TxGetStminTimerFromStminValue()
**********************************************************************************************************************/
/*! \brief         Converts STmin to number of task cycles
 *  \details       Calculate the number of task cycles required to achieve a requested STmin.
 *  \param[in]     STminValue             Value of STmin from flow control, as specified by ISO15765-2
 *  \return        Number of task cycles
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \pre           -
 *  \trace         DSGN-CanTp23083
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_TxGetStminTimerFromStminValue(uint8 STminValue);
#endif /* (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */

/**********************************************************************************************************************
  CanTp_TxGetBuffer()
**********************************************************************************************************************/
/*! \brief         Handles buffer request before transmission
 *  \details       Request the payload data of a CanTp frame to be transmitted
 *  \param[in]     pTpTxState             Reference to Tx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpTxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23061
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxGetBuffer(CanTp_TxStatePtrType pTpTxState);

/**********************************************************************************************************************
  CanTp_TxTransmitFrame()
**********************************************************************************************************************/
/*! \brief         Prepares transmission of CanTp frame
 *  \details       Assemble SF, FF or CF and trigger transmission
 *  \param[in]     pTpTxState             Reference to Tx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpTxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23083, DSGN-CanTp23316
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxTransmitFrame(CanTp_TxStatePtrType pTpTxState);

#if (CANTP_TRANSMITFCTOFLOLAYERFCTS == STD_ON)
/**********************************************************************************************************************
  CanTp_LoLayerTransmit()
**********************************************************************************************************************/
/*! \brief         Calls the transmit function of the lower layer assigned to an SDU
 *  \details       -
 *  \param[in]     Direction              SDU's direction
 *  \param[in]     SduHdl                 Rx or Tx SDU handle
 *  \param[in]     LoLayerTxPduId         PDU id provided by the lower layer
 *  \param[in]     pTpData                Pointer to PDU data to be transmitted
 *  \return        E_OK                   The transmit request has been accepted by the lower layer
 *  \return        E_NOT_OK               The transmit request has been rejected by the lower layer
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        Available if CANTP_TRANSMITFCTOFLOLAYERFCTS == STD_ON
 *  \pre           The passed SduHdl must be valid
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_LoLayerTransmit(CanTp_DirectionType Direction,
                                                                          PduIdType SduHdl,
                                                                          PduIdType LoLayerTxPduId,
                                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData);
#endif

#if (CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS == STD_ON)
/**********************************************************************************************************************
  CanTp_LoLayerCancelTransmit()
**********************************************************************************************************************/
/*! \brief         Calls the cancel transmit function of the lower layer assigned to an SDU
 *  \details       -
 *  \param[in]     Direction              SDU's direction
 *  \param[in]     SduHdl                 Rx or Tx SDU handle
 *  \param[in]     LoLayerTxPduId         PDU id provided by the lower layer
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        Available if CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS == STD_ON
 *  \pre           The passed SduHdl must be valid
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_LoLayerCancelTransmit(CanTp_DirectionType Direction,
                                                                      PduIdType SduHdl,
                                                                      PduIdType LoLayerTxPduId);
#endif


/* --- Rx Processing Functions ------------------------------------------------------------------------------------- */
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_OFF)                                                                      /* COV_CANTP_EXCLUDED_FEATURES TX */
/**********************************************************************************************************************
  CanTp_RxGetBytesPerBlock()
**********************************************************************************************************************/
/*! \brief         Calculates the minimum size of a block
 *  \details       This function calculates the minimum number of bytes in the next block after a flow control frame.
 *                 This is needed to determine the flow status, depending on the available buffer size.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \return        Number of bytes in next block
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \config        This function is only available if CANTP_SINGLE_RX_BUFFER_OPTIMIZED = STD_OFF
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23066, DSGN-CanTp23300
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(PduLengthType, CANTP_CODE) CanTp_RxGetBytesPerBlock(CanTp_RxStatePtrType pTpRxState);
#endif

/**********************************************************************************************************************
  CanTp_RxGetBufferSF()
**********************************************************************************************************************/
/*! \brief         Handles buffer request for a received single frame
 *  \details       Request the upper layer to copy the payload data of a received single frame and finalize the connection.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23072
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferSF(CanTp_RxStatePtrType pTpRxState);

/**********************************************************************************************************************
  CanTp_RxGetBufferFF()
**********************************************************************************************************************/
/*! \brief         Handles buffer request for a received first frame
 *  \details       Request the upper layer to copy the payload data of a received first frame and trigger FC transmission.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23072
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFF(CanTp_RxStatePtrType pTpRxState);

/**********************************************************************************************************************
  CanTp_RxGetBufferCF()
**********************************************************************************************************************/
/*! \brief         Handles buffer request for a received consecutive frame
 *  \details       Request the upper layer to copy the payload data of received consecutive frame and continue Rx
 *                 processing depending on the buffer result and the current state.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23072
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferCF(CanTp_RxStatePtrType pTpRxState);

/**********************************************************************************************************************
  CanTp_RxGetBufferFCWait()
**********************************************************************************************************************/
/*! \brief         Handles buffer request after FC.WAIT
 *  \details       Continue processing of a delayed Rx connection depending on the buffer state.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23072
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFCWait(CanTp_RxStatePtrType pTpRxState);

/**********************************************************************************************************************
  CanTp_RxGetBuffer()
**********************************************************************************************************************/
/*! \brief         Handles buffer requests during reception
 *  \details       Request a new buffer (if needed) and dispatch processing depending on the frame type.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23072
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void,  CANTP_CODE) CanTp_RxGetBuffer(CanTp_RxStatePtrType pTpRxState);

/**********************************************************************************************************************
  CanTp_RxTransmitFrame()
**********************************************************************************************************************/
/*! \brief         Prepares transmission of an FC frame
 *  \details       Assemble flow control and trigger transmission.
 *  \param[in]     pTpRxState             Reference to Rx channel state object
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that pTpRxState references a valid and initialized channel state
 *  \trace         DSGN-CanTp23053, DSGN-CanTp23066, DSGN-CanTp23300
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxTransmitFrame(CanTp_RxStatePtrType pTpRxState);


/* --- Helper and Conversion Functions ----------------------------------------------------------------------------- */
/**********************************************************************************************************************
  CanTp_Util_MemCpy()
**********************************************************************************************************************/
/*! \brief         Copies data
 *  \details       Copy n bytes from source to destination
 *  \param[in]     pDest                  Destination pointer
 *  \param[in]     pSrc                   Source pointer
 *  \param[in]     Count                  Number of bytes to copy
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \pre           All parameters are expected to be valid and consistent (Count <= size of referenced arrays)
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_MemCpy(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest, P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) pSrc, uint16 Count);

#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
/**********************************************************************************************************************
  CanTp_Util_AssertLessEqual()
**********************************************************************************************************************/
/*! \brief         Assertion check against an upper limit
 *  \details       Assert that a given configuration parameter is <= a given upper limit
 *  \param[in]     CurrentValue      Parameter to be checked
 *  \param[in]     UpperLimit        Maximum allowed value of the parameter
 *  \return        TRUE      parameter value is in range
 *  \return        FALSE     parameter value exceeds the upper limit
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           -
 *  \note          This function is used to implement the countermeasures, which result from the silent analysis for SafeBSW.
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_AssertLessEqual(uint32 CurrentValue, uint32 UpperLimit);
#endif

/**********************************************************************************************************************
  CanTp_Util_CheckConfigValidity()
**********************************************************************************************************************/
/*! \brief         Verify correctness of certain configuration parameters
 *  \details       This function verifies the validity of configuration parameters, which may potentially violate freedom of interference
 *  \return        TRUE      all checked parameters are in range
 *  \return        FALSE     at least one parameter exceeds the defined limits
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           -
 *  \note          This function implements countermeasures, which result from the silent analysis for SafeBSW.
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_CheckConfigValidity(void);

#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
/**********************************************************************************************************************
  CanTp_Util_GetPaddingLength()
**********************************************************************************************************************/
/*! \brief         Returns the length of the payload of an N-PDU with applied padding settings
 *  \details       Calculate the final length the payload of an N-PDU after padding, depending on the current payload
 *                 length and the configuration.                 
 *  \param[in]     CurrentLength          Current length of the N-PDU's payload
 *  \param[in]     PaddingActivation      Padding Activation setting (enabled = TRUE, disabled = FALSE)
 *  \param[in]     CanType                Type of CAN communication (CAN2.0 or CAN-FD)
 *  \return        Length of the padded payload, or zero if length can't be determined
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if CANTP_PADDING_SUPPORT_REQUIRED = STD_ON
 *  \pre           -
 *  \trace         DSGN-CanTp23086
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_GetPaddingLength(uint8 CurrentLength, boolean PaddingActivation, CanTp_CanType CanType);
#endif


#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
/**********************************************************************************************************************
  CanTp_Util_RxAssembleSduMetadata()
**********************************************************************************************************************/
/*! \brief         Assembles the metadata of an Rx SDU und copies it to the passed destination
 *  \details       Assembles the metadata of an Rx SDU based on the passed addressing mode, data-PDU metadata and
 *                 data-PDU payload. The resulting metadata is then copied to the passed destination.        
 *  \param[in]     Addressing             Rx SDU's addressing mode.
 *  \param[in]     pPayloadInfo           PduInfo struct with data-PDU payload.
 *  \param[in]     pMetadataInfo          PduInfo struct with data-PDU metadata.
 *  \param[out]    pDest                  Pointer to a buffer of length CANTP_MAX_SDU_METADATA_LENGTH where the
 *                                        resulting metadata shall be copied.
 *  \param[out]    pLength                Pointer to the variable where the length of the resulting metadata shall be
 *                                        copied.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different pDest and different pLength
 *  \config        This function is only available if CANTP_GENERIC_CONNECTIONS = STD_ON.
 *  \pre           -
 *  \trace         DSGN-CanTpGenericConnections
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxAssembleSduMetadata(uint8 Addressing,
                                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo,
                                                                           P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest,
                                                                           P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pLength);

/**********************************************************************************************************************
  CanTp_Util_RxSduMetadataFromDataPduMatch()
**********************************************************************************************************************/
/*! \brief         Assembles the metadata of an Rx SDU and checks if it matches the metadata assigned to an RxState
 *  \details       Assembles the metadata of an Rx SDU based on the passed data-PDU metadata, data-PDU payload and the
 *                 addressing mode assigned to an RxState. The resulting metadata is then checked against the metadata
 *                 assigned to the RxState.
 *  \param[in]     pTpRxState             Reference to Rx channel state object. Shall not be NULL.
 *  \param[in]     pPayloadInfo           PduInfo struct with data-PDU payload.
 *  \param[in]     pMetadataInfo          PduInfo struct with data-PDU metadata.
 *  \return        TRUE      The assembled metadata and the metadata assigned to the RxState are the same.
 *  \return        FALSE     The assembled metadata and the metadata assigned to the RxState aren't the same.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if CANTP_GENERIC_CONNECTIONS = STD_ON.
 *  \pre           -
 *  \trace         DSGN-CanTpGenericConnections
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_RxSduMetadataFromDataPduMatch(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState,
                                                                                      P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                                      P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

/**********************************************************************************************************************
  CanTp_Util_TxSduMetadataFromFcPduMatch()
**********************************************************************************************************************/
/*! \brief         Assembles the metadata of a Tx SDU and checks if it matches the metadata assigned to a TxState
 *  \details       Assembles the metadata of a Tx SDU based on the passed fc-PDU metadata, fc-PDU payload and the
 *                 addressing mode assigned to a TxState. The resulting metadata is then checked against the metadata
 *                 assigned to the TxState.
 *  \param[in]     pTpTxState             Reference to Tx channel state object. Shall not be NULL.
 *  \param[in]     pPayloadInfo           PduInfo struct with fc-PDU payload.
 *  \param[in]     pMetadataInfo          PduInfo struct with fc-PDU metadata.
 *  \return        TRUE      The assembled metadata and the metadata assigned to the TxState are the same.
 *  \return        FALSE     The assembled metadata and the metadata assigned to the TxState aren't the same.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if CANTP_GENERIC_CONNECTIONS = STD_ON.
 *  \pre           -
 *  \trace         DSGN-CanTpGenericConnections
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_TxSduMetadataFromFcPduMatch(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState,
                                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

/**********************************************************************************************************************
  CanTp_Util_RxExtractSduMetadataInfo()
**********************************************************************************************************************/
/*! \brief         Assembles the metadata of an Rx SDU and assigns it to the passed RxState.
 *  \details       Assembles the metadata of an Rx SDU based on the passed data-PDU metadata, data-PDU payload and the
 *                 addressing mode assigned to an RxState. The resulting metadata is then assigned to the RxState.               
 *  \param[in,out] pTpRxState             Reference to Rx channel state object. Shall not be NULL.
 *  \param[in]     pPayloadInfo           PduInfo struct with data-PDU payload.
 *  \param[in]     pMetadataInfo          PduInfo struct with data-PDU metadata.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if CANTP_GENERIC_CONNECTIONS = STD_ON
 *  \pre           -
 *  \trace         DSGN-CanTpGenericConnections
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxExtractSduMetadataInfo(CanTp_RxStatePtrType pTpRxState,
                                                                              P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                              P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

/**********************************************************************************************************************
  CanTp_Util_TxExtractSduMetadataInfo()
**********************************************************************************************************************/
/*! \brief         Stores any passed Tx SDU metadata and based on it derives and stores any required data-PDU metadata.
 *  \details       -
 *  \param[in]     pTpTxState             Reference to Tx channel state object. Shall not be NULL.
 *  \param[in]     CanTpTxInfoPtr         Pointer to a PduInfo struct. The SduDataPtr member points to metadata if the
 *                                        Tx N-SDU has been configured with it.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if CANTP_GENERIC_CONNECTIONS = STD_ON
 *  \pre           -
 *  \note          The SduDataPtr member of CanTpTxInfoPtr shall not be used for Tx SDUs configured without metadata.
 *  \trace         DSGN-CanTpGenericConnections
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_TxExtractSduMetadataInfo(CanTp_TxStatePtrType pTpTxState,
                                                                              P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);
#endif

/**********************************************************************************************************************
  CanTp_Util_RxGetFCInPayloadAddressInfo()
**********************************************************************************************************************/
/*! \brief         Provides the addressing byte at the beginning of the payload of fc-PDUs in some addressing modes.
 *  \details       Provides the addressing byte to be placed at the beginning of the payload of fc-PDUs when extended,
 *                 mixed11 and mixed29 addressing modes are used. For generic connections, the byte could be part of
 *                 the metadata. For non-generic connections, the byte is part of the configuration.
 *  \param[in]     pTpRxState             Reference to Rx channel state object. Shall not be NULL.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if Rx SDUs with extended, mixed11 or mixed29 addressing exist.
 *  \pre           -
 *  \trace         DSGN-CanTp23083
 *********************************************************************************************************************/
# if ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))
# if ((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)))
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_RxGetFCInPayloadAddressInfo(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState);
# else
#  define CanTp_Util_RxGetFCInPayloadAddressInfo(pTpRxState)    CanTp_RxCfg_GetTxFcAddress((pTpRxState)->RxHdl)        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif
#endif


/**********************************************************************************************************************
  CanTp_Util_TxGetInPayloadAddressInfo()
**********************************************************************************************************************/
/*! \brief         Provides the addressing byte at the beginning of the payload of data-PDUs in some addressing modes.
 *  \details       Provides the addressing byte to be placed at the beginning of the payload of data-PDUs if extended,
 *                 mixed11 or mixed29 addressing modes are used. For generic connections, the byte could be part of
 *                 the metadata. For non-generic connections, the byte is part of the configuration.
 *  \param[in]     pTpTxState             Reference to Tx channel state object. Shall not be NULL.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if Tx SDUs with extended, mixed11 or mixed29 addressing exist.
 *  \pre           -
 *  \trace         DSGN-CanTp23083
 *********************************************************************************************************************/
#if ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))
# if (CANTP_GENERIC_CONNECTIONS == STD_ON)
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_TxGetInPayloadAddressInfo(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState);
# else
#  define CanTp_Util_TxGetInPayloadAddressInfo(pTpTxState)    CanTp_TxCfg_GetTxAddress((pTpTxState)->TxHdl)            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif
#endif

#if (CANTP_RX_HAS_HALF_DUPLEX == STD_ON)
/**********************************************************************************************************************
  CanTp_RxCheckChannelMode()
**********************************************************************************************************************/
/*! \brief         Performs Rx full/half duplex check
 *  \details       Depending on the configured ChannelMode, check if an Rx connection is allowed to be started.
 *  \param[in]     RxHdl                  Rx connection handle
 *  \return        E_OK                   Connection can be started
 *  \return        E_NOT_OK               Start of connection not allowed
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \config        This function is only available if any channel is configured as 'half duplex'
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that RxHdl is valid (< CanTp_Cfg_GetNumRxHdls)
 *  \trace         DSGN-CanTp24842
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_RxCheckChannelMode(PduIdType RxHdl);
#endif

#if (CANTP_TX_HAS_HALF_DUPLEX == STD_ON)
/**********************************************************************************************************************
  CanTp_TxCheckChannelMode()
**********************************************************************************************************************/
/*! \brief         Performs Tx full/half duplex check
 *  \details       Depending on the configured ChannelMode, check if a Tx connection is allowed to be started.
 *  \param[in]     TxHdl                  Tx connection handle
 *  \return        E_OK                   Connection can be started
 *  \return        E_NOT_OK               Start of connection not allowed
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \config        This function is only available if any channel is configured as 'half duplex'
 *  \pre           Expects that TxHdl is valid (< CanTp_Cfg_GetNumTxHdls)
 *  \trace         DSGN-CanTp24842
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxCheckChannelMode(PduIdType TxHdl);
#endif


/* --- Retrieve Functions for SduHdl ------------------------------------------------------------------------------- */
#if ((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON) || CANTP_GENERIC_CONNECTIONS == STD_ON)
/**********************************************************************************************************************
  CanTp_Cfg_GetSduHdlByRxPduOnly()
**********************************************************************************************************************/
/*! \brief         Returns the SduHdl which belongs to a given combination of RxPdu and FrameType
 *  \details       This function is used for standard and normal fixed addressing to find the SDU handle related to a
 *                 received N-PDU. It is also used to retrive the SDU handle of generic connections.
 *  \param[in]     RxPduId                RxPduId, received from the lower layer.
 *  \param[in]     FrameType              Received protocol byte, which indicates the frame type.
 *  \return        Tx connection handle if a flow control has been received, otherwise a Rx connection handle
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is available if generic connections are enabled or if the addressing modes standard or
 *                 normal fixed are available
 *  \pre           -
 *  \trace         DSGN-CanTp23090
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduOnly (PduIdType RxPduId, uint8 FrameType);
#endif

#if ((CANTP_SUPPORT_EXTENDED_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED11_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED29_ADDRESSING == STD_ON))
/**********************************************************************************************************************
  CanTp_Cfg_GetSduHdlByRxPduAddress()
**********************************************************************************************************************/
/*! \brief         Returns the SduHdl which belongs to a given combination of RxPdu, FrameType and Address
 *  \details       This function is used for extended or mixed11 addressing to find the Sdu handle for a received N-PDU.
 *  \param[in]     RxPduId                RxPduId, received from CanIf
 *  \param[in]     FrameType              Received protocol byte, which indicates the frame type
 *  \param[in]     Address                Received target address / address extension
 *  \return        Tx connection handle if a flow control has been received, otherwise a Rx connection handle
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \config        This function is only available if extended, mixed11 or mixed29 addressing formats are used.
 *  \pre           -
 *  \trace         DSGN-CanTp23090
 *********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduAddress (PduIdType RxPduId, uint8 FrameType, uint8 Address);
#endif


/* --- Channel Assignment Support Functions ------------------------------------------------------------------------- */
/**********************************************************************************************************************
  CanTp_RxGetFreeChannelPtr()
**********************************************************************************************************************/
/*! \brief         Return a pointer to an unsed channel state object
 *  \details       Search for a free Rx channel and assign it to a Rx connection (if needed). Metadata information is
 *                 also assigned to the Rx connection if required.
 *  \param[in]     RxHdl                  Rx connection handle
 *  \param[in]     pPayloadInfo           PduInfo struct with data-PDU payload.
 *  \param[in]     pMetadataInfo          PduInfo struct with data-PDU metadata.
 *  \return        pointer to the acquired state data, or NULL_PTR if there is no free channel for this RxHdl
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that RxHdl is valid (< CanTp_Cfg_GetNumRxHdls)
 *  \note          This function only returns a pointer to a FREE channel. A pointer to an active channel can be
                   retrieved through CanTp_RxGetActiveChannelPtr()
 *  \trace         DSGN-CanTp23317
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetFreeChannelPtr(PduIdType RxHdl,
                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo);

/**********************************************************************************************************************
  CanTp_RxGetActiveChannelPtr()
**********************************************************************************************************************/
/*! \brief         Return a pointer to an active channel state
 *  \details       Get a pointer to the Rx channel state which is used by the fiven RxHdl
 *  \param[in]     RxHdl                  Rx connection handle
 *  \return        pointer to the state data, or NULL_PTR if there is no active channel for this RxHdl
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that RxHdl is valid (< CanTp_Cfg_GetNumRxHdls)
 *  \note          This function only returns a pointer to an ACTIVE channel. A pointer to an free channel can be retrieved through CanTp_RxGetFreeChannelPtr()
 *  \trace         DSGN-CanTp23317
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetActiveChannelPtr(PduIdType RxHdl);

/**********************************************************************************************************************
  CanTp_TxGetFreeChannelPtr()
**********************************************************************************************************************/
/*! \brief         Return a pointer to an unsed channel state object
 *  \details       Search for a free Tx channel and assign it to a Tx connection (if needed)
 *  \param[in]     TxHdl                  Tx connection handle
 *  \param[in]     CanTpTxInfoPtr         Pointer to a PduInfo struct. The SduDataPtr member points to metadata if the
 *                                        Tx N-SDU has been configured with it.
 *  \return        pointer to the acquired state data, or NULL_PTR if there is no free channel for this TxHdl
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that TxHdl is valid (< CanTp_Cfg_GetNumTxHdls)
 *  \note          This function only returns a pointer to a FREE channel. A pointer to an active channel can be retrieved through CanTp_TxGetActiveChannelPtr()
 *  \trace         DSGN-CanTp23317
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetFreeChannelPtr(PduIdType TxHdl,
                                                                             P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);

/**********************************************************************************************************************
  CanTp_TxGetActiveChannelPtr()
**********************************************************************************************************************/
/*! \brief         Return a pointer to an active channel state
 *  \details       Get a pointer to the Tx channel state which is used by the given TxHdl
 *  \param[in]     TxHdl                  Tx connection handle
 *  \return        pointer to the state data, or NULL_PTR if there is no active channel for this TxHdl
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects that TxHdl is valid (< CanTp_Cfg_GetNumTxHdls)
 *  \note          This function only returns a pointer to an ACTIVE channel. A pointer to an free channel can be retrieved through CanTp_TxGetFreeChannelPtr()
 *  \trace         DSGN-CanTp23317
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetActiveChannelPtr(PduIdType TxHdl);


/* --- Tx Queue Functions ------------------------------------------------------------------------------------------ */
#if (CANTP_TRANSMIT_QUEUE == STD_ON)
/**********************************************************************************************************************
  CanTp_TxQueueProcess()
**********************************************************************************************************************/
/*! \brief         Triggers transmission of a queued N-PDU
 *  \details       Called cyclically and upon successful transmission of an N-PDU to transmit eventually pending requests.
 *  \param[in]     TxConfPduId            Tx N-PDU Id
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \config        This function is only available if CANTP_TRANSMIT_QUEUE = STD_ON.
 *  \pre           Expects to be called in a critical section
 *  \pre           Expects a valid TxConfPdu if (< CanTp_Cfg_GetNumTxConfPdus)
 *  \trace         DSGN-CanTp23320
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueProcess(PduIdType TxConfPduId);

/**********************************************************************************************************************
  CanTp_TxQueueCancel()
**********************************************************************************************************************/
/*! \brief         Cancels transmission of an N-PDU
 *  \details       When a transmission request have to be canceled, this function either removes the according N-PDU
 *                 from the queue (if it is queued) or releases the semaphore (if already passed to the CanIf).
 *  \param[in]     SduHdl                 Rx or Tx connection handle
 *  \param[in]     Direction              Rx or Tx
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \config        This function is only available if CANTP_TRANSMIT_QUEUE = STD_ON.
 *  \pre           Expects to be called in a critical section
 *  \pre           Depending on Direction, SduHdl is expected to be either
 *                 - a valid Rx handle (< CanTp_Cfg_GetNumRxHdls) or
 *                 - a valid Tx handle (< CanTp_Cfg_GetNumTxHdls)
 *  \trace         DSGN-CanTp23320
 *********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueCancel(PduIdType SduHdl, CanTp_DirectionType Direction);
#endif



/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  CanTp_Util_MemCpy()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_MemCpy(P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest,
                                                            P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) pSrc,
                                                            uint16 Count)
{
  uint16_least i;

  /* #10 copy [Count] number of bytes from [pSrc] to [pDest]. */
  for (i = 0; i < Count; i++)
  {
    pDest[i] = pSrc[i];                                                                                                /* SBSW_CANTP_MEMCPY_WRITE_DEST */
  }
} /* CanTp_Util_MemCpy() */



#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
/***********************************************************************************************************************
 *  CanTp_Util_AssertLessEqual()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_AssertLessEqual (uint32 CurrentValue, uint32 UpperLimit)
{
  boolean lResult;

  if (CurrentValue <= UpperLimit)
  {
    lResult = TRUE;
  }
  else
  {
    lResult = FALSE;
    CanTp_DetReportError(CANTP_SID_INIT, CANTP_E_PARAM_CONFIG)
  }
  return lResult;
} /* CanTp_Util_AssertLessEqual */
#endif



/***********************************************************************************************************************
 *  CanTp_Util_CheckConfigValidity()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_CheckConfigValidity(void)
{
  boolean lResult = TRUE;

#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
  boolean lTmp;
  PduIdType lSduId;
  PduIdType lSduHdl;

# if (CANTP_LOLAYERFCTS == STD_ON)
  CanTp_LoLayerFctsIterType lLoLayerIdx;
# endif

# if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                     /* COV_CANTP_ROBUSTNESS_CASE TX */
  /* --- Checks in Rx N-SDU Config Table --- */
  for (lSduId = 0; lSduId < CanTp_Cfg_GetNumRxSduIds(); lSduId++)
  {
    if (CanTp_RxSduSnvIsAvailable(lSduId))                                                                             /* COV_CANTP_POSTBUILD_DELETED TX */
    {
      lSduHdl = CanTp_RxGetSduHdlBySduId(lSduId);                                                                      /* PRQA S 2982 */ /* MD_CanTp_RedundantAssignment */
      /* #20 Assert countermeasure CM_CANTP_RXMAXPAYLOADLENGTH */
      lTmp = CanTp_Util_AssertLessEqual(CanTp_RxCfg_GetMaxPayload(lSduHdl), CANTP_MAX_PAYLOAD_LENGTH);
      if (lTmp == FALSE)                                                                                               /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
      {
        lResult = FALSE;                                                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }

      /* #30 Assert countermeasure CM_CANTP_RXCFG_TXFCCONFPDUIDS */
      if (CanTp_RxCfg_GetTAType(lSduHdl) == CANTP_TATYPE_PHYSICAL)                                                     /* PRQA S 2741 */ /* MD_CanTp_ExpressionAlwaysTrue */ /* COV_CANTP_ONLY_PHYSICAL TX */
      {
        lTmp = CanTp_Util_AssertLessEqual(CanTp_RxCfg_GetTxFcConfPduId(lSduHdl), (CanTp_Cfg_GetNumTxConfPdus() - (uint32)1));
        if (lTmp == FALSE)                                                                                             /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
        {
          lResult = FALSE;                                                                                             /* PRQA S 2880 */ /* MD_MSR_Unreachable */
        }
      }
    }
    /* else: N-SDU not active in current configuration; TCASE-21611 verifies, that it is never processed */
  }
# endif

# if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                     /* COV_CANTP_ROBUSTNESS_CASE TX */
  /* --- Checks in Tx N-SDU Config Table --- */
  for (lSduId = 0; lSduId < CanTp_Cfg_GetNumTxSduIds(); lSduId++)
  {
    if (CanTp_TxSduSnvIsAvailable(lSduId))                                                                             /* COV_CANTP_POSTBUILD_DELETED TX */
    {
      lSduHdl = CanTp_TxGetSduHdlBySduId(lSduId);                                                                      /* PRQA S 2983 */ /* MD_CanTp_RedundantAssignment */
      /* #50 Assert countermeasure CM_CANTP_TXMAXPAYLOADLENGTH */
      lTmp = CanTp_Util_AssertLessEqual(CanTp_TxCfg_GetMaxPayload(lSduHdl), CANTP_MAX_PAYLOAD_LENGTH);
      if (lTmp == FALSE)                                                                                               /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
      {
        lResult = FALSE;                                                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }

      /* #60 Assert countermeasure CM_CANTP_TXCFG_TXCONFPDUIDS */
      lTmp = CanTp_Util_AssertLessEqual(CanTp_TxCfg_GetTxConfPduId(lSduHdl), (CanTp_Cfg_GetNumTxConfPdus() - (uint32)1));
      if (lTmp == FALSE)                                                                                               /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
      {
        lResult = FALSE;                                                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }

      /* #70 Assert countermeasure CM_CANTP_TXMAXFRAMELENGTH */
# if (CANTP_SUPPORT_MULTIPLE_ADDRESSING == STD_ON)
      if (CanTp_TxGetAdrOffset(lSduHdl) == 0u)
      {
        lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)1), CANTP_MAX_FRAME_LENGTH);
        if (lTmp == FALSE)                                                                                             /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
        {
          lResult = FALSE;
        }
      }
      else
      {
        lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)2), CANTP_MAX_FRAME_LENGTH);
        if (lTmp == FALSE)                                                                                             /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
        {
          lResult = FALSE;
        }
      }
# else /* CANTP_MULTIPLE_ADDRESSING */
#  if ((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON))
      lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)1), CANTP_MAX_FRAME_LENGTH);
      if (lTmp == FALSE)                                                                                               /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
      {
        lResult = FALSE;                                                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }
#  else
      lTmp = CanTp_Util_AssertLessEqual((CanTp_TxCfg_GetMaxPayload(lSduHdl) + (uint32)2), CANTP_MAX_FRAME_LENGTH);
      if (lTmp == FALSE)                                                                                               /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
      {
        lResult = FALSE;                                                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      }
#  endif
# endif

    }
    /* else: N-SDU not active in current configuration; TCASE-21611 verifies, that it is never processed */
  }
# endif

  /* --- Check of sizes for dependent arrays --- */
  /* #80 Assert countermeasure CM_CANTP_RXARRAYSIZES */
# if (CANTP_CONSTANT_BS == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfCalcBS());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif
# if (CANTP_ENABLE_CHANGE_PARAM == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfDynFCParameters());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif
# if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfRxChannelMap());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfRxSduCfg(), CanTp_GetSizeOfRxState());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif

  /* #90 Assert countermeasure CM_CANTP_TXARRAYSIZES */
# if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfTxSduCfg(), CanTp_GetSizeOfTxChannelMap());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfTxSduCfg(), CanTp_GetSizeOfTxState());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif


  /* #100 Assert countermeasure CM_CANTP_TXCONFARRAYSIZES */
# if (CANTP_TRANSMIT_QUEUE == STD_ON)
  lTmp = CanTp_Util_AssertLessEqual(CanTp_GetSizeOfTxSemaphores(), CanTp_GetSizeOfTxQueue());
  if (lTmp == FALSE)                                                                                                   /* PRQA S 2992, 2996 */ /* MD_CanTp_CheckCfgExpressionAlwaysFalse, MD_CanTp_CheckCfgOperationAlwaysFalse */ /* COV_CANTP_SILENT_RUNTIME_CHECK XF */
  {
    lResult = FALSE;                                                                                                   /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif

  /* #105 Assert countermeasure CM_CANTP_LOLAYERTRANSMITFCT */
# if (CANTP_LOLAYERFCTS == STD_ON)
  for (lLoLayerIdx = 0; lLoLayerIdx < CanTp_GetSizeOfLoLayerFcts(); lLoLayerIdx++)
  {
    if (CanTp_GetTransmitFctOfLoLayerFcts(lLoLayerIdx) == NULL_PTR)
    {
      /* For the other checks the Det error is reported within the assert function */
      CanTp_DetReportError(CANTP_SID_INIT, CANTP_E_PARAM_CONFIG)
      lResult = FALSE;
    }
  }
# endif

#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */

  /* #107 Assert countermeasure CM_CANTP_MAXSDUMETADATALENGTH */
#if ((CANTP_GENERIC_CONNECTIONS == STD_ON) && (CANTP_MIXED29_ADDRESSING == STD_ON) && (CANTP_MAX_SDU_METADATA_LENGTH != 3))
# error "CANTP_MAX_SDU_METADATA_LENGTH must be 3 if generic connections and mixed29 addressing are enabled."
#elif ((CANTP_GENERIC_CONNECTIONS == STD_ON) && (CANTP_NORMALFIXED_ADDRESSING == STD_ON) && (CANTP_MAX_SDU_METADATA_LENGTH < 2))
# error "CANTP_MAX_SDU_METADATA_LENGTH must be at least 2 if generic connections and normal fixed addressing are enabled."
#elif ((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_EXTENDED_ADDRESSING == STD_ON) || (CANTP_MIXED11_ADDRESSING == STD_ON)) && (CANTP_MAX_SDU_METADATA_LENGTH < 1))
# error "CANTP_MAX_SDU_METADATA_LENGTH must be at least 1 if generic connections and extended/mixed11 addressing are enabled."
#endif

  /* #108 Assert countermeasure CM_CANTP_MAXPDUMETADATALENGTH */
#if ((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_MIXED29_ADDRESSING == STD_ON) || (CANTP_NORMALFIXED_ADDRESSING == STD_ON)) && (CANTP_MAX_PDU_METADATA_LENGTH != 2))
# error "CANTP_MAX_PDU_METADATA_LENGTH must be 2 if generic connections and mixed29/normal fixed addressing are enabled."
#endif

  return lResult;
} /* CanTp_Util_CheckConfigValidity */ /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */



#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
/***********************************************************************************************************************
 *  CanTp_Util_GetPaddingLength()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_GetPaddingLength(uint8 CurrentLength, boolean PaddingActivation, CanTp_CanType CanType)
{
  uint8 lPaddedLength;

  /* in case of an error: return length which is always invalid */
  lPaddedLength = 0;

  if (CurrentLength <= CANTP_CAN20_FRAME_LENGTH)                                                                       /* COV_CANTP_CONSTANT_PARAMETER */
  {
    /* classic CAN or 8 byte CAN-FD are treated the same way */
    if (PaddingActivation == FALSE)                                                                                    /* COV_CANTP_CONSTANT_PARAMETER */
    {
      /* no padding, use length as it is */
      lPaddedLength = CurrentLength;
    }
    else
    {
      /* extend to 8 byte */
      lPaddedLength = CANTP_CAN20_FRAME_LENGTH;
    }
  }
# if (CANTP_SUPPORT_CANFD == STD_ON)
  else
  {
    /* CAN-FD with more than 8 byte */
    if (CanType == CANTP_CANTYPE_CANFD)                                                                                /* COV_CANTP_CONSTANT_PARAMETER */
    {
      /* CAN-FD frames must be extended to one of the valid frame lengths */
      /* Padded length can be obtained using bit masking                  */

      /* Current Length |  Padded Length   | Bitmask */
      /* ---------------+------------------+-------- */
      /*   9 .... 12    | 12 = 0b0000 1100 |  0xFC   */
      /*   13 ... 16    | 16 = 0b0001 0000 |  0xFC   */
      /*   17 ... 20    | 20 = 0b0001 0100 |  0xFC   */
      /*   21 ... 24    | 24 = 0b0001 1000 |  0xFC   */
      /*   25 ... 32    | 32 = 0b0010 0000 |  0xF0   */
      /*   33 ... 48    | 48 = 0b0011 0000 |  0xF0   */
      /*   49 ... 64    | 64 = 0b0100 0000 |  0xF0   */

      /* the padded length is ... */
      if (CurrentLength <= 24u)
      {
        /* ... calculated by masking out the 2 lowest bits (0xFC) and incrementing bit 3 (0x04) */
        lPaddedLength = (uint8)(((uint8)(CurrentLength - 1u) & 0xFCu) + 0x04u);
      }
      else if (CurrentLength <= 64u)
      {
        /* ... calculated by masking out the 4 lowest bits (0xF0) and incrementing bit 5 (0x10) */
        lPaddedLength = (uint8)(((uint8)(CurrentLength - 1u) & 0xF0u) + 0x10u);
      }
      else
      {
        /* ... invalid; DLC > 64 is not supported */
      }
    }
    /* else: invalid configuration; DLC > 8 only allowed for N-PDUs which are configured as CAN FD! */
  }
# else
  CANTP_DUMMY_STATEMENT(CanType);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return lPaddedLength;
} /* CanTp_Util_GetPaddingLength() */
#endif /* CANTP_PADDING_SUPPORT_REQUIRED == STD_ON */


#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
/***********************************************************************************************************************
 *  CanTp_Util_RxAssembleSduMetadata()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxAssembleSduMetadata(uint8 Addressing,
                                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo,
                                                                           P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pDest,
                                                                           P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) pLength)
{
  CANTP_DUMMY_STATEMENT(pPayloadInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  CANTP_DUMMY_STATEMENT(pMetadataInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  switch (Addressing)
  {
# if ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON))
    case CANTP_ADDRESS_FORMAT_EXTENDED:
    case CANTP_ADDRESS_FORMAT_MIXED11:
      pDest[0] = pPayloadInfo->SduDataPtr[0];                                                                          /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST */
      *pLength = 1;                                                                                                    /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PLENGTH */
      break;
# endif

# if (CANTP_RX_HAS_NORMALFIXED_ADDRESSING == STD_ON)
    case CANTP_ADDRESS_FORMAT_NORMALFIXED:
      pDest[0] = pMetadataInfo->SduDataPtr[0];                                                                          /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST */
      pDest[1] = pMetadataInfo->SduDataPtr[1];                                                                          /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST */
      *pLength = 2;                                                                                                     /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PLENGTH */
      break;
# endif

# if (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)
    case CANTP_ADDRESS_FORMAT_MIXED29:
      pDest[0] = pMetadataInfo->SduDataPtr[0];                                                                          /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST */
      pDest[1] = pMetadataInfo->SduDataPtr[1];                                                                          /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST */
      pDest[2] = pPayloadInfo->SduDataPtr[0];                                                                           /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST */
      *pLength = 3;                                                                                                     /* SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PLENGTH */
      break;
# endif

    default:                                                                                                           /* COV_CANTP_DEFAULT_BRANCH */
      break;
  }
}


/***********************************************************************************************************************
 *  CanTp_Util_RxSduMetadataFromDataPduMatch()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_RxSduMetadataFromDataPduMatch(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState,
                                                                                      P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                                      P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo)
{
  boolean result = TRUE;
  uint8 lSduMetadataLength;
  uint8 lSduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];
  uint8_least i;

  /* #10 Assemble the Rx SDU metadata based on the passed addressing mode, data-PDU payload and data-PDU metadata. */
  CanTp_Util_RxAssembleSduMetadata(CanTp_RxCfg_GetAddressingFormat(pTpRxState->RxHdl), pPayloadInfo, pMetadataInfo,    /* SBSW_CANTP_RXASSEMBLESDUMETADATA_CALL_PTRS */
                                   lSduMetadata, &lSduMetadataLength);

  /* #20 If the assembled metadata doesn't match the metadata assigned to the passed RxState struct, return FALSE.
   *     Otherwise, return TRUE.
   */
  for (i = 0; i < pTpRxState->SduMetadataLength; i++)
  {
    if (pTpRxState->SduMetadata[i] != lSduMetadata[i])
    {
      result = FALSE;
      break;
    }
  }

  return result;
}


/***********************************************************************************************************************
 *  CanTp_Util_TxSduMetadataFromFcPduMatch()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(boolean, CANTP_CODE) CanTp_Util_TxSduMetadataFromFcPduMatch(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState,
                                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo)
{
  boolean result = TRUE;
  CANTP_DUMMY_STATEMENT(pPayloadInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  CANTP_DUMMY_STATEMENT(pMetadataInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* #10 If the Tx SDU currently assigned to the TxState has SDU metadata (the result has been set to TRUE): */
  if (pTpTxState->SduMetadataLength != 0u)
  {

# if (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)
    uint8_least i;
    uint8 lSduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];
# endif

    /* #15 Continue depending on the addressing mode of the Tx SDU currently assigned to the TxState: */
    switch (CanTp_TxCfg_GetAddressingFormat(pTpTxState->TxHdl))
    {

      /* #20 Extended Addressing:
       *       If the first byte of the fc-PDU payload doesn't match the configured TA:
       *          FALSE will be returned.
       */
# if (CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_EXTENDED:
        if (pPayloadInfo->SduDataPtr[0] != CanTp_TxCfg_GetRxFcAddress(pTpTxState->TxHdl))
        {
          result = FALSE;
        }
        break;
# endif

      /* #30 Mixed11 Addressing:
       *       If the first byte of the fc-PDU payload doesn't match the last (and only) byte of the SDU metadata (AE):
       *          FALSE will be returned.
       */
# if (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_MIXED11:
        if (pPayloadInfo->SduDataPtr[0] != pTpTxState->SduMetadata[pTpTxState->SduMetadataLength - 1u])
        {
          result = FALSE;
        }
        break;
# endif

      /* #40 Normal Fixed Addressing:
       *       Assemble the Tx SDU metadata, considering that in the fc-PDU metadata SA and TA are swapped.
       *       If the assembled metadata (SA and TA) doesn't match the metadata assigned to the passed TxState:
       *          FALSE will be returned.
       */
# if (CANTP_TX_HAS_NORMALFIXED_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_NORMALFIXED:
        lSduMetadata[0] = pMetadataInfo->SduDataPtr[1];                                                                /* SBSW_CANTP_TXSDUMETADATAMATCH_WRITE_LOCALBUFFER */
        lSduMetadata[1] = pMetadataInfo->SduDataPtr[0];                                                                /* SBSW_CANTP_TXSDUMETADATAMATCH_WRITE_LOCALBUFFER */

        for (i = 0; i < pTpTxState->SduMetadataLength; i++)
        {
          if (pTpTxState->SduMetadata[i] != lSduMetadata[i])
          {
            result = FALSE;
            break;
          }
        }

        break;
# endif

      /* #50 Mixed29 Addressing:
       *       Assemble the Tx SDU metadata, considering that in the fc-PDU metadata SA and TA are swapped.
       *       If the assembled metadata (SA, TA and AE) doesn't match the metadata assigned to the passed TxState:
       *          FALSE will be returned.
       */
# if (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)
      case CANTP_ADDRESS_FORMAT_MIXED29:
        lSduMetadata[0] = pMetadataInfo->SduDataPtr[1];                                                                /* SBSW_CANTP_TXSDUMETADATAMATCH_WRITE_LOCALBUFFER */
        lSduMetadata[1] = pMetadataInfo->SduDataPtr[0];                                                                /* SBSW_CANTP_TXSDUMETADATAMATCH_WRITE_LOCALBUFFER */
        lSduMetadata[2] = pPayloadInfo->SduDataPtr[0];                                                                 /* SBSW_CANTP_TXSDUMETADATAMATCH_WRITE_LOCALBUFFER */

        for (i = 0; i < pTpTxState->SduMetadataLength; i++)
        {
          if (pTpTxState->SduMetadata[i] != lSduMetadata[i])
          {
            result = FALSE;
            break;
          }
        }
        break;
# endif

      default:                                                                                                        /* COV_CANTP_DEFAULT_BRANCH */
        break;
    }
  }
  return result;
} /* CanTp_Util_TxSduMetadataFromFcPduMatch() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

/***********************************************************************************************************************
 *  CanTp_Util_RxExtractSduMetadataInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_RxExtractSduMetadataInfo(CanTp_RxStatePtrType pTpRxState,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo)
{
  CANTP_DUMMY_STATEMENT(pPayloadInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* #10 If the passed RxState struct has been assigned to a generic Rx SDU:
   *       Assemble and store the Rx SDU metadata based on the passed addressing mode, data-PDU payload and data-PDU metadata.
   */
  if (CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl)) {
    CanTp_Util_RxAssembleSduMetadata(CanTp_RxCfg_GetAddressingFormat(pTpRxState->RxHdl), pPayloadInfo, pMetadataInfo,   /* SBSW_CANTP_RXASSEMBLESDUMETADATA_CALL_PTRS */
      pTpRxState->SduMetadata, &pTpRxState->SduMetadataLength);
  }

  /* #20 If PDU metadata is present:
   *       Assemble the PDU metadata to be used when sending fc-PDUs, keeping in mind that SA and TA must be swapped.
   *     Otherwise, set the fc-PDU metadata length to 0;
   */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  if (pMetadataInfo->SduLength == CANTP_MAX_PDU_METADATA_LENGTH)
  {
    /* This branch corresponds to generic Rx SDUs with normal fixed or mixed29 addressing. */
    pTpRxState->FcPduMetadata[0] = pMetadataInfo->SduDataPtr[1];        /* Received TA used as SA */                   /* SBSW_CANTP_INTERN_WRITE_PDUMETADATA */
    pTpRxState->FcPduMetadata[1] = pMetadataInfo->SduDataPtr[0];        /* Received SA used as TA */                   /* SBSW_CANTP_INTERN_WRITE_PDUMETADATA */
    pTpRxState->FcPduMetadataLength = CANTP_MAX_PDU_METADATA_LENGTH;    /* 2 bytes */                                  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  }
  else
  {
    pTpRxState->FcPduMetadataLength = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  }
# endif
}

/***********************************************************************************************************************
 *  CanTp_Util_TxExtractSduMetadataInfos()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_Util_TxExtractSduMetadataInfo(CanTp_TxStatePtrType pTpTxState,
                                                                              P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr)
{

  /* #10 If the Tx SDU currently assigned to the TxState has SDU metadata: */
  if (CanTp_TxCfg_GetSduMetadataLength(pTpTxState->TxHdl) != 0u)
  {
    /* #15 Store the metadata passed by the upper layer. */
    pTpTxState->SduMetadataLength = CanTp_TxCfg_GetSduMetadataLength(pTpTxState->TxHdl);                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
    CanTp_Util_MemCpy(pTpTxState->SduMetadata, CanTpTxInfoPtr->SduDataPtr, pTpTxState->SduMetadataLength);             /* SBSW_CANTP_MEMCPY_CALL_TXSDUMETADATA */

    /* #20 If PDU metadata is enabled, continue depending on the addressing mode of the Tx SDU currently assigned to the TxState: */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
    switch (CanTp_TxCfg_GetAddressingFormat(pTpTxState->TxHdl))
    {

      /* #30 Extended Addressing or Mixed11 Addressing:
       *       Set the data-PDU metadata length to 0, since no metadata is passed to the lower layer.
       */
#  if ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON))
      case CANTP_ADDRESS_FORMAT_EXTENDED:
      case CANTP_ADDRESS_FORMAT_MIXED11:
        pTpTxState->DataPduMetadataLength = 0;                                                                         /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
        break;
#  endif 

      /* #40 Normal Fixed Addressing or Mixed29 Addressing:
       *       Assemble the data-PDU metadata, keeping in mind that SA and TA must not be swapped.
       */
#  if (CANTP_TX_HAS_NORMALFIXED_ADDRESSING)
      case CANTP_ADDRESS_FORMAT_NORMALFIXED:
#  endif
#  if (CANTP_TX_HAS_MIXED29_ADDRESSING)
      case CANTP_ADDRESS_FORMAT_MIXED29:
#  endif
        pTpTxState->DataPduMetadata[0] = pTpTxState->SduMetadata[0];                                                   /* SBSW_CANTP_INTERN_WRITE_PDUMETADATA */
        pTpTxState->DataPduMetadata[1] = pTpTxState->SduMetadata[1];                                                   /* SBSW_CANTP_INTERN_WRITE_PDUMETADATA */
        pTpTxState->DataPduMetadataLength = 2;                                                                         /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
        break;

      default:                                                                                                         /* COV_CANTP_DEFAULT_BRANCH */
        break;
    }
# endif
  }
}
#endif


#if ((CANTP_GENERIC_CONNECTIONS == STD_ON) && ((CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON)))
/***********************************************************************************************************************
 *  CanTp_Util_RxGetFCInPayloadAddressInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_RxGetFCInPayloadAddressInfo(P2CONST(CanTp_RxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpRxState)
{
  uint8 result;

  /* #10 If the passed RxState struct has been assigned to a generic Rx SDU and the addressing mode is not extended:
   *       Set result to the last byte of the Rx SDU metadata (AE is always in the last byte of the SDU metadata).
   *     Otherwise, set result to the configured TA.
   */
  if ((CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl))
# if (CANTP_RX_HAS_EXTENDED_ADDRESSING)
      && (CanTp_RxCfg_GetAddressingFormat(pTpRxState->RxHdl) != CANTP_ADDRESS_FORMAT_EXTENDED)
# endif
     )
  {
    result = pTpRxState->SduMetadata[pTpRxState->SduMetadataLength - 1u];
  }
  else
  {
    result = CanTp_RxCfg_GetTxFcAddress(pTpRxState->RxHdl);
  }

  return result;
}
#endif


#if ((CANTP_GENERIC_CONNECTIONS == STD_ON) && \
     ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON)))
/***********************************************************************************************************************
 *  CanTp_Util_TxGetInPayloadAddressInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_Util_TxGetInPayloadAddressInfo(P2CONST(CanTp_TxStateType, AUTOMATIC, CANTP_APPL_DATA) pTpTxState)
{
  uint8 result;

  /* #10 If the passed TxState struct has been assigned to a generic Tx SDU:
   *       Set result to the last byte of the Tx SDU metadata (TA or AE are always in the last byte of the metadata).
   *     Otherwise, set result to the configured TA or AE.
   */
  if (CanTp_TxCfg_GetSduMetadataLength(pTpTxState->TxHdl) != 0u)
  {
    /* The TA and AE are always in the last SDU metadata byte. */
    result = pTpTxState->SduMetadata[pTpTxState->SduMetadataLength - 1u];
  }
  else
  {
    result = CanTp_TxCfg_GetTxAddress(pTpTxState->TxHdl);
  }

  return result;
}
#endif

#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
/***********************************************************************************************************************
 *  CanTp_TxGetStminTimerFromStminValue()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(uint8, CANTP_CODE) CanTp_TxGetStminTimerFromStminValue(uint8 STminValue)
{
  uint8  lTaskCycles = 0;  /* initialize for burst mode */
  uint8  lSTminTemp  = STminValue;

  if (STminValue > CANTP_STMIN_MILLISEC_MAX)
  {
    /* valid value in the range of microseconds => use 1 task cycle */
    if ((STminValue >= CANTP_STMIN_MICROSEC_MIN) && (STminValue <= CANTP_STMIN_MICROSEC_MAX))                          /* COV_CANTP_RESERVED_STMIN */
    {
      lTaskCycles = 1;
      lSTminTemp  = 0;  /* don't calculated number of task cycles */
    }
    else
    {
      /* invalid value: use max STmin */
      lSTminTemp = CANTP_STMIN_MILLISEC_MAX;
      /* [ISO]: If an FC N_PDU message is received with a reserved ST parameter value, then the sending network entity
         shall use the longest ST value specified by this part of ISO 15765 (7F hex ... 127 ms) instead of the value
         received from the receiving network entity for the duration of the ongoing segmented message transmission. */
    }
  }
  /* else if STmin = 0: burst mode / no STmin, use initial value for number of task cycles */
  /* else if STmin > 0: valid value in the range of milliseconds, calculate number of task cycles directly from input */

  if (lSTminTemp != 0u)
  {
    lTaskCycles = (uint8)(((lSTminTemp + (CanTp_Cfg_GetTaskCycle() - 1u)) / CanTp_Cfg_GetTaskCycle()) + 1u);
  }

  return lTaskCycles;
} /* CanTp_TxGetStminTimerFromStminValue() */
#endif /* (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */


/***********************************************************************************************************************
 *  CanTp_CanIfRxIndicationSF()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationSF(CanTp_RxStatePtrType pTpRxState,
                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu)
{
  uint8                   lAddressingOffset;
  uint8                   lPayloadOffset;
  uint8                   lMinPayloadLength;
  uint8                   lMaxPayloadLength;
  PduLengthType           lReceivedDataLength;

  lAddressingOffset = CanTp_RxGetAdrOffset(pTpRxState->RxHdl);

  /* --- Read DataLength from SF --- */
  /* #10 Read 4Bit DataLength (standard single frame format). */
  lReceivedDataLength = ((PduLengthType)pPdu->SduDataPtr[lAddressingOffset] & CANTP_MASK_SF_LENGTH);

  /* prepare for length check */
  lPayloadOffset    = (uint8)(lAddressingOffset + CANTP_PCI_LENGTH_SF);   /* offset, so that SduDataPtr points to the first payload byte */
  lMinPayloadLength = 1;
  lMaxPayloadLength = CanTp_RxCfg_GetMaxPayloadSF(pTpRxState->RxHdl);

#if (CANTP_RX_HAS_CANFD == STD_ON)
  /* #20 If DataLength is 0 and CAN-FD is supported: use 8Bit DataLength instead (long single frame format). */
  /* Note: the case that a DLC > 8 is received for an N-PDU configured as CAN 2.0 is already detected        */
  /* during padding check (see CanTp_Util_GetPaddingLength), so no CAN-Type check is needed here.            */
  if (pPdu->SduLength > CANTP_CAN20_FRAME_LENGTH)
  {
    if (lReceivedDataLength == 0u)
    {
      /* valid Long Single Frame; get DataLength and adjust payload length and offset of length check */
      lReceivedDataLength = (PduLengthType)(pPdu->SduDataPtr[lAddressingOffset + 1u]);
      lPayloadOffset      = (uint8)(lAddressingOffset + CANTP_PCI_LENGTH_LSF);   /* offset, so that SduDataPtr points to the first payload byte */
      lMinPayloadLength   = (uint8)(CanTp_RxCfg_GetMaxPayloadSF(pTpRxState->RxHdl) + 1u);
      lMaxPayloadLength   = (uint8)CanTp_RxCfg_GetMaxPayloadLSF(pTpRxState->RxHdl);
    }
    else
    {
      /* else: if the network layer receives a SF where CAN_DL is greater than 8 and the low nibble of the */
      /* first PCI byte is not 0000 then the network layer shall ignore the received SF N_PDU.             */
      lMaxPayloadLength = 0u;
    }
  }
  /* else: standard single frame; proceed with initially retrieved values */
#endif

  /* --- Check data length and CAN frame length --- */
  if ( (lReceivedDataLength >= lMinPayloadLength) &&                                       /* min SF DL check   */
       (lReceivedDataLength <= lMaxPayloadLength) &&                                       /* max SF DL check   */
       ((pPdu->SduLength)   >= (PduLengthType)(lPayloadOffset +  lReceivedDataLength)) )   /* min CAN DLC check */
  {

    /* --- Check for already running connection --- */
    if (pTpRxState->ChannelState != CANTP_RXSTATE_IDLE)
    {
      /* #40 If channel is already active: terminate it. */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_UNEXP_PDU, CANTP_E_RX_RESTART, CANTP_RESET_BUT_KEEP_MAPPING);              /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
    }

    /* #50  Setup a new connection, call debugging call-out, inform PduR and pass the Rx SDU metadata if required. */
    pTpRxState->FrameType  = CANTP_FRAME_SF;                                                                           /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
    pTpRxState->DataLength = lReceivedDataLength;                                                                      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
    pTpRxState->PayloadLength = (uint8)pTpRxState->DataLength;                                                         /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
    CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&pTpRxState->Payload[0]),                             /* SBSW_CANTP_MEMCPY_CALL_PAYLOAD */
                      (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&pPdu->SduDataPtr[lPayloadOffset]),
                      (pTpRxState->PayloadLength) );

    CanTp_ApplRxSFIndication(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), pPdu)                                      /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */
    /* prepare for initial buffer request */
    pTpRxState->ProvidedBufferSize = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
    if (CanTp_RxCfg_PassSduMetadata(pTpRxState->RxHdl))
    {
      PduInfoType lPduInfo;
      lPduInfo.SduDataPtr = pTpRxState->SduMetadata;
      lPduInfo.SduLength  = pTpRxState->SduMetadataLength;

      pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */ /* SBSW_CANTP_PDURSTARTOFRECEPTION_CALL_RXSTATE */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                           &lPduInfo,
                                                           pTpRxState->DataLength,                        /* SduLength    */
                                                           &(pTpRxState->ProvidedBufferSize));            /* RxBufSizePtr */
    }
    else
#endif
    {
      pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */ /* SBSW_CANTP_PDURSTARTOFRECEPTION_CALL_RXSTATE */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                           NULL_PTR,
                                                           pTpRxState->DataLength,                        /* SduLength    */
                                                           &(pTpRxState->ProvidedBufferSize));            /* RxBufSizePtr */
    }

    /* #60  Continue depending on the buffer state returned by PduR: */
    switch(pTpRxState->BufferState)
    {
      /* #70  If buffer state is ok or busy: */
      case CANTP_BUFREQ_OK:
      case CANTP_BUFREQ_E_BUSY:
        /* #80 Prepare for buffer request to copy received data. */
        pTpRxState->Timer        = CanTp_RxCfg_GetNBr(pTpRxState->RxHdl); /* CANTP166 */                               /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
        pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_BUFFER_SF;                                                       /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

#if (CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)
        /* application has accepted the reception */
        pTpRxState->ApplState = (uint8)CANTP_APPL_INFORMED;                                                            /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#endif
        CanTp_RxGetBuffer_ISR(pTpRxState)                                                                              /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
        break;

      case CANTP_BUFREQ_E_NOT_OK:
      case CANTP_BUFREQ_E_OVFL:
      default:
        /* #100 Reset connection with buffer error. */
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                  /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
        break;
    } /* switch(BufferState) */
  }
  else
  {
    /* #110 If Length check failed: ignore received frame and release channel if no longer in use. */
    CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_INVALID_RX_LENGTH)
    if (pTpRxState->ChannelState == CANTP_RXSTATE_IDLE)
    {
      /* a new channel has been allocated for this SF; release it, but do not notify PduR */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NORESULT, CANTP_E_NO_ERROR, CANTP_RESET_ALL);                              /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
    }
    /* else: channel is already in use anyway; don't disturb it with an invalid frame */
  }
} /* CanTp_CanIfRxIndicationSF () */



/***********************************************************************************************************************
 *  CanTp_CanIfRxIndicationFF()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFF(CanTp_RxStatePtrType pTpRxState,
                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu)
{
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */

  uint8                   lAddressingOffset;
  uint8                   lPayloadOffset;
  uint8                   lMaxPayloadLen;
  uint16                  lDataLengthLowerLimit;
  PduLengthType           lReceivedDataLength;

  lAddressingOffset = CanTp_RxGetAdrOffset(pTpRxState->RxHdl);

  /* --- Check TA-Type --- */
# if (CANTP_RX_HAS_TATYPE_FUNCTIONAL == STD_ON)
  if (CANTP_TATYPE_FUNCTIONAL == CanTp_RxCfg_GetTAType(pTpRxState->RxHdl))
  {
    /* Don't accept functional FF in 1:n connections */
    CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NORESULT, CANTP_E_INVALID_TATYPE, CANTP_RESET_ALL);                          /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
  }
  /* #20 Otherwise: TA-Type is physical. */
  else
# endif
  {
    /* --- Read DataLength from FF --- */
    lReceivedDataLength = CanTp_Util_Make16Bit( (uint8)(pPdu->SduDataPtr[lAddressingOffset] & CANTP_MASK_FF_LENGTH),
                                                (uint8)(pPdu->SduDataPtr[lAddressingOffset + 1u]) );

# if (CANTP_SUPPORT_LONG_FF == STD_ON)
    /* #40 If DataLength is 0 and long FFs are supported: get 16Bit or 32Bit data length instead, depending on PduLengthType. */
    if (lReceivedDataLength == 0u)
    {
#  if (CANTP_SIZEOF_PDULENGTHTYPE < 4)
      /* PduLengthType is only uint16, the upper 16Bit of the received data length must be zero */
      if ((pPdu->SduDataPtr[lAddressingOffset + 2u] == 0u) &&
          (pPdu->SduDataPtr[lAddressingOffset + 3u] == 0u))
      {
        lReceivedDataLength = (PduLengthType)CanTp_Util_Make16Bit((uint8)(pPdu->SduDataPtr[lAddressingOffset + 4u]),
                                                                  (uint8)(pPdu->SduDataPtr[lAddressingOffset + 5u]));
      }
      else
      {
        /* 32Bit DL received, although PduLengthType is only uint16; set invalid data length to reject reception  */
        lReceivedDataLength = 0;
      }
#  else
      /* full 32Bit data length is supported */
      lReceivedDataLength = (PduLengthType)CanTp_Util_Make32Bit((uint8)(pPdu->SduDataPtr[lAddressingOffset + 2u]),
                                                                (uint8)(pPdu->SduDataPtr[lAddressingOffset + 3u]),
                                                                (uint8)(pPdu->SduDataPtr[lAddressingOffset + 4u]),
                                                                (uint8)(pPdu->SduDataPtr[lAddressingOffset + 5u]));
#  endif
      /* prepare length and offset variables for long FF */
      lDataLengthLowerLimit = CANTP_FF_DL_12BIT;                                     /* LFF data length must be greater than standard 12Bit FF DL */
      lMaxPayloadLen        = CanTp_RxCfg_GetMaxPayloadLFF(pTpRxState->RxHdl);
      lPayloadOffset        = (uint8) (lAddressingOffset + CANTP_PCI_LENGTH_LFF);    /* offset, so that SduDataPtr points to the first payload byte */
    }
    else
# endif
    {
      /* prepare length and offset variables for standard FF */
      lDataLengthLowerLimit = (uint16)(CanTp_RxCfg_GetMaxSFDataLength(pTpRxState->RxHdl, pPdu->SduLength));  /* FF data length must be greater than max single frame length */
      lMaxPayloadLen        = CanTp_RxCfg_GetMaxPayloadFF(pTpRxState->RxHdl);
      lPayloadOffset        = (uint8) (lAddressingOffset + CANTP_PCI_LENGTH_FF);   /* offset, so that SduDataPtr points to the first payload byte */
    }

    /* --- Check data length and CAN frame length --- */
    if ((lReceivedDataLength  > lDataLengthLowerLimit) &&                             /* min FF DL check   */
        (pPdu->SduLength     <= ((PduLengthType)lPayloadOffset + lMaxPayloadLen)) &&  /* CAN max DLC check */
        (pPdu->SduLength     >= CANTP_CAN20_FRAME_LENGTH))                            /* CAN min DLC check */
    {

      /* --- Check for already running connection --- */
      if (pTpRxState->ChannelState != CANTP_RXSTATE_IDLE)
      {
        /* #60 If channel is already active: terminate it. */
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_UNEXP_PDU, CANTP_E_RX_RESTART, CANTP_RESET_BUT_KEEP_MAPPING);            /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }

      /* #70  Setup a new connection, call debugging call-out inform PduR and pass the Rx SDU metadata if required. */
      pTpRxState->DataLength = lReceivedDataLength;                                                                    /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->FrameType  = CANTP_FRAME_FF;                                                                         /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ExpectedSN = CANTP_SN_FIRST_CF;   /* Wait for a CF with first SN */                                  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->DataIndex  = 0;                                                                                      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->WFTCounter = CanTp_RxCfg_GetWFTmax(pTpRxState->RxHdl);                                               /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

      /* copy payload data to internal buffer */
      pTpRxState->PayloadLength = (uint8)(pPdu->SduLength - lPayloadOffset);  /* actual payload may be less than max payload */                             /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->InitalDLC     = (uint8)pPdu->SduLength;                     /* FF DLC is needed for CF length consistency check (SWS_CanTp_00350) */      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->Payload[0]),                          /* SBSW_CANTP_MEMCPY_CALL_PAYLOAD */
                        (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pPdu->SduDataPtr[lPayloadOffset]),
                        (pTpRxState->PayloadLength) );

      CanTp_ApplRxFFIndication(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), pPdu)                                    /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */

      /* prepare for initial buffer request */
      pTpRxState->ProvidedBufferSize = 0;                                                                              /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
      if (CanTp_RxCfg_PassSduMetadata(pTpRxState->RxHdl))
      {
        PduInfoType lPduInfo;
        lPduInfo.SduDataPtr = pTpRxState->SduMetadata;
        lPduInfo.SduLength  = pTpRxState->SduMetadataLength;

        pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */  /* SBSW_CANTP_PDURSTARTOFRECEPTION_CALL_RXSTATE */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                             &lPduInfo,
                                                             pTpRxState->DataLength,                        /* SduLength    */
                                                             &(pTpRxState->ProvidedBufferSize));            /* RxBufSizePtr */
      }
    else
#endif
      {
        pTpRxState->BufferState = CanTp_PduRStartOfReception(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */  /* SBSW_CANTP_PDURSTARTOFRECEPTION_CALL_RXSTATE */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                             NULL_PTR, 
                                                             pTpRxState->DataLength,                        /* SduLength    */
                                                             &(pTpRxState->ProvidedBufferSize));            /* RxBufSizePtr */
      }

      /* #80  Depending on the buffer state returned by PduR, prepare FC transmission. */
      switch(pTpRxState->BufferState)
      {
        case CANTP_BUFREQ_OK:
          /* #90 If buffer state is ok: get buffer for FF (will lead to FC.CTS transmission). */
          pTpRxState->Timer         = CanTp_RxCfg_GetNBr(pTpRxState->RxHdl);                                           /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          pTpRxState->ChannelState  = CANTP_RXSTATE_WAIT_BUFFER_FF;                                                    /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

# if (CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)
          /* now the application is informed about a reception being in process */
          pTpRxState->ApplState     = (uint8)CANTP_APPL_INFORMED;                                                      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
# endif
# if (CANTP_CONSTANT_BS == STD_ON)
          /* reset stored block size so it is recalculated for this connection */
          CanTp_Data_CalcBS(pTpRxState->RxHdl) = 0;                                                                    /* SBSW_CANTP_INTERNAL_WRITE_CALCBS */
# endif
          CanTp_RxGetBuffer_ISR(pTpRxState)                                                                            /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
          break;

        case CANTP_BUFREQ_E_BUSY:
          /* #100 If buffer state is busy: transmit FC.WT. */
          pTpRxState->Timer         = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                           /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          pTpRxState->ChannelState  = CANTP_RXSTATE_TRANSMIT_FC_WT;                                                    /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
# if (CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)
          /* now the application is informed about a reception being in process */
          pTpRxState->ApplState     = (uint8)CANTP_APPL_INFORMED;                                                      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
# endif
          CanTp_RxTransmitFrame_ISR(pTpRxState)                                                                        /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
          break;

        case CANTP_BUFREQ_E_OVFL:
          /* #110 If buffer state is overflow: transmit FC.OVFL. */
          pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                            /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_OVFL;                                                   /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          CanTp_RxTransmitFrame_ISR(pTpRxState)                                                                        /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
          break;

        case CANTP_BUFREQ_E_NOT_OK:
        default:
          /* #120 Any other buffer state: reset connection with buffer error. */
          CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
          break;
      } /* switch(BufferState */
    }

    /* #130 If length check failed: ignore frame and release channel if no longer in use. */
    else
    {
      CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_INVALID_RX_LENGTH)
      if (pTpRxState->ChannelState == CANTP_RXSTATE_IDLE)
      {
        /* a new channel has been allocated for this FF; release it, but do not notify PduR */
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NORESULT, CANTP_E_NO_ERROR, CANTP_RESET_ALL);                            /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      /* else: channel is already in use anyway; don't disturb it with an invalid frame */
    }
  }

#else
CANTP_DUMMY_STATEMENT(pTpRxState);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
CANTP_DUMMY_STATEMENT(pPdu);         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
} /* CanTp_CanIfRxIndicationFF() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */



/***********************************************************************************************************************
 *  CanTp_CanIfRxIndicationCF()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationCF(CanTp_RxStatePtrType pTpRxState,
                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu)
{
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */

  uint8                   lAddressingOffset;
  uint8                   lPayloadOffset;
  uint8                   lSNinFrame;

  lAddressingOffset = CanTp_RxGetAdrOffset(pTpRxState->RxHdl);

  /* #10 If a CF is received before the TxConfirmation of the previous FC.CTS: */
  if (pTpRxState->ChannelState == CANTP_RXSTATE_WAIT_TXCONFFC_CTS)
  {
    /* #20 Release semaphore and trigger confirmation of FC. */
# if (CANTP_TRANSMIT_QUEUE == STD_ON)
    CanTp_TxQueueCancel(pTpRxState->RxHdl, CANTP_DIR_RX);                                                              /* SBSW_CANTP_TXQUEUCANCEL_CALL_RX */
# else
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl) ).Handle    = CANTP_INVALID_HDL;           /* SBSW_CANTP_CANIFRXINDICATIONCF_WRITE_TXSEMAPHORE */
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl) ).Direction = CANTP_DIR_NONE;              /* SBSW_CANTP_CANIFRXINDICATIONCF_WRITE_TXSEMAPHORE */
    CanTp_CanIfCancelTransmit(CANTP_DIR_RX, pTpRxState->RxHdl, CanTp_RxCfg_GetLoLayerTxFcPduId(pTpRxState->RxHdl));
# endif
    CanTp_CanIfTxConfirmationFC(pTpRxState); /* mark FC as confirmed */                                                /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
  }

  /* #30 If CF is expected: */
  if (pTpRxState->ChannelState == CANTP_RXSTATE_WAIT_CF)
  {
    uint8 lErrorId = CANTP_E_INVALID_RX_LENGTH;

    pTpRxState->FrameType     = CANTP_FRAME_CF;                                                                        /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
    lSNinFrame                = (uint8)(pPdu->SduDataPtr[lAddressingOffset] & CANTP_PCI_SN_MASK);

    /* --- Get payload length and check DLC --- */
    /*  ISO15765-2 / SWS_CanTp_00350:
     *  Due to the fact that the TX_DL configuration of the sending node is not known by the receiver, the receiving
     *  node shall always adapt to the settings of the sender.
     *  CAN_DL shall be considered correct if the [FF] RX_DL value matches RX_DL for all CF's except for the last
     *  (or only) CF. The last (or only) CF shall pass this check if CAN_DL is less than RX_DL.
     */
    lPayloadOffset            = (uint8)(lAddressingOffset + CANTP_PCI_LENGTH_CF); /* offset, so that SduDataPtr points to the first payload byte */
    pTpRxState->PayloadLength = (uint8)(pTpRxState->InitalDLC - lPayloadOffset);  /* assume valid CF DLC which matches the FF DLC */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

    if (pTpRxState->PayloadLength <= (pTpRxState->DataLength - pTpRxState->DataIndex))
    {
      /* not the last CF: DLC must match with the DLC of the FF */
      if (pPdu->SduLength == pTpRxState->InitalDLC)
      {
        /* CF DLC check passed */
        lErrorId = CANTP_E_NO_ERROR;
      }
    }
    else
    {
      /* last CF: reduce expected payload */
      pTpRxState->PayloadLength = (uint8)(pTpRxState->DataLength - pTpRxState->DataIndex);                             /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

      if (pPdu->SduLength >= ((PduLengthType)pTpRxState->PayloadLength + lPayloadOffset))
      {
        /* min DLC check passed */
        lErrorId = CANTP_E_NO_ERROR;
      }
    }

    if (lErrorId != CANTP_E_NO_ERROR)
    {
      /* #50 If DLC check failed: ignore frame and report DET error. */
      CanTp_DetReportError(CANTP_SID_RXINDICATION, lErrorId)
    }

    /* --- Check SN --- */
    else if (lSNinFrame != (uint8)(pTpRxState->ExpectedSN))
    {
      /* #70 In case of a wrong SN, reset connection. */
# if (CANTP_IGNORE_CF_WITH_WRONG_SN != STD_ON)                                                                         /* COV_CANTP_EXCLUDED_FEATURES TX */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_WRONG_SN, CANTP_E_RX_INVALID_SN, CANTP_RESET_ALL);                         /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
# endif
    }
    else
    {
      /* #80 If the SN is correct, call debugging call-out, copy payload to internal buffer and prepare for buffer request. */
      pTpRxState->ExpectedSN = (uint8)((pTpRxState->ExpectedSN + 1u) & CANTP_PCI_SN_MASK);                             /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_ApplRxCFIndication(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), pPdu)                                    /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */

      /* --- Copy payload and request buffer --- */
      CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pTpRxState->Payload[0]),                          /* SBSW_CANTP_MEMCPY_CALL_PAYLOAD */
                        (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (&pPdu->SduDataPtr[lPayloadOffset]),
                        (pTpRxState->PayloadLength) );

# if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                      /* COV_CANTP_EXCLUDED_FEATURES XF */
      /* validity of buffer size already checked after first frame */
      pTpRxState->BufferState = CANTP_BUFREQ_OK;                                                                       /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
# else
      if (pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)
      {
        /* enough buffer available, just request to copy data */
        pTpRxState->BufferState = CANTP_BUFREQ_OK;                                                                     /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      }
      else
      {
        /* buffer insufficient for this CF; a new buffer must be requested */
        pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;                                                                 /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      }
# endif

      pTpRxState->Timer        = CanTp_RxCfg_GetNCr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_BUFFER_CF;                                                         /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_RxGetBuffer_ISR(pTpRxState)                                                                                /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
    }
  }
  /* else: channel is not waiting for CF; ignore frame */

#else
CANTP_DUMMY_STATEMENT(pTpRxState);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
CANTP_DUMMY_STATEMENT(pPdu);         /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
} /* CanTp_CanIfRxIndicationCF() */



/***********************************************************************************************************************
 *  CanTp_CanIfRxIndicationFC()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_CanIfRxIndicationFC(CanTp_TxStatePtrType pTpTxState,
                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPdu)
{
  uint8 lAddressingOffset = CanTp_TxGetAdrOffset(pTpTxState->TxHdl);

  /* #10 If the FC is received before the TxConfirmation of the FF or the last CF in block: */
  if (  (pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_TXCONF_FF ) ||                                        /* FC received before Tx confirmation of FF */
       ((pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_TXCONF_CF) && (pTpTxState->BlocksizeCounter == 1u)) )  /* FC received before Tx confirmation of last CF in block */
  {
    /* #20 Copy frame to internal buffer and exit. */
    pTpTxState->FCLength = CANTP_PCI_LENGTH_FC + lAddressingOffset;                                                    /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
    CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pTpTxState->FCData),                                 /* SBSW_CANTP_MEMCPY_CALL_FCDATA */
                      (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA)) (pPdu->SduDataPtr),
                      (pTpTxState->FCLength) );
    /* Note: if this is not the first flow control which have been received before TxConfirmation, the previous
     * FC is overwritten. As multiple FCs may only be received for FC.WT, this is acceptable (latest is best) */
  }
  else
  {
    /* #30 If channel is waiting for a flow control: */
    if (pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_FC)
    {
      /* #40 Check length of received frame. */
      if (pPdu->SduLength >= ((PduLengthType)CANTP_PCI_LENGTH_FC + lAddressingOffset))
      {
        /* #50 If length check passed: continue according to received flow status. */
        switch(pPdu->SduDataPtr[lAddressingOffset] & CANTP_MASK_FS)
        {
          /* --- Received FC.CTS --- */
          case CANTP_FLOWSTATUS_CTS:
#if (CANTP_USE_ONLY_FIRST_FC == STD_ON)
            /* #70 If only the first FC shall be used and this is not the first FC: */
            if (pTpTxState->FirstFCReceived == TRUE)
            {
              /* #80 Use BS and STmin of initially received FC. */
              pTpTxState->BlocksizeCounter = pTpTxState->BS;                                                           /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
              /* pTpTxState->STmin already contains the correct value and don't have to be changed */
            }
            else
#endif /* CANTP_USE_ONLY_FIRST_FC */
            {
              /* #90 If all FCs shall be evaluated, or if only the first shall be used and this is the first FC: */
#if (CANTP_MODIFIED_RES_STMIN_HANDLING == STD_ON)
              /* #100 If STmin is reserved and modified handling of reserved STmins is enabled: */
              uint8 lTempSTmin;
              lTempSTmin = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_STMIN];

              if ( ((lTempSTmin > CANTP_STMIN_MILLISEC_MAX) && (lTempSTmin < CANTP_STMIN_MICROSEC_MIN)) ||
                    (lTempSTmin > CANTP_STMIN_MICROSEC_MAX) )
              {
# if (CANTP_REJECT_FC_WITH_RES_STMIN == STD_ON)                                                                        /* COV_CANTP_MODIFIED_STMIN_HANDLING TX */
                /* #110 Reset connection if reserved STmins shall be rejected, otherwise ignore received FC and exit. */
                CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NOT_OK, CANTP_E_TX_RES_STMIN);                                   /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
# endif
                break;          /* PRQA S 3333 */ /* MD_CanTp_3333 */
              }
#endif /* CANTP_MODIFIED_RES_STMIN_HANDLING */

              /* #120 Get BS and STmin of the received FC. */
              pTpTxState->STmin            = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_STMIN];    /* current STmin    */  /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
              pTpTxState->BlocksizeCounter = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_BS];       /* current BS       */  /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#if (CANTP_USE_ONLY_FIRST_FC == STD_ON)
              pTpTxState->BS               = pPdu->SduDataPtr[lAddressingOffset + CANTP_FRAME_OFFSET_FC_BS];       /* store initial BS */  /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
              pTpTxState->FirstFCReceived  = TRUE;                                                                                         /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#endif /* CANTP_USE_ONLY_FIRST_FC */
            }

            /* #130 Prepare for transmission of next CF by loading STmin counter and requesting payload buffer. */
            pTpTxState->Timer           = CanTp_TxCfg_GetNCs(pTpTxState->TxHdl);    /* CANTP167 */                     /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
            pTpTxState->ChannelState    = CANTP_TXSTATE_WAIT_BUFFER_CF;                                                /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
            CanTp_TxGetBuffer_ISR(pTpTxState)                                                                          /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
            break; /* FC.CTS */


          /* --- Received FC.WT --- */
          case CANTP_FLOWSTATUS_WT:
            /* #150 Only reload timer and keep waiting for flow controls. */
            pTpTxState->Timer = CanTp_TxCfg_GetNBs(pTpTxState->TxHdl);                                                 /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
            break; /* FC.WT */


          /* --- Received FC.OVFL --- */
#if (CANTP_IGNORE_FC_OVFL_INVALID_FS == STD_ON)                                                                        /* COV_CANTP_EXCLUDED_FEATURES XF */
          case CANTP_FLOWSTATUS_OVFL:
          default:
            /* Ignore FC */
            break;
#else
          case CANTP_FLOWSTATUS_OVFL:
            /* #170 Only if FC.OVFL shall not be ignored, reset connection with buffer error. */
            CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_TX_FC_OVFL);                                      /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
            break; /* FC.OVFL */

          /* #180 Any other flow status: */
          default:
            /* #190 Only if an invalid FS shall not be ignored, reset connection. */
            CanTp_TxInit(pTpTxState, CANTP_NOTIFY_INVALID_FS, CANTP_E_TX_INVALID_FS);                                  /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
            break;
#endif
        } /* switch(FlowStatus) */
      }
      /* #200 If length check failed, report DET error. */
      else
      {
        CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_INVALID_RX_LENGTH)
      }
    }
    /* else: unexpected FC, Ignore ! */
  }
} /* CanTp_CanIfRxIndicationFC() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
 *  CanTp_TxStartConnection()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxStartConnection(PduIdType TxSduSnv,
                                                                            PduIdType TxHdl,
                                                                            PduLengthType SduLength,
                                                                            P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr)
{
  CanTp_TxStatePtrType pTpTxState;
  Std_ReturnType       lReturnValue;

  lReturnValue = E_NOT_OK;
  CANTP_DUMMY_STATEMENT(TxSduSnv);                                                                                     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* --- Get Pointer to Channel --- */
  /* #10 Try to get a free channel. */
  pTpTxState = CanTp_TxGetFreeChannelPtr(TxHdl, CanTpTxInfoPtr);                                                       /* SBSW_CANTP_TXGETFREECHANNEL_CALL_PTR */

  /* #30 If a free channel is available: */
  if (pTpTxState != NULL_PTR)
  {
    lReturnValue = E_OK;
#if (CANTP_STMIN_BY_APPL == STD_ON)
    pTpTxState->TxSduSnv = TxSduSnv;                                                                                   /* SBSW_CANTP_TXSTART_WRITE_TXSTATE */
#endif

    /* #40  Check if transmission is segmented and accordingly set the ChannelState to get a buffer for SF or FF. */
    if (SduLength > CanTp_TxCfg_GetMaxSFDataLength(TxHdl))
    {
      /* multi frame is needed */
      pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_FF;                                                         /* SBSW_CANTP_TXSTART_WRITE_TXSTATE */

      /* #50 For segmented transmissions, also check the TA type. */
#if (CANTP_TX_HAS_TATYPE_FUNCTIONAL == STD_ON)
      if (CanTp_TxCfg_GetTAType(TxHdl) == CANTP_TATYPE_FUNCTIONAL)
      {
        /* #60 If TA type is functional, abort setting up the transmission and return E_NOT_OK. */
        CanTp_TxInit(pTpTxState, CANTP_NOTIFY_UNEXP_PDU, CANTP_E_INVALID_TATYPE);                                      /* SBSW_CANTP_TXSTART_CALL_TXSTATE */
        lReturnValue = E_NOT_OK;
      }
#endif
      /* else: physical multi frame connection; proceed with processing */
    }
    else
    {
      /* single frame sufficient */
      pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_SF;                                                         /* SBSW_CANTP_TXSTART_WRITE_TXSTATE */
    }
  }
  /* else: channel busy or no more channels available */


  /* --- Trigger Transmission of SF / FF --- */
  if (lReturnValue == E_OK)
  {
    /* #70 Prepare for buffer request and SF/FF transmission and return E_OK. */
    pTpTxState->DataIndex   = 0;                                                                                       /* SBSW_CANTP_TXSTART_WRITE_TXSTATE */
    pTpTxState->DataLength  = SduLength;                                                                               /* SBSW_CANTP_TXSTART_WRITE_TXSTATE */
    pTpTxState->Timer       = CanTp_TxCfg_GetNCs(TxHdl);   /* CANTP167 */                                              /* SBSW_CANTP_TXSTART_WRITE_TXSTATE */

#if (CANTP_SYNC_TRANSMIT == STD_ON)
    /* #80 Only when synchronous transmission is used, immediately get a buffer in order to transmit SF / FF. */
    CanTp_TxGetBuffer(pTpTxState);                                                                                     /* SBSW_CANTP_TXSTART_CALL_TXSTATE */
#else
    /* buffer provision and frame transmission is done asynchronously on task level (CANTP176) */
#endif
  }
  /* else: channel busy or not available, or request was a functional multi frame */

  return lReturnValue;
} /* CanTp_TxStartConnection() */



#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_OFF)                                                                      /* COV_CANTP_EXCLUDED_FEATURES TX */
/***********************************************************************************************************************
 *  CanTp_RxGetBytesPerBlock()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(PduLengthType, CANTP_CODE) CanTp_RxGetBytesPerBlock(CanTp_RxStatePtrType pTpRxState)           /* PRQA S 3673 */ /* MD_CanTp_3673 */
{
  PduLengthType           lBytesPerBlock;

  /* assume that block size can be adjusted, so a block has at least the size of one CF */
  lBytesPerBlock = (PduLengthType)CanTp_RxCfg_GetMaxPayloadCF(pTpRxState->RxHdl);

# if (CANTP_CONSTANT_BS == STD_ON)
  if (pTpRxState->FrameType != CANTP_FRAME_FF)
  {
    /* not the first block: same block size as calculated for first FC.CTS must be used */
    lBytesPerBlock = (PduLengthType)(lBytesPerBlock * CanTp_Data_CalcBS(pTpRxState->RxHdl));
  }
# endif

  /* reduce size for last block */
  if (lBytesPerBlock > (pTpRxState->DataLength - pTpRxState->DataIndex))
  {
    lBytesPerBlock = pTpRxState->DataLength - pTpRxState->DataIndex;
  }

  return lBytesPerBlock;
} /* CanTp_RxGetBytesPerBlock() */
#endif /* CANTP_SINGLE_RX_BUFFER_OPTIMIZED != STD_ON */



/***********************************************************************************************************************
 *  CanTp_RxGetBufferSF()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferSF(CanTp_RxStatePtrType pTpRxState)
{
  PduInfoType             lPduInfo;

  /* #10 If buffer state is valid and buffer size is sufficient for received payload: */
  if ((pTpRxState->BufferState == CANTP_BUFREQ_OK) && (pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength))
  {
    /* #20 Request PduR to copy the received data. */
    lPduInfo.SduLength  = pTpRxState->PayloadLength;
    lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
    pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */   /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                   &lPduInfo,                                     /* PduInfoPtr   */
                                                   &pTpRxState->ProvidedBufferSize);              /* RxBufSizePtr */

    /* #30 If request succeeded: reception finished, reset connection without error. */
    if (pTpRxState->BufferState == CANTP_BUFREQ_OK)
    {
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);                                    /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
    }
    /* #40 Otherwise, reset connection with buffer error. */
    else
    {
      /* CopyRxData failed; reset connection and notify application */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                    /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
    }
  }
#if (CANTP_FAULT_TOLERANT_RXBUFFER == STD_ON)                                                                          /* COV_CANTP_EXCLUDED_FEATURES XF */
  /* #50 If buffer state is ok but buffer size is not sufficient: */
  else if (pTpRxState->BufferState == CANTP_BUFREQ_OK)
  {
    /* #60 If fault tolerant buffer handling is used, proceed as for busy buffer state, otherwise as for invalid buffer state. */
    pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;                                                                     /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  }
#endif
  /* #70 If buffer state is busy: do nothing and retry to get a buffer on task level. */
  else if (pTpRxState->BufferState == CANTP_BUFREQ_E_BUSY)
  {
    /* buffer is busy: retry on task level */
  }
  /* #80 If buffer state is invalid: reset connection with buffer error. */
  else
  {
    /* buffer not large enough or invalid */
    CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                      /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
  }
} /* CanTp_RxGetBufferSF() */



/***********************************************************************************************************************
 *  CanTp_RxGetBufferFF()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFF(CanTp_RxStatePtrType pTpRxState)
{
  PduInfoType             lPduInfo;

  /* --- Request to copy payload --- */
  /* Note: buffer status is here always OK; all other values are already handled after call to StartOfReception */
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                       /* COV_CANTP_EXCLUDED_FEATURES XF */
  /* buffer must be sufficient for complete message */
  if (pTpRxState->ProvidedBufferSize >= pTpRxState->DataLength)
#else
  /* buffer must be sufficient for stored FF */
  if (pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)
#endif
  {
    /* #20  Request PduR to copy the received data and update buffer state with the result. */
    lPduInfo.SduLength  = pTpRxState->PayloadLength;
    lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
    pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl),  /* CanTpRxPduId */  /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                   &lPduInfo,                                      /* PduInfoPtr   */
                                                   &pTpRxState->ProvidedBufferSize);               /* RxBufSizePtr */
  }
  else
  {
#if (CANTP_FAULT_TOLERANT_RXBUFFER == STD_ON)                                                                          /* COV_CANTP_EXCLUDED_FEATURES XF */
    /* buffer is insufficient: send FC.WAIT and retry later */
    pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;                                                                     /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#else
    /* buffer is insufficient: terminate reception */
    pTpRxState->BufferState = CANTP_BUFREQ_E_NOT_OK;                                                                   /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#endif
  }

  /* --- Handle result of copy / buffer request and determine FC to be sent --- */
  switch (pTpRxState->BufferState)
  {
    case CANTP_BUFREQ_OK:
      /* #60 If buffer state is ok: data of FF has been copied successfully, update data counters. */
      pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + pTpRxState->PayloadLength);                      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->PayloadLength = 0;                                                                                   /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */


      /* #70 If buffer size is sufficient for one block, trigger transmission of FC.CTS, otherwise of FC.WAIT. */
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                       /* COV_CANTP_EXCLUDED_FEATURES XF */
      /* buffer assumed to be always sufficient; transmit FC.CTS */
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                                        /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#else
      {
        PduLengthType  lBytesPerBlock;
        lBytesPerBlock = CanTp_RxGetBytesPerBlock(pTpRxState);                                                         /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */

        /* check for FC.WT or FC.CTS */
        if (pTpRxState->ProvidedBufferSize >= lBytesPerBlock)
        {
          /* buffer sufficient for one or last CF; transmit FC.CTS */
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                                    /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
        }
        else
        {
          /* buffer not sufficient for next CF; transmit FC.WT */
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;                                                     /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
        }
      }
#endif /* CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON */

      /* transmit FC */
      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_RxTransmitFrame(pTpRxState);                                                                               /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    case CANTP_BUFREQ_E_BUSY:
      /* #90 Trigger transmission of FC.WAIT. */
      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;                                                         /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_RxTransmitFrame(pTpRxState);                                                                               /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    case CANTP_BUFREQ_E_OVFL:
      /* #110 Trigger transmission of FC.OVFL. */
      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_OVFL;                                                       /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_RxTransmitFrame(pTpRxState);                                                                               /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    case CANTP_BUFREQ_E_NOT_OK:
    default:
      /* #120 Any other buffer state: reset connection without sending a flow control. */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                    /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;
  } /* switch(BufferState) */
} /* CanTp_RxGetBufferFF() */



/***********************************************************************************************************************
 *  CanTp_RxGetBufferCF()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferCF(CanTp_RxStatePtrType pTpRxState)
{
  PduInfoType             lPduInfo;

  /* --- check buffer state and copy received payload --- */
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                       /* COV_CANTP_EXCLUDED_FEATURES XF */
  /* buffer assumed to be sufficient: copy received payload of CF */
  lPduInfo.SduLength  = pTpRxState->PayloadLength;
  lPduInfo.SduDataPtr = &(pTpRxState->Payload[0]);
  pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl),  /* CanTpRxPduId */    /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                 &lPduInfo,                                      /* PduInfoPtr   */
                                                 &pTpRxState->ProvidedBufferSize);               /* RxBufSizePtr */
#else
  /* #10 If buffer state is sufficient for received payload: */
  if (pTpRxState->BufferState == CANTP_BUFREQ_OK)
  {
    if (pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)
    {
      /* #20 Request PduR to copy the received data and update buffer state with the result. */
      lPduInfo.SduLength  = pTpRxState->PayloadLength;
      lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
      pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */ /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                     &lPduInfo,                                     /* PduInfoPtr   */
                                                     &pTpRxState->ProvidedBufferSize);              /* RxBufSizePtr */
    }
    else
    {
      /* #30 If buffer size is not sufficient: assume an invalid buffer state for further processing */
      /* Note: this shouldn't happen as a FC.CTS is only sent if enough buffer is available  */
      pTpRxState->BufferState = CANTP_BUFREQ_E_NOT_OK;                                                                 /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
    }
  }   
#endif /* CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON */

  /* --- Handle result of copy / buffer request --- */
  switch (pTpRxState->BufferState)
  {
    case CANTP_BUFREQ_OK:
      pTpRxState->DataIndex = (PduLengthType)(pTpRxState->DataIndex + pTpRxState->PayloadLength);                      /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->PayloadLength = 0;                                                                                   /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

      /* #60 If the current CF is the last: reception finished, reset connection without error. */
      if (pTpRxState->DataIndex >= pTpRxState->DataLength)
      {
        /* --- Buffer ok and last CF: reception finished --- */
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);                                  /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      else
      {
        /* #70 If the current CF is not the last: proceed according to the current BS counter: */
        /* BS = 0: no FC allowed, wait for next CF            */
        /* BS = 1: decrement, transmit FC.CTS or FC.WT        */
        /* BS > 1: decrement, no FC allowed, wait for next CF */

        /* assume in-block CF; will be overwritten if this is not correct */
        pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_CF;                                                              /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

        /* #80 If BS counter = 0: no FC allowed at all, wait for next CF. */
        if (pTpRxState->BlocksizeCounter > 0u)
        {
          /* #90 If BS counter = 1: end of block reached, update BS counter and prepare for flow control transmission. */
          pTpRxState->BlocksizeCounter--;                                                                              /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          if (pTpRxState->BlocksizeCounter == 0u)
          {

            /* --- Buffer ok and CF at end of block --- */
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                       /* COV_CANTP_EXCLUDED_FEATURES XF */
            /* buffer sufficient for next block: transmit FC.CTS */
            pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                                  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

            /* transmit FC */
            pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                          /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
            CanTp_RxTransmitFrame(pTpRxState);                                                                         /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
#else
            PduLengthType  lBytesPerBlock;

            lBytesPerBlock = CanTp_RxGetBytesPerBlock(pTpRxState);                                                     /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */

            if (pTpRxState->ProvidedBufferSize >= lBytesPerBlock)                                                      /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */
            {
              /* #100 If buffer size is sufficient for one block: trigger transmission of FC.CTS. */
              pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
            }
            else
            {
              /* --- New buffer request at end of block --- */
              lPduInfo.SduLength = 0;                                                                                  /* PRQA S 2880 */ /* MD_MSR_Unreachable */
              pTpRxState->BufferState = (CanTp_BufferStateType)CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */ /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                                                    &lPduInfo,                                     /* PduInfoPtr   */
                                                                                    &pTpRxState->ProvidedBufferSize);              /* RxBufSizePtr */

              /* assume FC.WT transmission; will be overwritten if other FC is needed */
              pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;                                                 /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
              if (pTpRxState->BufferState == CANTP_BUFREQ_OK)
              {
                if (pTpRxState->ProvidedBufferSize >= lBytesPerBlock)
                {
                  /* #120 If buffer is valid and large enough for one block: trigger transmission of FC.CTS. */
                  pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                            /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                }
                /* else: buffer still not sufficient; transmit FC.WT */
              }
              else
              {
                if (pTpRxState->BufferState != CANTP_BUFREQ_E_BUSY)
                {
                  /* #140 Any other buffer state: reset connection with buffer error (no FC is sent). */
                  CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);        /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
                }
                /* else: buffer busy; transmit FC.WT */
              }
            }

            if (pTpRxState->ChannelState != CANTP_RXSTATE_IDLE)
            {
              /* transmit FC */
              pTpRxState->Timer = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                               /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
              CanTp_RxTransmitFrame(pTpRxState);                                                                       /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
            }
            /* else: connection has been terminated */
#endif /* CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON */
          }
          /* else: CF not at end of block: wait for next CF (state is already set) */
        }
        /* else: BS = 0 and end of message not yet reached; wait for next CF (state is already set)   */
        /* check if remaining buffer is sufficient for next CF is omitted, because if sending BS = 0, */
        /* the receiver is responsible for providing enough buffer                                    */
      }
      break;

    case CANTP_BUFREQ_E_BUSY:
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_OFF)                                                                       /* COV_CANTP_EXCLUDED_FEATURES TX */
      /* --- Buffer busy: transmit FC.WT when at end of block --- */
      if (pTpRxState->BlocksizeCounter == 1u)
      {
        /* #170 If BS counter is 1: end of block reached, trigger transmission of FC.WAIT */
        pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                              /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
        pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;                                                       /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
        CanTp_RxTransmitFrame(pTpRxState);                                                                             /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      else
      {
        /* #180 If BS counter is 0 or > 1: not at end of block, no FC.WAIT allowed, reset connection with buffer error. */
        /* Note: busy buffer not allowed within a block or with BS = 0 (CANTP271) */
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                  /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      break;
#endif
    case CANTP_BUFREQ_E_OVFL:  /* CANTP318: no FC.OVFL is transmitted after a CF */
    case CANTP_BUFREQ_E_NOT_OK:
    default:
      /* #190 Any other buffer state: reset connection without sending a flow control. */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                    /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;
  } /* switch(BufferState) */
} /* CanTp_RxGetBufferCF() */  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */



/***********************************************************************************************************************
 *  CanTp_RxGetBufferFCWait()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxGetBufferFCWait(CanTp_RxStatePtrType pTpRxState)
{
  PduInfoType             lPduInfo;

  /* --- Copy previously stored payload, if there is any --- */
  if ((pTpRxState->BufferState == CANTP_BUFREQ_OK) && (pTpRxState->PayloadLength != 0u) )
  {
    /* #20 If the provided buffer is valid and large enough: */
#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                       /* COV_CANTP_EXCLUDED_FEATURES XF */
    if (pTpRxState->ProvidedBufferSize >= pTpRxState->DataLength)     /* buffer must be sufficient for the complete message */
#else
    if (pTpRxState->ProvidedBufferSize >= pTpRxState->PayloadLength)  /* buffer must be sufficient to stored payload */
#endif
    {
      /* #30 Request PduR to copy the received data and update buffer state with the result. */
      lPduInfo.SduLength  = pTpRxState->PayloadLength;
      lPduInfo.SduDataPtr = &pTpRxState->Payload[0];
      pTpRxState->BufferState = CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */ /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                     &lPduInfo,                                     /* PduInfoPtr   */
                                                     &pTpRxState->ProvidedBufferSize);              /* RxBufSizePtr */
    }
    else
    {
      /* #40 If buffer is not sufficient: wait for more buffer (set buffer state to busy). */
      pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;                                                                   /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
    }
  }

  /* --- Check state of provided buffer --- */
  switch (pTpRxState->BufferState)
  {
    case CANTP_BUFREQ_OK:
      /* --- Buffer ok and last CF already received --- */
      pTpRxState->DataIndex = (pTpRxState->DataIndex + pTpRxState->PayloadLength);                                     /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->PayloadLength = 0;                                                                                   /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

#if (CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON)                                                                       /* COV_CANTP_EXCLUDED_FEATURES XF */
      /* BUFREQ_OK after FC.WT: only if buffer is sufficient for complete message */
      pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                                        /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      CanTp_RxTransmitFrame(pTpRxState);                                                                               /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
#else
      /* #70  If no more CFs are expected: reception finished, reset connection without error. */
      if (pTpRxState->DataIndex >= pTpRxState->DataLength)
      {
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);                                  /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      else
      {
        /* --- Buffer ok and last CF no yet received --- */
        /* #80  If more CFs are expected and buffer is sufficient for one block: trigger transmission of FC.CTS. */
        PduLengthType  lBytesPerBlock;

        /* buffer need to be sufficient for at least one block */
        lBytesPerBlock = CanTp_RxGetBytesPerBlock(pTpRxState);                                                         /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */

        if (pTpRxState->ProvidedBufferSize >= lBytesPerBlock)                                                          /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */
        {
          pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                            /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_CTS;                                                    /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
          CanTp_RxTransmitFrame(pTpRxState);                                                                           /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
        }
        else
        {
          /* #90 If buffer is not sufficient for one block: keep waiting for buffer (set buffer state to busy). */
          pTpRxState->BufferState = CANTP_BUFREQ_E_BUSY;                                                               /* PRQA S 2880 */ /* MD_MSR_Unreachable */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
        }
      }
#endif /* CANTP_SINGLE_RX_BUFFER_OPTIMIZED == STD_ON */
      break;

    case CANTP_BUFREQ_E_BUSY:
      /* #100  If buffer state is busy: do nothing, keep waiting for buffer. */
      break;

    default:
      /* #110 Any other buffer state: reset connection with buffer error. */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                    /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;
  } /* switch(BufferState) */
} /* CanTp_RxGetBufferFCWait() */



#if ((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON) || (CANTP_GENERIC_CONNECTIONS == STD_ON))
/***********************************************************************************************************************
 *  CanTp_Cfg_GetSduHdlByRxPduOnly()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduOnly (PduIdType RxPduId, uint8 FrameType)
{
  PduIdType lSduHdl = CANTP_INVALID_HDL;                                                                               /* PRQA S 	2981 */ /* MD_CanTp_RedundantAssignment */

  /* due to optimizations, the RxPduId may not be needed */
  CANTP_DUMMY_STATEMENT(RxPduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */


  if ( (FrameType == CANTP_PCI_TYPE_FC) && (CanTp_CanIfRxPduHasTxSduRef(RxPduId)) )                                    /* COV_CANTP_PDU_REF */
  {
    /* --- get TxSduId from RxPduId  --- */
    /* for standard addressing, this is a 1:1 reference (validated by GenTool) */
    /* #20 get the configured Tx N-SDU handle for a given RxPduId from the generated tables. */
    lSduHdl = (PduIdType)CanTp_GetTxSduCfgInd(CanTp_GetTxSduCfgIndStartIdxOfRxPduMap(RxPduId));
  }
# if (CANTP_RXSDUCFGIND == STD_ON)                                                                                     /* COV_CANTP_ROBUSTNESS_CASE TX */
  else if ( (FrameType != CANTP_PCI_TYPE_FC) && (CanTp_CanIfRxPduHasRxSduRef(RxPduId)) )                               /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */ /* COV_CANTP_PDU_REF */
  {
    /* --- get RxSduId from RxPduId  --- */
    /* for standard addressing, this is a 1:1 reference (validated by GenTool) */
    /* #40 get the configured Rx N-SDU handle for a given RxPduId from the generated tables. */
    lSduHdl = (PduIdType)CanTp_GetRxSduCfgInd(CanTp_GetRxSduCfgIndStartIdxOfRxPduMap(RxPduId));
  }
# endif /* (CANTP_RXSDUCFGIND == STD_ON) */
  else
  {
    /* invalid handle; is already set initially */
  }

  /* #50 Return the matching SduHandle, or an invalid handle if none have been found. */
  return lSduHdl;
} /* CanTp_Cfg_GetSduHdlByRxPduOnly */
#endif



#if ((CANTP_SUPPORT_EXTENDED_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED11_ADDRESSING == STD_ON) || (CANTP_SUPPORT_MIXED29_ADDRESSING == STD_ON))
/***********************************************************************************************************************
 *  CanTp_Cfg_GetSduHdlByRxPduAddress()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(PduIdType, CANTP_CODE) CanTp_Cfg_GetSduHdlByRxPduAddress (PduIdType RxPduId, uint8 FrameType, uint8 Address)
{
  PduIdType lSduCurrentHdl;
  PduIdType lSduReturnHdl = CANTP_INVALID_HDL;

  /* due to optimizations, the RxPduId may not be needed */
  CANTP_DUMMY_STATEMENT(RxPduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  if (FrameType == CANTP_PCI_TYPE_FC)
  {
    /* --- get TxSduId from RxPduId  --- */
    /* with an additional address byte in the payload, there may be multiple references */
#if (CANTP_TXSDUCFGIND == STD_ON)                                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
    CanTp_TxSduCfgIndIterType lTxduIndirectionIndex;

    /* #20 Iterate over all configured Tx N-SDU handles for a given RxPduId until a Tx N-SDU with the given address have been found. */
    /* Note: if start and end index are equal, no RxSdu is configured */
    for (lTxduIndirectionIndex = (PduIdType)CanTp_GetTxSduCfgIndStartIdxOfRxPduMap(RxPduId);
         lTxduIndirectionIndex < (PduIdType)CanTp_GetTxSduCfgIndEndIdxOfRxPduMap(RxPduId);
         lTxduIndirectionIndex++)
    {
      lSduCurrentHdl = (PduIdType)CanTp_GetTxSduCfgInd(lTxduIndirectionIndex);

      if (CanTp_TxCfg_GetRxFcAddress(lSduCurrentHdl) == Address)
      {
        /* the TxSdu which is referenced by the RxPdu has also the correct FC Address --> bingo! */
        lSduReturnHdl = lSduCurrentHdl;
        break;
      }
    }
#endif
  }
  else
  {
    /* --- get RxSduId from RxPduId  --- */
    /* with an additional address byte in the payload, there may be multiple references */
#if (CANTP_RXSDUCFGIND == STD_ON)                                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
    CanTp_RxSduCfgIndIterType lRxduIndirectionIndex;
    /* #40 Iterate over all configured Rx N-SDU handles for a given RxPduId until an Rx N-SDU with the given address have been found. */
    /* Note: if start and end index are equal, no RxSdu is configured */
    for (lRxduIndirectionIndex = (PduIdType)CanTp_GetRxSduCfgIndStartIdxOfRxPduMap(RxPduId);
         lRxduIndirectionIndex < (PduIdType)CanTp_GetRxSduCfgIndEndIdxOfRxPduMap(RxPduId);
         lRxduIndirectionIndex++)
    {
      lSduCurrentHdl = (PduIdType)CanTp_GetRxSduCfgInd(lRxduIndirectionIndex);

      if (CanTp_RxCfg_GetRxAddress(lSduCurrentHdl) == Address)
      {
        /* the RxSdu which is referenced by the RxPdu has also the correct Address --> bingo! */
        lSduReturnHdl = lSduCurrentHdl;
        break;                                                                                                         /* PRQA S 3333 */ /* MD_CanTp_3333 */
      }
    }
#endif
  }

  /* #50 Return the matching SduHandle, or an invalid handle if none have been found. */
  return lSduReturnHdl;
} /* CanTp_Cfg_GetSduHdlByRxPduAddress */
#endif



/***********************************************************************************************************************
 *  CanTp_RxInitState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_RxInitState(CanTp_RxStatePtrType pTpRxState)
{
  /* #10 Reset all elements in the Rx state struct referenced by RxStatePtr.                             */
  /* data buffers are not reset; the validity of their content is given by the related length parameter: */
  /* - PayloadLength <--> Payload[]                                                                      */
  /* - SduMetadataLength <--> SduMetadata[]                                                              */
  /* - PduMetadataLength <--> PduMetadata[]                                                              */
  pTpRxState->RxHdl                = CANTP_INVALID_HDL;                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->FrameType            = CANTP_FRAME_INVALID;                                                              /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->ChannelState         = CANTP_RXSTATE_IDLE;                                                               /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->Timer                = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->DataLength           = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->DataIndex            = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->ProvidedBufferSize   = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->WFTCounter           = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->BufferState          = CANTP_BUFREQ_OK;                                                                  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->BlocksizeCounter     = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->PayloadLength        = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->InitalDLC            = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
  pTpRxState->ExpectedSN           = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#if (( CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON ) || ( CANTP_RC == STD_ON ))
  pTpRxState->ApplState            = CANTP_APPL_NOT_INFORMED;                                                          /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#endif
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  pTpRxState->SduMetadataLength    = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  pTpRxState->FcPduMetadataLength  = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
# endif
#endif

} /* CanTp_RxInitState() */



/***********************************************************************************************************************
 *  CanTp_TxInitState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_TxInitState(CanTp_TxStatePtrType pTpTxState)
{
  /* #10 Reset all elements in the Tx state struct referenced by TxStatePtr.                             */
  /* data buffers are not reset; the validity of their content is given by the related length parameter: */
  /* - PayloadLength <--> Payload[]                                                                      */
  /* - FCLength      <--> FCData[]                                                                       */
  /* - SduMetadataLength      <--> SduMetadata[]                                                         */
  /* - DataPduMetadataLength  <--> DataPduMetadata[]                                                     */
  pTpTxState->TxHdl             = CANTP_INVALID_HDL;                                                                   /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#if (CANTP_STMIN_BY_APPL == STD_ON)
  pTpTxState->TxSduSnv          = CanTp_Cfg_GetNumTxSduIds();                                                          /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#endif
  pTpTxState->ChannelState          = CANTP_TXSTATE_IDLE;                                                              /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->Timer                 = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->DataLength            = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->DataIndex             = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->BufferState           = CANTP_BUFREQ_OK;                                                                 /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->BlocksizeCounter      = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->STmin                 = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->STminTimer            = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->PayloadLength         = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->SeqNumber             = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#if (CANTP_USE_ONLY_FIRST_FC == STD_ON)
  pTpTxState->BS                    = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  pTpTxState->FirstFCReceived       = FALSE;                                                                           /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#endif
  pTpTxState->FCLength              = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  pTpTxState->SduMetadataLength     = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  pTpTxState->DataPduMetadataLength = 0;                                                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
# endif
#endif
} /* CanTp_TxInitState() */



/***********************************************************************************************************************
 *  CanTp_RxGetFreeChannelPtr()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetFreeChannelPtr(PduIdType RxHdl,
                                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                                                    P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo)
{
  CanTp_RxStatePtrType pTpRxState = NULL_PTR;

  /* #10 If RxHdl is currently not active: */
  if (CanTp_RxChannelIsIdle(RxHdl))
  {
#if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
    PduIdType            lChannelHdl;
    /* #20 If Dynamic Channel Assignment is used, iterate through all the available Rx channels: */
    for (lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumRxChannels(); lChannelHdl++)
    {
      /* #30 If a free Rx channel is found, map the passed RxHdl to it.
       *     Otherwise, a NULL pointer will be returned.
       */
      if (CanTp_Data_RxState(lChannelHdl).ChannelState == CANTP_RXSTATE_IDLE)
      {
        CanTp_NumRxChannelsAvail--;
        CanTp_Data_RxChannelMap(RxHdl) = lChannelHdl;         /* mapping handle -> state */                            /* SBSW_CANTP_RXGETFREECHANNEL_WRITE_CHANNELMAP */
        pTpRxState = &CanTp_Data_RxState(lChannelHdl);
        pTpRxState->RxHdl = RxHdl;                            /* mapping state -> handle */                            /* SBSW_CANTP_RXGETFREECHANNEL_WRITE_STATE */

        break;
      }
    }
#else
    /* #40 Otherwise, Return a pointer to RxState[RxHdl] (non-dynamic channel assignment). */
    pTpRxState = &CanTp_Data_RxState(RxHdl);
    pTpRxState->RxHdl = RxHdl;                            /* mapping state -> handle */                                /* SBSW_CANTP_RXGETFREECHANNEL_WRITE_STATE */
#endif
  }

  /* #70 If required and a free channel is available, extract and store the Rx SDU metadata. */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  if (pTpRxState != NULL_PTR)
  {
    CanTp_Util_RxExtractSduMetadataInfo(pTpRxState, pPayloadInfo, pMetadataInfo);                                      /* SBSW_CANTP_RXEXTRACTSDUMETADATA_CALL_PTRS */
  }
#else
  CANTP_DUMMY_STATEMENT(pPayloadInfo);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  CANTP_DUMMY_STATEMENT(pMetadataInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return pTpRxState;
} /* CanTp_RxGetFreeChannelPtr() */



/***********************************************************************************************************************
 *  CanTp_RxGetActiveChannelPtr()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(CanTp_RxStatePtrType, CANTP_CODE) CanTp_RxGetActiveChannelPtr(PduIdType RxHdl)
{
  CanTp_RxStatePtrType pTpRxState = NULL_PTR;

  /* #10 If RxHdl is not related to an idle channel, return a pointer to the channel state. */
  if (!CanTp_RxChannelIsIdle(RxHdl))
  {
    pTpRxState = CanTp_RxGetChannelPtr(RxHdl);
  }

  return pTpRxState;
} /* CanTp_RxGetActiveChannelPtr */


/***********************************************************************************************************************
 *  CanTp_TxGetFreeChannelPtr()
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
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetFreeChannelPtr(PduIdType TxHdl,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr)
{
  CanTp_TxStatePtrType pTpTxState = NULL_PTR;

  /* #10 If TxHdl is currently not active: */
  if (CanTp_TxChannelIsIdle(TxHdl))
  {
#if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
    PduIdType            lChannelHdl;
    /* #20 If Dynamic Channel Assignment is used, iterate through all the available Tx channels: */
    for (lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumTxChannels(); lChannelHdl++)
    {
      /* #30 If a free Tx channel is found, map the passed TxHdl to it.
       *     Otherwise, a NULL pointer will be returned.
       */
      if (CanTp_Data_TxState(lChannelHdl).ChannelState == CANTP_TXSTATE_IDLE)
      {
        CanTp_NumTxChannelsAvail--;
        CanTp_Data_TxChannelMap(TxHdl) = lChannelHdl;         /* mapping handle -> state */                            /* SBSW_CANTP_TXGETFREECHANNEL_WRITE_CHANNELMAP */
        pTpTxState = &CanTp_Data_TxState(lChannelHdl);
        pTpTxState->TxHdl = TxHdl;                            /* mapping state -> handle */                            /* SBSW_CANTP_TXGETFREECHANNEL_WRITE_STATE */
        break;
      }
    }
#else
    /* #40 Otherwise, Return a pointer to TxState[TxHdl] (non-dynamic channel assignment). */
    pTpTxState = &CanTp_Data_TxState(TxHdl);
    pTpTxState->TxHdl = TxHdl;                            /* mapping state -> handle */                                /* SBSW_CANTP_TXGETFREECHANNEL_WRITE_STATE */
#endif
  }

  /* #70 If required and a free channel is available, extract and store the Tx SDU metadata. */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  if (pTpTxState != NULL_PTR)
  {
    CanTp_Util_TxExtractSduMetadataInfo(pTpTxState, CanTpTxInfoPtr);                                                   /* SBSW_CANTP_TXEXTRACTSDUMETADATA_CALL_PTRS */
  }
#else
  CANTP_DUMMY_STATEMENT(CanTpTxInfoPtr);                                                                               /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return pTpTxState;
} /* CanTp_TxGetFreeChannelPtr() */


/***********************************************************************************************************************
 *  CanTp_TxGetActiveChannelPtr()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(CanTp_TxStatePtrType, CANTP_CODE) CanTp_TxGetActiveChannelPtr(PduIdType TxHdl)
{
  CanTp_TxStatePtrType pTpTxState = NULL_PTR;

  /* #10 If TxHdl is not related to an idle channel, return a pointer to the channel state. */
  if (!CanTp_TxChannelIsIdle(TxHdl))
  {
    pTpTxState = CanTp_TxGetChannelPtr(TxHdl);
  }

  return pTpTxState;
} /* CanTp_TxGetActiveChannelPtr */


#if (CANTP_TRANSMITFCTOFLOLAYERFCTS == STD_ON)
/***********************************************************************************************************************
 *  CanTp_LoLayerTransmit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(Std_ReturnType, CANTP_CODE) CanTp_LoLayerTransmit(CanTp_DirectionType Direction,
                                                                          PduIdType SduHdl,
                                                                          PduIdType LoLayerTxPduId,
                                                                          P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData)
{
  uint8 lLoLayerIdx;
  Std_ReturnType lResult;

  /* #10 Determine the lower layer of the passed SDU. */
  if (Direction == CANTP_DIR_TX) 
  {
    lLoLayerIdx = CanTp_TxCfg_GetLoLayerIdx(SduHdl);
  }
  else
  {
    lLoLayerIdx = CanTp_RxCfg_GetLoLayerIdx(SduHdl);
  }

  /* #20 Request the transmission of the passed data to the lower layer. */
  lResult = CanTp_GetTransmitFctOfLoLayerFcts(lLoLayerIdx)(LoLayerTxPduId, pTpData);                                   /* SBSW_CANTP_LOLAYERTRANSMIT_FCTPTR */

  return lResult;
} /* CanTp_LoLayerTransmit */
#endif

#if (CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS == STD_ON)
/***********************************************************************************************************************
 *  CanTp_LoLayerCancelTransmit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL_INLINE FUNC(void, CANTP_CODE) CanTp_LoLayerCancelTransmit(CanTp_DirectionType Direction, PduIdType SduHdl, PduIdType LoLayerTxPduId)
{
  uint8 lLoLayerIdx;

  /* #10 Determine the lower layer of the passed SDU. */
  if (Direction == CANTP_DIR_TX) 
  {
    lLoLayerIdx = CanTp_TxCfg_GetLoLayerIdx(SduHdl);
  }
  else
  {
    lLoLayerIdx = CanTp_RxCfg_GetLoLayerIdx(SduHdl);
  }

  /* #20 If transmission cancellation is possible, request the lower layer to do so. */
  if (CanTp_GetCancelTransmitFctOfLoLayerFcts(lLoLayerIdx) != NULL_PTR)                                                /* COV_CANTP_LOLAYERFCT_CHECK TX */
  {
    (void)CanTp_GetCancelTransmitFctOfLoLayerFcts(lLoLayerIdx)(LoLayerTxPduId);                                        /* SBSW_CANTP_LOLAYERCANCELTRANSMIT_FCTPTR */
  }
} /* CanTp_LoLayerCancelTransmit */
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  CanTp_CanIfRxIndication()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfRxIndication(PduIdType  SduHdl,
                                                           uint8      FrameType,
                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pPayloadInfo,
                                                           P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pMetadataInfo)
{
  CANTP_DUMMY_STATEMENT(SduHdl);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  CANTP_DUMMY_STATEMENT(pMetadataInfo); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  if (CANTP_PCI_TYPE_FC != FrameType)  /* Rx */
  {

    /* --- Rx Padding Check --- */
#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
    uint8 lPaddingLength;

    lPaddingLength = CanTp_Util_GetPaddingLength((uint8)pPayloadInfo->SduLength, CanTp_RxCfg_HasPaddingActivation(SduHdl), CanTp_RxCfg_GetCanType(SduHdl));
    if (pPayloadInfo->SduLength != lPaddingLength)
    {
      /* received N-PDUs which do not meet the configured padded frame length are considered corrupt */
      CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_PARAM_CONFIG)
    }
    else
#endif /* CANTP_PADDING_SUPPORT_REQUIRED == STD_ON */
    {
      CanTp_EnterCritical();  /* CanTp_RxIndication ~~~~~~~~~~~~~~~~~~~~ */

      /*--- Rx Half-Duplex Check --- */
#if (CANTP_RX_HAS_HALF_DUPLEX == STD_ON)
      if (CanTp_RxCheckChannelMode(SduHdl) == E_OK)
#endif
      {

        /* --- Process Received Data N-PDU --- */
        {
          CanTp_RxStatePtrType pTpRxState;
          pTpRxState = CanTp_RxGetActiveChannelPtr(SduHdl);

          if (pTpRxState == NULL_PTR)
          {
            /* no channel active; maybe we can start a new connection? */
            /* #50 In case of a received SF or FF: allocate new channel, if needed. */
            if ((FrameType == CANTP_PCI_TYPE_SF) || (FrameType == CANTP_PCI_TYPE_FF))
            {
              pTpRxState = CanTp_RxGetFreeChannelPtr(SduHdl, pPayloadInfo, pMetadataInfo);                             /* SBSW_CANTP_RXGETFREECHANNEL_CALL_PTRS */
            }
            /* else: CF received out of order, leave RxStatePtr as NULL to ignore the frame */
          }
          /* else: use the already mapped channel for further processing */

          /* #60  If a channel is allocated: */
          if (pTpRxState != NULL_PTR)
          {
            /* #61  If the just-received Rx SDU metadata matches the one already assigned to the channel: */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
            if (CanTp_Util_RxSduMetadataFromDataPduMatch(pTpRxState, pPayloadInfo, pMetadataInfo) == TRUE)             /* SBSW_CANTP_RXSDUMETADATAMATCH_CALL_PTRS */
#endif
            {
              /* #62  Continue processing depending on FrameType: */
              switch (FrameType)
              {
                /* #63  SF or FF:
                 *        If the SDU is non-generic or if the channel is idle, continue processing.
                 *        Otherwise, Ignore frame.
                 */
                case CANTP_PCI_TYPE_SF:
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
                  if ((!CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl)) ||
                      (pTpRxState->ChannelState == CANTP_RXSTATE_IDLE))
#endif
                  {
                    CanTp_CanIfRxIndicationSF(pTpRxState, pPayloadInfo);                                               /* SBSW_CANTP_CANIFRXINDICATION_CALL_RXSTATE */
                  }
                  break;
                case CANTP_PCI_TYPE_FF:
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
                  if ((!CanTp_RxCfg_IsGenericConnection(pTpRxState->RxHdl)) ||
                      (pTpRxState->ChannelState == CANTP_RXSTATE_IDLE))
#endif
                  {
                    CanTp_CanIfRxIndicationFF(pTpRxState, pPayloadInfo);                                               /* SBSW_CANTP_CANIFRXINDICATION_CALL_RXSTATE */
                  }
                  break;

                /* #65  CF: Continue processing. */
                case CANTP_PCI_TYPE_CF:
                  CanTp_CanIfRxIndicationCF(pTpRxState, pPayloadInfo);                                                 /* SBSW_CANTP_CANIFRXINDICATION_CALL_RXSTATE */
                  break;

                /* #66  Other: Ignore. */
                default:                                                                                               /* COV_CANTP_INVALID_FRAME_TYPE */
                  /* Ignore unknown frame types */
                  break;
              }
            }
          }
          /* #70  Otherwise: no channel could be allocated or there's a metadata mismatch, ignore reception. */
        }
      }
      /* else: half duplex and Tx side is busy */
      /* #80 If half duplex check failed, ignore frame. */
      CanTp_LeaveCritical();  /* CanTp_RxIndication ~~~~~~~~~~~~~~~~~~~~ */
    } /* end: Rx padding check */
  }

  else  /* Tx */
  {
    /* --- Tx Padding Check --- */
#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
    uint8  lPaddingLength;

    lPaddingLength = CanTp_Util_GetPaddingLength((uint8)pPayloadInfo->SduLength, CanTp_TxCfg_HasPaddingActivation(SduHdl), CanTp_TxCfg_GetCanType(SduHdl));
    if (pPayloadInfo->SduLength != lPaddingLength )
    {
      /* received FC N-PDU which do not meet the configured padded frame length are considered corrupt */
      CanTp_DetReportError(CANTP_SID_RXINDICATION, CANTP_E_PARAM_CONFIG)
    }
    else
#endif /* CANTP_PADDING_SUPPORT_REQUIRED == STD_ON */
    {
      CanTp_TxStatePtrType pTpTxState;

      /* --- Process Received Flow Control N-PDU --- */
      CanTp_EnterCritical();  /* CanTp_RxIndication ~~~~~~~~~~~~~~~~~~~~~~ */

      /* #120 If a channel is active: */
      pTpTxState = CanTp_TxGetActiveChannelPtr(SduHdl);
      if (pTpTxState != NULL_PTR)
      {
        /* #124 If the just-received Tx SDU metadata matches the one already assigned to the channel: */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
        if (CanTp_Util_TxSduMetadataFromFcPduMatch(pTpTxState, pPayloadInfo, pMetadataInfo) == TRUE)                   /* SBSW_CANTP_TXSDUMETADATAMATCH_CALL_PTRS */
#endif
        {
          /* #127 Process FC reception. */
          CanTp_CanIfRxIndicationFC(pTpTxState, pPayloadInfo);                                                         /* SBSW_CANTP_CANIFRXINDICATION_CALL_TXSTATE */
        }
      }
      /* #130 Otherwise: ignore FC, it is not expected. */

      CanTp_LeaveCritical();  /* CanTp_RxIndication ~~~~~~~~~~~~~~~~~~~~~~ */
    } /* end: Tx padding check */
  } /* end: frame type / direction check */
} /* CanTp_CanIfRxIndication() */  /* PRQA S 6050, 6030, 6080 */ /* MD_MSR_STCAL, MD_MSR_STCYC, MD_MSR_STMIF */


#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
/***********************************************************************************************************************
 *  CanTp_CanIfTxConfirmation()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmation(CanTp_TxStatePtrType pTpTxState)
{
  switch (pTpTxState->ChannelState)
  {
    /* --- SF is confirmed --- */
    case CANTP_TXSTATE_WAIT_TXCONF_SF:
      /* #30 Transmission is complete, reset connection.*/
      CanTp_TxInit(pTpTxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR);                                                     /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
      break; /* SF */

    /* --- FF is confirmed --- */
    case CANTP_TXSTATE_WAIT_TXCONF_FF:
      /* #50 Start waiting for flow control. */
# if (CANTP_USE_ONLY_FIRST_FC == STD_ON)
      pTpTxState->FirstFCReceived = FALSE;                                                                             /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
# endif
      pTpTxState->Timer        = CanTp_TxCfg_GetNBs(pTpTxState->TxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_FC;                                                                /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      break; /* FF */

    /* --- CF is confirmed --- */
    case CANTP_TXSTATE_WAIT_TXCONF_CF:
      if (pTpTxState->DataIndex < pTpTxState->DataLength)
      {
        /* #70 If last CF has not yet been transmitted: prepare for transmission of next CF. */
        /* Still data left, proceed with transmission of next CF */
        pTpTxState->SeqNumber  = (uint8)((pTpTxState->SeqNumber + 1u) & CANTP_PCI_SN_MASK);                            /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */

        /* --- Check for End of Block--- */
        /* #80 If end of block has been reached: wait for next flow control. */
        if (pTpTxState->BlocksizeCounter != 0u)
        {
          pTpTxState->BlocksizeCounter--;                                                                              /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
          if (pTpTxState->BlocksizeCounter == 0u)
          {
            /* Block finished - Wait for FC */
            pTpTxState->Timer        = CanTp_TxCfg_GetNBs(pTpTxState->TxHdl);                                          /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
            pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_FC;                                                          /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
          }
        }
        /* else: block size not used */

        /* #90 If end of block has not yet been reached, start waiting for STmin: */
        if (pTpTxState->ChannelState != CANTP_TXSTATE_WAIT_FC)
        {

          /* --- Prepare Waiting for STmin --- */
          /* separation time need to be applied; timeout is always N_Cs (= STmax) */
          pTpTxState->Timer        = CanTp_TxCfg_GetNCs(pTpTxState->TxHdl);                                            /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
          {
# if (CANTP_STMIN_BY_APPL == STD_ON)
            boolean lSeparationTimeByAppl;

            /* assume that the application will do STmin, just wait for N_Cs/STmax */
            pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_STMIN_APPL;                                                  /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */

            /* exit critical section for the call, as application might use OS functions to activate a timer! */
            CanTp_LeaveCritical();  /* CanTp_CanIfTxConfirmation ~~~~~~~~~~~~~~~~ */
            lSeparationTimeByAppl = CanTp_ApplStartSeparationTime(pTpTxState->TxSduSnv, pTpTxState->STmin);
            CanTp_EnterCritical();  /* CanTp_CanIfTxConfirmation ~~~~~~~~~~~~~~~~ */

            /* ask application to handle the separation time; take care of unexpected interruptions */
            /* e.g. when the application calls CanTp_CancelTransmit in the call-out                 */
            if ( (lSeparationTimeByAppl    == FALSE) &&
                 (pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_STMIN_APPL) )
# endif
            {
              /* CanTp internal STmin handling */
              if (pTpTxState->STmin == 0u)
              {
                /* burst mode; transmit next CF immediately */
                pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;                                               /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
                CanTp_TxGetBuffer_ISR(pTpTxState)                                                                      /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
              }
              else
              {
                /* prepare for waiting for end of STmin */
                pTpTxState->STminTimer   = CanTp_TxGetStminTimerFromStminValue(pTpTxState->STmin);                     /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
                pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_STMIN_INTERN;                                            /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
              }
            }
            /* else: STmin handled by application, or state have changed */
          }
          /* end of block 'STmin Handling */
        }
        /* else: end of block, no STmin needed */
      }
      /* #100 If last CF has been transmitted, the transmission is complete, reset connection. */
      else
      {
        CanTp_TxInit(pTpTxState, CANTP_NOTIFY_OK, CANTP_E_NO_ERROR);                                                   /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
      }
      break; /* CF */

    /* #110 Any other ChannelState: report DET error and exit. */
    default:                                                                                                           /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      CanTp_DetReportError(CANTP_SID_TXCONFIRMATION, CANTP_E_INVALID_TX_STATE)
      break;
  }  /* switch(ChannelState) */

  /* --- Rx/Tx inversion handling --- */
  /* #120 If a flow control has been stored due to enabled Rx/Tx inversion handling: process the stored frame (call CanTp_CanIfRxIndicationFC). */
  if (pTpTxState->FCLength != 0u)
  {
    PduInfoType PduInfo;

    PduInfo.SduDataPtr   = pTpTxState->FCData;
    PduInfo.SduLength    = pTpTxState->FCLength;
    pTpTxState->FCLength = 0;                                                                                          /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
    CanTp_CanIfRxIndicationFC(pTpTxState, &PduInfo);                                                                   /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
  }
} /* CanTp_CanIfTxConfirmation() */  /* PRQA S 6080, 6030, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCYC, MD_MSR_STCAL */
#endif /* (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */


#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
/***********************************************************************************************************************
 *  CanTp_CanIfTxConfirmationFC()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_CanIfTxConfirmationFC(CanTp_RxStatePtrType pTpRxState)
{
  /* #10 Process the TxConfirmation depending on the flow status (indicated by the ChannelState). */
  switch (pTpRxState->ChannelState)
  {
    /* #20  FC.CTS is confirmed: */
    case CANTP_RXSTATE_WAIT_TXCONFFC_CTS:
    /* #30 Reset WFT counter, set the timer and wait for next CF. */
      pTpRxState->WFTCounter   = CanTp_RxCfg_GetWFTmax(pTpRxState->RxHdl);                                             /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->Timer        = CanTp_RxCfg_GetNCr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_CF;                                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      break; /* FC.CTS */

    /* #40 FC.WT is confirmed: */
    case CANTP_RXSTATE_WAIT_TXCONFFC_WT:
    /* #50 Wait for next wait frame, set the timer and prepare for buffer request on task level. */
      CanTp_DetAssert((pTpRxState->WFTCounter >= 1u), CANTP_SID_TXCONFIRMATION, (CANTP_E_PARAM_CONFIG))
      pTpRxState->WFTCounter--;                                                                                        /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->BufferState  = CANTP_BUFREQ_E_BUSY;                                                                  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->Timer        = CanTp_RxCfg_GetNBr(pTpRxState->RxHdl);                                                /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      pTpRxState->ChannelState = CANTP_RXSTATE_WAIT_NEXT_FCWAIT;                                                       /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      break; /* FC.WT */

    /* #60  FC.OVFL is confirmed: */
    case CANTP_RXSTATE_WAIT_TXCONFFC_OVFL:
      /* #70 Reset connection after error during buffer request. */
      CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);                    /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break; /* FC.OVFL */

    /* #80 Any other ChannelState: report DET error */
    default:                                                                                                           /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      CanTp_DetReportError(CANTP_SID_TXCONFIRMATION, CANTP_E_INVALID_RX_STATE)
      break;
  } /* switch(ChannelState) */
} /* CanTp_CanIfTxConfirmationFC() */
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */


/***********************************************************************************************************************
 *  CanTp_CanIfTransmitFrame()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(CanTp_TxResultType, CANTP_CODE) CanTp_CanIfTransmitFrame(P2CONST(CanTp_PduTxInfoType, AUTOMATIC, CANTP_APPL_DATA) pPduTxData,
                                                                          P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) pTpData)             /* PRQA S 3673 */ /* MD_CanTp_3673 */
{
  CanTp_TxResultType  lCanIfResult;

#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
  /* --- Add Padding --- */
# if (CANTP_HAVE_PADDING_BYTE == STD_ON)
  while( pTpData->SduLength < (PduLengthType)pPduTxData->PaddingLength )
  {
    /* #10 If needed, add padding bytes with the configured pattern until the required PaddingLength is reached. */
    pTpData->SduDataPtr[pTpData->SduLength] = CANTP_PADDING_PATTERN;                                                   /* SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TPDATAPTR */
    pTpData->SduLength++;                                                                                              /* SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TPDATAPTR */
  }
# else
  /* only adapt the length for CanIf */
  pTpData->SduLength = (PduLengthType)pPduTxData->PaddingLength;                                                       /* SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TPDATAPTR */
# endif
#endif

  /* #15  If PDU metadata is required, append it after the already copied payload. */
#if (CANTP_MAX_PDU_METADATA_LENGTH != 0) 
  if (pPduTxData->PduMetadataLength != 0u)
  {
    CanTp_Util_MemCpy(&pTpData->SduDataPtr[pTpData->SduLength],                                                        /* SBSW_CANTP_MEMCPY_CALL_TXFRAMEMETADATA */
                      pPduTxData->PduMetadata,
                      pPduTxData->PduMetadataLength);
    pTpData->SduLength += pPduTxData->PduMetadataLength;                                                               /* SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TPDATAPTR */
  }
#endif

  /*--- Transmit CanTp Frame --- */
  /* #20 If semaphore of TxConfPdu is not yet in use: */
  if (CanTp_Data_TxSemaphore(pPduTxData->TxConfPduId).Handle == CANTP_INVALID_HDL)
  {
    /* #30 Pass CanTp frame to CanIf and return the result of the transmission request. */
    lCanIfResult = CanTp_CanIfTransmit(pPduTxData->SduDirection, pPduTxData->SduHdl, pPduTxData->TxPduId, pTpData);    /* SBSW_CANTP_CANIFTRANSMIT_CALL_TPDATA */

    if (lCanIfResult == CANTP_TX_OK)
    {
      /* #40 If request was successful, also lock the semaphore and call debugging call-out. */
      CanTp_Data_TxSemaphore(pPduTxData->TxConfPduId).Direction = pPduTxData->SduDirection;                            /* SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TXSEMAPHORE */
      CanTp_Data_TxSemaphore(pPduTxData->TxConfPduId).Handle    = pPduTxData->SduHdl;                                  /* SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TXSEMAPHORE */

      CanTp_ApplFrameTransmission(pPduTxData->TxPduId, pTpData)                                                        /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */
    }
    /* else: transmission failed for unknown reason */
  }
  /* #50 If semaphore of TxConfPdu is already locked and N-PDU can't be queued: return status "busy". */
  else
  {
    /* Pdu already in use; try later */
    lCanIfResult = CANTP_TX_BUSY;

#if (CANTP_TRANSMIT_QUEUE == STD_ON)
    /* #60 If Tx queue is used and not full, store N-PDU in queue and assume a successful transmission (return status "ok"). */
    if (!CanTp_TxQueueIsFull(pPduTxData->TxConfPduId))
    {
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).PduId = pPduTxData->TxPduId;                                           /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduHandle = pPduTxData->SduHdl;                                        /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduDirection = pPduTxData->SduDirection;                               /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
      CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduLength = pTpData->SduLength;                                        /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
      CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(CanTp_TxQueueEntryWritePos(pPduTxData->TxConfPduId).SduData), /* SBSW_CANTP_MEMCPY_CALL_TXQUEUE */
                        (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pTpData->SduDataPtr), (uint16)pTpData->SduLength);

      CanTp_Data_TxQueue(pPduTxData->TxConfPduId).WritePos = (uint8)((CanTp_Data_TxQueue(pPduTxData->TxConfPduId).WritePos + 1u) & CANTP_TX_QUEUE_MASK); /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
      lCanIfResult = CANTP_TX_OK;
    }
    /* else: queue is full; transmission will be automatically retried on task level */
#endif
  }

  return lCanIfResult;
} /* CanTp_CanIfTransmitFrame() */



/***********************************************************************************************************************
 *  CanTp_RxInit()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxInit(CanTp_RxStatePtrType pTpRxState, CanTp_NotificationType NotifyCode, uint8 DetError, CanTp_ResetControlType ResetRequest)
{
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */

  uint8  lIndicationPduR = 0;
  PduIdType lRxHdl = pTpRxState->RxHdl;  /* store RxHdl so it is still available after RxState has been reset */
  
  /* If generic connections are available, store the metadata info, so it's available after RxState has been reset */
# if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  uint8 lSduMetadataLength   = pTpRxState->SduMetadataLength;
#  if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8 lFcPduMetadataLength = pTpRxState->FcPduMetadataLength;
#  endif
# endif

  /* --- Check for Pending CanIf Transmissions --- */
  if ((pTpRxState->ChannelState & CANTP_RXSTATE_WAIT_TXCONFFC_ANY) == CANTP_RXSTATE_WAIT_TXCONFFC_ANY)
  {
    /* #20 If pending, cancel transmission (either via TxQueue if configured, or directly in TxSemaphore and CanIf). */
# if (CANTP_TRANSMIT_QUEUE == STD_ON)
    CanTp_TxQueueCancel(lRxHdl, CANTP_DIR_RX);                                                                         /* SBSW_CANTP_TXQUEUCANCEL_CALL_RX */
# else
    /* no FC transmission request pending, only waiting for confirmation; release semaphore and cancel transmission */
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(lRxHdl) ).Handle    = CANTP_INVALID_HDL;                      /* SBSW_CANTP_RXINIT_WRITE_TXSEMAPHORE */
    CanTp_Data_TxSemaphore( CanTp_RxCfg_GetTxFcConfPduId(lRxHdl) ).Direction = CANTP_DIR_NONE;                         /* SBSW_CANTP_RXINIT_WRITE_TXSEMAPHORE */
    CanTp_CanIfCancelTransmit(CANTP_DIR_RX, lRxHdl, CanTp_RxCfg_GetLoLayerTxFcPduId(lRxHdl));
# endif
  }


  /* --- Reset channel --- */
  /* #30 Before resetting, check if PduR must be notified (depends on NotifyCode and ApplState). */
  if (NotifyCode != CANTP_NOTIFY_NORESULT)
  {
# if (CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON)
    if (pTpRxState->ApplState == CANTP_APPL_INFORMED)
# endif
    {
      lIndicationPduR = 1;
    }
  }


  /* --- Reset channel data --- */
  CanTp_RxInitState(pTpRxState);                                                                                       /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */

  if (ResetRequest == CANTP_RESET_BUT_KEEP_MAPPING)
  {
    /* restore back-link from channel to connection, as the channel is still needed */
    pTpRxState->RxHdl = lRxHdl;                                                                                        /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */

    /* If generic connections are available, restore the metadata information */
# if (CANTP_GENERIC_CONNECTIONS == STD_ON)
    pTpRxState->SduMetadataLength   = lSduMetadataLength;                                                              /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#  if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
    pTpRxState->FcPduMetadataLength = lFcPduMetadataLength;                                                            /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
#  endif
# endif

  }
# if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  else
  {
    /* channel no longer needed, completely remove the mapping */
    CanTp_Data_RxChannelMap(lRxHdl) = CANTP_INVALID_HDL;                                                               /* SBSW_CANTP_RXINIT_WRITE_CHANNELMAP */
    CanTp_NumRxChannelsAvail++;
  }
# endif

  /* --- Notify other BSW modules --- */
  /* #50 Notify PduR, if needed. */
  if (lIndicationPduR != 0u)
  {
    CanTp_PduRRxIndication(CanTp_RxCfg_GetPduRRxSduId(lRxHdl), NotifyCode);
  }

  /* #60 Report failed receptions also to DET (reception is failed if DetError != no error). */
  if (DetError != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_RXINIT, DetError)
  }

#else
CANTP_DUMMY_STATEMENT(pTpRxState);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
CANTP_DUMMY_STATEMENT(NotifyCode);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
CANTP_DUMMY_STATEMENT(DetError);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
CANTP_DUMMY_STATEMENT(ResetRequest);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
} /* CanTp_RxInit() */



/***********************************************************************************************************************
 *  CanTp_TxInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxInit(CanTp_TxStatePtrType pTpTxState, CanTp_NotificationType NotifyCode, uint8 DetError)
{
#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */

  PduIdType lTxHdl = pTpTxState->TxHdl;  /* store TxHdl so it is still available after TxState have been reset */
  CANTP_DUMMY_STATEMENT(lTxHdl);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* --- Check for Pending CanIf Transmissions --- */
  if ((pTpTxState->ChannelState & CANTP_TXSTATE_WAIT_TXCONF_ANY) == CANTP_TXSTATE_WAIT_TXCONF_ANY)
  {
    /* #20 If pending, cancel transmission (either via TxQueue if configured, or directly in TxSemaphore and CanIf). */
# if (CANTP_TRANSMIT_QUEUE == STD_ON)
    /* other channels may be blocked and may have been queued */
    CanTp_TxQueueCancel(lTxHdl, CANTP_DIR_TX);                                                                         /* SBSW_CANTP_TXQUEUCANCEL_CALL_TX */
# else
    /* waiting for confirmation; release semaphore and cancel transmission */
    CanTp_Data_TxSemaphore( CanTp_TxCfg_GetTxConfPduId(lTxHdl) ).Handle = CANTP_INVALID_HDL;                           /* SBSW_CANTP_TXINIT_WRITE_TXSEMAPHORE */
    CanTp_Data_TxSemaphore( CanTp_TxCfg_GetTxConfPduId(lTxHdl) ).Direction = CANTP_DIR_NONE;                           /* SBSW_CANTP_TXINIT_WRITE_TXSEMAPHORE */
    CanTp_CanIfCancelTransmit(CANTP_DIR_TX, lTxHdl, CanTp_TxCfg_GetLoLayerTxPduId(lTxHdl));
# endif
  }


  /* --- Reset channel data --- */
  CanTp_TxInitState(pTpTxState);                                                                                       /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
# if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  CanTp_Data_TxChannelMap(lTxHdl) = CANTP_INVALID_HDL;                                                                 /* SBSW_CANTP_TXINIT_WRITE_CHANNELMAP */
  CanTp_NumTxChannelsAvail++;
# endif


  /* --- Notify other BSW modules --- */
  /* #40 Notify PduR of the transmission result. */
  CanTp_PduRTxConfirmation(CanTp_TxCfg_GetPduRTxSduId(lTxHdl), NotifyCode);

  /* #50 Report failed transmissions also to DET (transmission is failed if  DetError != no error). */
  if (DetError != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_TXINIT, DetError)
  }

#else
  CANTP_DUMMY_STATEMENT(pTpTxState);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  CANTP_DUMMY_STATEMENT(NotifyCode);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  CANTP_DUMMY_STATEMENT(DetError);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
} /* CanTp_TxInit() */



/***********************************************************************************************************************
 *  CanTp_ResetChannels()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_ResetChannels(void)
{
  {
    PduIdType  lSduHdl;

    /* #10 Iterate through all configured Rx N-SDUs; for each do the following: */
    for (lSduHdl = 0; lSduHdl < CanTp_Cfg_GetNumRxHdls(); lSduHdl++)
    {
#if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
      /* #20 In case of dynamic channel assignment: reset Rx SDU-to-channel mapping. */
      CanTp_Data_RxChannelMap(lSduHdl) = CANTP_INVALID_HDL;                                                            /* SBSW_CANTP_RESETCHANNELS_WRITE_RXHDL */
#endif

#if (CANTP_ENABLE_CHANGE_PARAM == STD_ON)
      /* #40 Reset dynamic FC parameters, if available. */
      CanTp_Data_DynFcParam(lSduHdl).BS    = CanTp_RxCfg_GetBS(lSduHdl);                                               /* SBSW_CANTP_RESETCHANNELS_WRITE_RXHDL */
      CanTp_Data_DynFcParam(lSduHdl).STmin = CanTp_RxCfg_GetSTmin(lSduHdl);                                            /* SBSW_CANTP_RESETCHANNELS_WRITE_RXHDL */
#endif
    }

#if (CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
    /* #50 Iterate through all configured Tx N-SDUs; for each do the following: */
    for (lSduHdl = 0; lSduHdl < CanTp_Cfg_GetNumTxHdls(); lSduHdl++)
    {
      /* #60 In case of dynamic channel assignment: reset Tx SDU-to-channel mapping. */
      CanTp_Data_TxChannelMap(lSduHdl) = CANTP_INVALID_HDL;                                                            /* SBSW_CANTP_RESETCHANNELS_WRITE_TXHDL */
    }
#endif
  }

  /* --- Reset channel specific data --- */
  {
    PduIdType  lChannelHdl;

    /* #110 Always initialize all the Rx channels. */
    for (lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumRxChannels(); lChannelHdl++)
    {
      CanTp_RxInitState(&CanTp_Data_RxState(lChannelHdl));                                                             /* SBSW_CANTP_RXINITSTATE_CALL_CHANNELHDL */
    }

    /* #120 Always initialize all the Tx channels. */
    for (lChannelHdl = 0; lChannelHdl < CanTp_Cfg_GetNumTxChannels(); lChannelHdl++)
    {
      CanTp_TxInitState(&CanTp_Data_TxState(lChannelHdl));                                                             /* SBSW_CANTP_TXINITSTATE_CALL_CHANNELHDL */
    }
  }

#if(CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
  /* #130 In case of dynamic channel assignment: Reset the number of available channels. */
  CanTp_NumRxChannelsAvail = CanTp_Cfg_GetNumRxChannels();
  CanTp_NumTxChannelsAvail = CanTp_Cfg_GetNumTxChannels();
#endif

  /* #200 Iterate through all configured Tx N-PDUs; for each do the following: */
  {
    PduIdType  lTxConfHdl;

    for (lTxConfHdl = 0; lTxConfHdl < CanTp_Cfg_GetNumTxConfPdus(); lTxConfHdl++)
    {
      /* #210 Reset the transmit semaphore of the N-PDU. */
      CanTp_Data_TxSemaphore(lTxConfHdl).Handle     = CANTP_INVALID_HDL;                                               /* SBSW_CANTP_RESETCHANNELS_WRITE_TXSEMAPHORE */
      CanTp_Data_TxSemaphore(lTxConfHdl).Direction  = CANTP_DIR_NONE;                                                  /* SBSW_CANTP_RESETCHANNELS_WRITE_TXSEMAPHORE */

#if (CANTP_TRANSMIT_QUEUE == STD_ON)
      {
        /* #220 Reset the Tx queue entry of the N-PDU (if configured). */
        uint8 lQueueCntr;

        CanTp_Data_TxQueue(lTxConfHdl).ReadPos = 0;                                                                    /* SBSW_CANTP_RESETCHANNELS_WRITE_TXSEMAPHORE */
        CanTp_Data_TxQueue(lTxConfHdl).WritePos = 0;                                                                   /* SBSW_CANTP_RESETCHANNELS_WRITE_TXSEMAPHORE */

        for (lQueueCntr = 0; lQueueCntr < CANTP_TX_QUEUE_SIZE; lQueueCntr++)
        {
          CanTp_Data_TxQueue(lTxConfHdl).Entries[lQueueCntr].SduHandle = CANTP_INVALID_HDL;                            /* SBSW_CANTP_RESETCHANNELS_WRITE_TXSEMAPHORE */  /* SBSW_CANTP_RESETCHANNELS_WRITE_QUEUEENTRY */
        }
      }
#endif
    }
  }
} /* CanTp_ResetChannels() */



/***********************************************************************************************************************
 *  CanTp_RxGetBuffer()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxGetBuffer(CanTp_RxStatePtrType pTpRxState)
{
  PduInfoType             lPduInfo;

  /* --- Get new buffer --- */
  if (pTpRxState->BufferState == CANTP_BUFREQ_E_BUSY)
  {
    lPduInfo.SduLength = 0;
    pTpRxState->BufferState = (CanTp_BufferStateType)CanTp_PduRCopyRxData(CanTp_RxCfg_GetPduRRxSduId(pTpRxState->RxHdl), /* CanTpRxPduId */ /* SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                                           &lPduInfo,                                    /* PduInfoPtr   */
                                                                           &pTpRxState->ProvidedBufferSize);             /* RxBufSizePtr */
  }


  /* --- Dispatch buffer processing --- */
  switch (pTpRxState->ChannelState)
  {
    case CANTP_RXSTATE_WAIT_BUFFER_SF:
      /* buffer handling after SF reception */
      CanTp_RxGetBufferSF(pTpRxState);                                                                                 /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    case CANTP_RXSTATE_WAIT_BUFFER_FF:
      /* buffer handling after FF reception */
      CanTp_RxGetBufferFF(pTpRxState);                                                                                 /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    case CANTP_RXSTATE_WAIT_BUFFER_CF:
      /* buffer handling after CF reception */
      CanTp_RxGetBufferCF(pTpRxState);                                                                                 /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    case CANTP_RXSTATE_WAIT_NEXT_FCWAIT:
      /* buffer handling between FC.WT transmissions */
      CanTp_RxGetBufferFCWait(pTpRxState);                                                                             /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      break;

    default:                                                                                                           /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* #30 If the ChannelState is neither "wait for XX buffer" nor "wait for next FC.WAIT": report DET error. */
      CanTp_DetReportError(CANTP_SID_RXGETBUFFER, CANTP_E_INVALID_RX_STATE)
      break;
  } /* switch(ChannelState) */
} /* CanTp_RxGetBuffer() */



/***********************************************************************************************************************
 *  CanTp_TxGetBuffer()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxGetBuffer(CanTp_TxStatePtrType pTpTxState)                                  /* PRQA S 2889 */ /* MD_CanTp_ReturnPaths */
{
#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */

  PduInfoType               lPduInfo;
  CanTp_TxChannelStateType  lNewChannelState;
  PduLengthType             lRemainingBufferSize;

  /* --- Prepare for buffer request and transmission --- */
  switch (pTpTxState->ChannelState)
  {
    case CANTP_TXSTATE_WAIT_BUFFER_SF:
      /* #20 Wait for SF Buffer: length is the overall data length. */
      pTpTxState->PayloadLength = (uint8)pTpTxState->DataLength;                                                       /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      lNewChannelState = CANTP_TXSTATE_TRANSMIT_SF;
      break; /* SF */

    case CANTP_TXSTATE_WAIT_BUFFER_FF:
      /* #30 Wait for FF Buffer: length is the max payload length of a FF or LFF (if configured and needed). */
# if (CANTP_SUPPORT_LONG_FF == STD_ON)
      if (pTpTxState->DataLength > CANTP_FF_DL_12BIT)
      {
        /* a long first frame is used; adjust payload */
        pTpTxState->PayloadLength = CanTp_TxCfg_GetMaxPayloadLFF(pTpTxState->TxHdl);                                   /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      }
      else
# endif
      {
        pTpTxState->PayloadLength = CanTp_TxCfg_GetMaxPayloadFF(pTpTxState->TxHdl);                                    /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      }
      lNewChannelState = CANTP_TXSTATE_TRANSMIT_FF;
      break; /* FF */

    case CANTP_TXSTATE_WAIT_BUFFER_CF:
      /* #40 Wait for CF Buffer: length is the max payload length of a CF or (for the last CF) the remaining length. */
      pTpTxState->PayloadLength = CanTp_TxCfg_GetMaxPayloadCF(pTpTxState->TxHdl);                                      /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      lNewChannelState = CANTP_TXSTATE_TRANSMIT_CF;

      if ((pTpTxState->DataIndex + pTpTxState->PayloadLength) > pTpTxState->DataLength)
      {
        /* last CF: reduce payload */
        pTpTxState->PayloadLength = (uint8)(pTpTxState->DataLength - pTpTxState->DataIndex);                           /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      }
      break; /* CF */

    default:
      /* #50 Any other state: report DET error and exit. */
      CanTp_DetReportError(CANTP_SID_TXGETBUFFER, CANTP_E_INVALID_TX_STATE)
      return;
  } /* switch(ChannelState) */


  /* --- Get payload and start transmission --- */
  lPduInfo.SduDataPtr = &pTpTxState->Payload[0];
  lPduInfo.SduLength  =  pTpTxState->PayloadLength;
  pTpTxState->BufferState = CanTp_PduRCopyTxData(CanTp_TxCfg_GetPduRTxSduId(pTpTxState->TxHdl),                        /* SBSW_CANTP_PDURCOPYTXDATA_CALL_PDUINFO */ /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
                                                  &lPduInfo,
                                                  NULL_PTR,                   /* retry not supported (CANTP272) */
                                                  &lRemainingBufferSize);     /* remaining number of bytes not important for CanTp */

  if (pTpTxState->BufferState == CANTP_BUFREQ_OK)
  {
    /* #70 If request succeeded: continue with transmission of the according frame (call CanTp_TxTransmitFrame). */
    pTpTxState->Timer        = CanTp_TxCfg_GetNAs(pTpTxState->TxHdl);                                                  /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
    pTpTxState->ChannelState = lNewChannelState;                                                                       /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
    CanTp_TxTransmitFrame(pTpTxState);                                                                                 /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
  }
  else
  {
    if (pTpTxState->BufferState != CANTP_BUFREQ_E_BUSY)
    {
      /* #80 If request failed: reset connection with buffer error. */
      CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_TX_BUFFER);                                     /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
    }
    /* #90 If request returned status busy: do nothing, retry is done on task level. */
  }

#else
  CANTP_DUMMY_STATEMENT(pTpTxState);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
} /* CanTp_TxGetBuffer() */



/***********************************************************************************************************************
 *  CanTp_RxTransmitFrame()
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
 *
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_RxTransmitFrame(CanTp_RxStatePtrType pTpRxState)
{
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */

  CanTp_TxResultType      lTxResult;
  PduInfoType             lFCFrameData;
  uint8                   lFCBuffer[CANTP_FRAME_FC_MAX_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH];   /* although 4 bytes are sufficient for FC, frame may be extended to 8 byte by padding and metadata could also be appended */
  uint8                   lBlockSizeValue;
  boolean                 lTransmitFC;

  /* a FC have to be transmitted */
  lTransmitFC = TRUE;
  lFCFrameData.SduDataPtr = lFCBuffer;
  lFCFrameData.SduLength  = 0;

  /* --- Add Addressing Information --- */
  /* #10 In case of Extended, Mixed11 or Mixed29 addressing, write the address to the first byte of the CAN frame buffer. */
# if (CANTP_RX_CHECK_ADDRESSING_FORMAT == STD_ON)
  if (CanTp_RxGetAdrOffset(pTpRxState->RxHdl) != 0u)
# endif
# if ((CANTP_RX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_RX_HAS_MIXED29_ADDRESSING == STD_ON))
  {
    lFCFrameData.SduDataPtr[0] = CanTp_Util_RxGetFCInPayloadAddressInfo(pTpRxState);                                     /* SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR */ /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
    lFCFrameData.SduLength++;
  }
# endif

  /* get configured Block Size */
  lBlockSizeValue = CanTp_RxGetCurrentBS(pTpRxState->RxHdl);

  /* #20 Add the FC protocol information depending on the flow status to be transmitted (indicated by the channel state). */
  switch(pTpRxState->ChannelState)
  {
    /* #30 Assemble FC.CTS: */
    case CANTP_RXSTATE_TRANSMIT_FC_CTS:

      if (lBlockSizeValue != 0u)
      {
# if (CANTP_CONSTANT_BS == STD_ON)
        if (CanTp_Data_CalcBS(pTpRxState->RxHdl) != 0u)
        {
          /* use the initially calculated BS */
          lBlockSizeValue = CanTp_Data_CalcBS(pTpRxState->RxHdl);
        }
        else
# endif
        {
          uint16 lBytesPerBlock;

          /* calculate BS depending on available buffer */
          lBytesPerBlock = ((uint16)lBlockSizeValue) * CanTp_RxCfg_GetMaxPayloadCF(pTpRxState->RxHdl);
          if ( (pTpRxState->ProvidedBufferSize < lBytesPerBlock) &&                                      /* buffer too small for next block */
               (pTpRxState->ProvidedBufferSize < (pTpRxState->DataLength - pTpRxState->DataIndex)) )     /* buffer too small for last block */
          {
            /* Provided length is insufficient, reduce next block */
            lBlockSizeValue = (uint8)(pTpRxState->ProvidedBufferSize / CanTp_RxCfg_GetMaxPayloadCF(pTpRxState->RxHdl));

            /* FC.CTS is only sent if he provided buffer is sufficient for at least one CF, so the calculated */
            /* block size should always be >= 1; check that this is still valid after future changes          */
            CanTp_DetAssert(lBlockSizeValue >= 1u, CANTP_SID_RXTRANSMITFRAME, CANTP_E_INVALID_RX_BUFFER)
          }
          /* else: provided length is enough for next or last block: take the configured (or already calculated) BS */

# if (CANTP_CONSTANT_BS == STD_ON)
          /* store calculated value for later use when transmitting the next FC */
          CanTp_Data_CalcBS(pTpRxState->RxHdl) = lBlockSizeValue;                                                      /* SBSW_CANTP_INTERNAL_WRITE_CALCBS */
# endif
        } /* Calculate BS */
      } /* BS != 0 */

      /* #50 Add flow control protocol info = 0x30. Values of STmin and BS will be added later. */
      lFCFrameData.SduDataPtr[lFCFrameData.SduLength] = CANTP_PCI_TYPE_FC;                                             /* SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR */

      /* Load internal BS counter */
      pTpRxState->BlocksizeCounter = lBlockSizeValue;                                                                  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
      break; /* FC.CTS */


    /* --- Assemble FC.WAIT --- */
    case CANTP_RXSTATE_TRANSMIT_FC_WT:
      /* #60 FC.WAIT: check WFTmax counter. */
      if (pTpRxState->WFTCounter > 0u )
      {
        /* #70 If counter > 0: assemble flow control with protocol info = 0x31. Values of STmin and BS will be added later. */
        lFCFrameData.SduDataPtr[lFCFrameData.SduLength] = (CANTP_PCI_TYPE_FC | CANTP_FLOWSTATUS_WT);                   /* SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR */
      }
      else
      {
        /* #80 If counter = 0: reset connection, as wait frames are either not supported or limit is reached. */
        lTransmitFC = FALSE;
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_WFT_OVERRUN, CANTP_E_RX_WFTMAX, CANTP_RESET_ALL);                        /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      break; /* FC.WAIT */


    /* --- Assemble FC.OVFL --- */
    case CANTP_RXSTATE_TRANSMIT_FC_OVFL:
      /* #90 FC.OVFL: assemble flow control with protocol info = 0x32. Values of STmin and BS will be added later. */
      lFCFrameData.SduDataPtr[lFCFrameData.SduLength] = (CANTP_PCI_TYPE_FC | CANTP_FLOWSTATUS_OVFL);                   /* SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR */
      break; /* FC.OVFL */


    /* #100 Any other channel state is invalid, report DET error and exit. */
    default:
      CanTp_DetReportError(CANTP_SID_RXTRANSMITFRAME, CANTP_E_INVALID_RX_STATE)
      lTransmitFC = FALSE;
      break;
  } /* switch(ChannelState) */


  /* #105 If a frame was successfully assembled and has to be transmitted: */
  if (lTransmitFC == TRUE)
  {
    CanTp_PduTxInfoType  lPduTxInfo;

    /* #110 finalize FC frame with the BS value and the configured STmin. */
    lFCFrameData.SduDataPtr[lFCFrameData.SduLength + CANTP_FRAME_OFFSET_FC_BS ]   = lBlockSizeValue;                   /* BS */       /* SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR */
    lFCFrameData.SduDataPtr[lFCFrameData.SduLength + CANTP_FRAME_OFFSET_FC_STMIN] = CanTp_RxGetCurrentSTmin(pTpRxState->RxHdl);    /* STmin */    /* SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR */
    lFCFrameData.SduLength += CANTP_PCI_LENGTH_FC;

    /* --- Transmit FC --- */
    lPduTxInfo.SduDirection  = CANTP_DIR_RX;
    lPduTxInfo.SduHdl        = pTpRxState->RxHdl;
    lPduTxInfo.TxPduId       = CanTp_RxCfg_GetLoLayerTxFcPduId(pTpRxState->RxHdl);
    lPduTxInfo.TxConfPduId   = CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl);

# if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
    lPduTxInfo.PaddingLength = CanTp_Util_GetPaddingLength((uint8)lFCFrameData.SduLength, CanTp_RxCfg_HasPaddingActivation(pTpRxState->RxHdl), CanTp_RxCfg_GetCanType(pTpRxState->RxHdl));
# endif

    /* #120 If required, append the fc-PDU metadata information. */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
    lPduTxInfo.PduMetadata = pTpRxState->FcPduMetadata;
    lPduTxInfo.PduMetadataLength = pTpRxState->FcPduMetadataLength;
# endif


    lTxResult = CanTp_CanIfTransmitFrame(&lPduTxInfo, &lFCFrameData);                                                  /* SBSW_CANTP_CANIFTRANSMITFRAME_CALL_FCDATA */

    if (lTxResult == CANTP_TX_OK)
    {
      /* #210 If transmission was successful, switch channel state to "wait for confirmation". */
      pTpRxState->ChannelState = (CanTp_RxChannelStateType)((pTpRxState->ChannelState  & CANTP_RXSTATE_TRANSMIT_FC_ANY_MASK) /* clear transmission bit */  /* SBSW_CANTP_INTERNAL_WRITE_RXSTATE */
                                                            | CANTP_RXSTATE_WAIT_TXCONFFC_ANY);                              /* set TxConfirmation bit */
    }
    else
    {
      if (lTxResult == CANTP_TX_NOT_OK)
      {
        /* #220 If transmission failed, reset connection. */
        CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NOT_OK, CANTP_E_RX_TRANSMIT_ERROR, CANTP_RESET_ALL);                     /* SBSW_CANTP_INTERNAL_CALL_RXSTATE */
      }
      /* else: CANTP_TX_BUSY, do not change state and retry on task level */
    }
  }

#else
  CANTP_DUMMY_STATEMENT(pTpRxState);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
} /* CanTp_RxTransmitFrame() */  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */



/***********************************************************************************************************************
 *  CanTp_TxTransmitFrame()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxTransmitFrame(CanTp_TxStatePtrType pTpTxState)                              /* PRQA S 2889 */ /* MD_CanTp_ReturnPaths */
{
  PduInfoType             lTxFrameData;
  uint8                   lTxFrameDataBuffer[CANTP_MAX_FRAME_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH];
  CanTp_PduTxInfoType     lPduTxInfo;
  Std_ReturnType          lTxResult;


  lTxFrameData.SduDataPtr = lTxFrameDataBuffer;
  lTxFrameData.SduLength  = 0;

  /* --- Add Addressing Information --- */
#if (CANTP_TX_CHECK_ADDRESSING_FORMAT == STD_ON)
  if (CanTp_TxGetAdrOffset(pTpTxState->TxHdl) != 0u)
#endif
#if ((CANTP_TX_HAS_EXTENDED_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED11_ADDRESSING == STD_ON) || (CANTP_TX_HAS_MIXED29_ADDRESSING == STD_ON))
  {
    lTxFrameData.SduDataPtr[0] = CanTp_Util_TxGetInPayloadAddressInfo(pTpTxState);                                     /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */ /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
    lTxFrameData.SduLength++;
  }
#endif

  switch(pTpTxState->ChannelState)
  {
    /* --- Assemble SF --- */
    case CANTP_TXSTATE_TRANSMIT_SF:
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength]  = CANTP_PCI_TYPE_SF;                                            /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */

#if (CANTP_TX_HAS_CANFD == STD_ON)
      if ((CANTP_PCI_LENGTH_SF + lTxFrameData.SduLength + pTpTxState->PayloadLength) > CANTP_CAN20_FRAME_LENGTH)
      {
        /* #40 If (PCI + address offset + payload) > 8: use long SF format. */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 1u] = (uint8)(pTpTxState->DataLength);                         /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_LSF;
      }
      else
#endif
      {
        /* #50 Otherwise: prepare standard SF format. */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength] |= (uint8)((pTpTxState->DataLength) & CANTP_MASK_SF_LENGTH);   /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_SF;
      }
      break; /* SF */


    /* --- Assemble FF --- */
    case CANTP_TXSTATE_TRANSMIT_FF:
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength]  = CANTP_PCI_TYPE_FF;                                            /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */

#if (CANTP_SUPPORT_LONG_FF == STD_ON)
      if (pTpTxState->DataLength > CANTP_FF_DL_12BIT)
      {
        /* #70 If supported and if the requested DataLength is > 4095: use long FF format. */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 1u] = 0;  /* escape sequence */                               /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
# if (CANTP_SIZEOF_PDULENGTHTYPE < 4)
        /* DataLength is only uint16; upper 2 bytes are unused */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 2u] = 0;                                                      /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 3u] = 0;                                                      /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 4u] = CanTp_Util_GetHiByte(pTpTxState->DataLength);           /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 5u] = CanTp_Util_GetLoByte(pTpTxState->DataLength);           /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
# else
        /* full 32Bit support is enabled */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 2u] = CanTp_Util_GetHiHiByte(pTpTxState->DataLength);         /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 3u] = CanTp_Util_GetHiLoByte(pTpTxState->DataLength);         /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 4u] = CanTp_Util_GetLoHiByte(pTpTxState->DataLength);         /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 5u] = CanTp_Util_GetLoLoByte(pTpTxState->DataLength);         /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
# endif
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_LFF;
      }
      else
#endif
      {
        /* #80 Otherwise use standard FF format. */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength]     |= (uint8)(CanTp_Util_GetHiByte(pTpTxState->DataLength) & CANTP_MASK_FF_LENGTH); /* PRQA S 2985 */ /* MD_CanTp_RedundantOperation */ /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduDataPtr[lTxFrameData.SduLength + 1u]  = (uint8)(CanTp_Util_GetLoByte(pTpTxState->DataLength)); /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
        lTxFrameData.SduLength += CANTP_PCI_LENGTH_FF;
      }

      pTpTxState->SeqNumber        = CANTP_SN_FIRST_CF; /* Set SN to initial starting number */                        /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      pTpTxState->BlocksizeCounter = 0; /* Is calculate on transition to CANTP_TXSTATE_WAIT_FC */                      /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      pTpTxState->DataIndex        = 0;                                                                                /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
      break; /* FF */


    /* --- Assemble CF --- */
    case CANTP_TXSTATE_TRANSMIT_CF:
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength]  = CANTP_PCI_TYPE_CF;                                            /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
      lTxFrameData.SduDataPtr[lTxFrameData.SduLength] |= (uint8) (pTpTxState->SeqNumber);                              /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */
      lTxFrameData.SduLength += CANTP_PCI_LENGTH_CF;
      break; /* CF */


    /* #100 Any other channel state is invalid, report DET error and exit. */
    default:
      CanTp_DetReportError(CANTP_SID_TXTRANSMITFRAME, CANTP_E_INVALID_TX_STATE)
      return;
  } /* switch(ChannelState) */


  /* --- Add Payload --- */
  CanTp_Util_MemCpy((P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(&lTxFrameData.SduDataPtr[lTxFrameData.SduLength]),      /* SBSW_CANTP_MEMCPY_CALL_TXFRAMEDATA */
                    (P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA))(pTpTxState->Payload),
                    pTpTxState->PayloadLength);
  lTxFrameData.SduLength += pTpTxState->PayloadLength;


  /* --- Transmit TP Frame --- */
  lPduTxInfo.SduDirection  = CANTP_DIR_TX;
  lPduTxInfo.SduHdl        = pTpTxState->TxHdl;
  lPduTxInfo.TxPduId       = CanTp_TxCfg_GetLoLayerTxPduId(pTpTxState->TxHdl);
  lPduTxInfo.TxConfPduId   = CanTp_TxCfg_GetTxConfPduId(pTpTxState->TxHdl);

#if (CANTP_PADDING_SUPPORT_REQUIRED == STD_ON)
  lPduTxInfo.PaddingLength = CanTp_Util_GetPaddingLength((uint8)lTxFrameData.SduLength,
                                                         CanTp_TxCfg_HasPaddingActivation(pTpTxState->TxHdl),
                                                         CanTp_TxCfg_GetCanType(pTpTxState->TxHdl));
#endif

  /* #115 If required, append the data-PDU metadata information. */
#if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  lPduTxInfo.PduMetadata = pTpTxState->DataPduMetadata;
  lPduTxInfo.PduMetadataLength = pTpTxState->DataPduMetadataLength;
#endif

  lTxResult = CanTp_CanIfTransmitFrame(&lPduTxInfo, &lTxFrameData);                                                    /* SBSW_CANTP_CANIFTRANSMITFRAME_CALL_TXDATA */ /* SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR */

  if (lTxResult == CANTP_TX_OK)
  {
    /* #130 If transmission was successful, switch channel state to "wait for confirmation". */
    pTpTxState->ChannelState = (CanTp_TxChannelStateType)((pTpTxState->ChannelState  & CANTP_TXSTATE_TRANSMIT_ANY_MASK)     /* clear transmission bit */ /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
                                                          | CANTP_TXSTATE_WAIT_TXCONF_ANY);                                 /* set TxConfirmation bit */
    pTpTxState->DataIndex = pTpTxState->DataIndex + pTpTxState->PayloadLength;                                         /* SBSW_CANTP_INTERNAL_WRITE_TXSTATE */
  }
  else
  {
    if (lTxResult == CANTP_TX_NOT_OK)
    {
      /* #140 If transmission failed, reset connection. */
      CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NOT_OK, CANTP_E_TX_TRANSMIT_ERROR);                                        /* SBSW_CANTP_INTERNAL_CALL_TXSTATE */
    }
    /* else: CANTP_TX_BUSY, do not change state and retry on task level */
  }
} /* CanTp_TxTransmitFrame () */



#if (CANTP_RX_HAS_HALF_DUPLEX == STD_ON)
/***********************************************************************************************************************
 *  CanTp_RxCheckChannelMode()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_RxCheckChannelMode(PduIdType RxHdl)
{
  Std_ReturnType  lResult;
  CANTP_DUMMY_STATEMENT(RxHdl);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  if (!CanTp_RxSdu2TxSduRefIsAvailable(RxHdl))                                                                         /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    /* no Tx connection defined for this channel */
    lResult = E_OK;                                                                                                    /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# if (CANTP_RX_CHECK_HALF_DUPLEX == STD_ON)
  else if (CANTP_MODE_FULL_DUPLEX == CanTp_RxCfg_GetChannelMode(RxHdl))
  {
    /* full duplex: both directions are allowed */
    lResult = E_OK;
  }
# endif
  else if (CanTp_TxChannelIsIdle(CanTp_RxCfg_GetTxSduHdl(RxHdl)))
  {
    /* Tx channel is idle, half duplex communication can be started */
    lResult = E_OK;
  }
  else
  {
    /* half duplex, but channel is already in use */
    lResult = E_NOT_OK;
  }
  return lResult;
} /* CanTp_RxCheckChannelMode() */
#endif /* CANTP_RX_HAS_HALF_DUPLEX == STD_ON */



#if (CANTP_TX_HAS_HALF_DUPLEX == STD_ON)
/***********************************************************************************************************************
 *  CanTp_TxCheckChannelMode()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxCheckChannelMode(PduIdType TxHdl)
{
  Std_ReturnType  lResult;
  CANTP_DUMMY_STATEMENT(TxHdl);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  if (!CanTp_TxSdu2RxSduRefIsAvailable(TxHdl))                                                                         /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    /* no Tx connection defined for this channel */
    lResult = E_OK;                                                                                                    /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# if (CANTP_TX_CHECK_HALF_DUPLEX == STD_ON)
  else if (CANTP_MODE_FULL_DUPLEX == CanTp_TxCfg_GetChannelMode(TxHdl))
  {
    /* full duplex: both directions are allowed */
    lResult = E_OK;
  }
# endif
  else if (CanTp_RxChannelIsIdle(CanTp_TxCfg_GetRxSduHdl(TxHdl)) == TRUE)
  {
    /* Tx channel is idle, half duplex communication can be started */
    lResult = E_OK;
  }
  else
  {
    /* half duplex, but channel is already in use */
    lResult = E_NOT_OK;
  }
  return lResult;
} /* CanTp_TxCheckChannelMode() */
#endif /* CANTP_TX_HAS_HALF_DUPLEX == STD_ON */



#if (CANTP_TRANSMIT_QUEUE == STD_ON)
/***********************************************************************************************************************
 *  CanTp_TxQueueProcess()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueProcess(PduIdType TxConfPduId)
{
  PduInfoType          lPduInfo;
  PduIdType            lQueuedHandle;
  PduIdType            lQueuedPduId;
  CanTp_DirectionType  lQueuedDirection;
  CanTp_TxResultType   lCanIfResult;


  /* #10 If current TxQueue entry is not empty and N-PDU can be transmitted (semaphore is free): */
  if (CanTp_TxQueueEntryReadPos(TxConfPduId).SduHandle != CANTP_INVALID_HDL)
  {
    if (CanTp_Data_TxSemaphore(TxConfPduId).Handle == CANTP_INVALID_HDL)
    {
  /* #20 Transmit queued N-PDU and remove entry from queue. */
      lPduInfo.SduLength  = CanTp_TxQueueEntryReadPos(TxConfPduId).SduLength;
      lPduInfo.SduDataPtr = CanTp_TxQueueEntryReadPos(TxConfPduId).SduData;
      lQueuedPduId        = CanTp_TxQueueEntryReadPos(TxConfPduId).PduId;
      lQueuedHandle       = CanTp_TxQueueEntryReadPos(TxConfPduId).SduHandle;
      lQueuedDirection    = CanTp_TxQueueEntryReadPos(TxConfPduId).SduDirection;
      
      lCanIfResult = CanTp_CanIfTransmit(lQueuedDirection, lQueuedHandle, lQueuedPduId, &lPduInfo);                  /* SBSW_CANTP_CANIFTRANSMIT_CALL_TXQUEUE */
                                           
      CanTp_TxQueueEntryReadPos(TxConfPduId).SduHandle = CANTP_INVALID_HDL;                                            /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
      CanTp_Data_TxQueue(TxConfPduId).ReadPos = (uint8)((CanTp_Data_TxQueue(TxConfPduId).ReadPos + 1u) & CANTP_TX_QUEUE_MASK); /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */

      if (lCanIfResult == CANTP_TX_OK)
      {
        /* #30 If N-PDU has been successfully transmitted, lock its semaphore an call debugging call-out. */
        CanTp_Data_TxSemaphore(TxConfPduId).Handle    = lQueuedHandle;                                                 /* SBSW_CANTP_TXQUEUEPROCESS_WRITE_TXSEMAPHORE */
        CanTp_Data_TxSemaphore(TxConfPduId).Direction = lQueuedDirection;                                              /* SBSW_CANTP_TXQUEUEPROCESS_WRITE_TXSEMAPHORE */

        CanTp_ApplFrameTransmission(lQueuedPduId, &lPduInfo)                                                           /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */
      }
      else
      {
        /* #40 If N-PDU transmission failed, reset connection. */
        if (lQueuedDirection == CANTP_DIR_TX)
        {
          CanTp_TxInit(CanTp_TxGetChannelPtr(lQueuedHandle), CANTP_NOTIFY_NOT_OK, CANTP_E_TX_TRANSMIT_ERROR);          /* SBSW_CANTP_RXTXINIT_CALL_QUEUEDHDL */
        }
        else
        {
          CanTp_RxInit(CanTp_RxGetChannelPtr(lQueuedHandle), CANTP_NOTIFY_NOT_OK, CANTP_E_RX_TRANSMIT_ERROR, CANTP_RESET_ALL); /* SBSW_CANTP_RXTXINIT_CALL_QUEUEDHDL */
        }
      }
    }
    /* else: N-PDU is already sent by another N-SDU, retry later */
  }

  /* #50 If current TxQueue entry is empty, only switch to next entry. */
  else
  {
    CanTp_Data_TxQueue(TxConfPduId).ReadPos = (uint8)((CanTp_Data_TxQueue(TxConfPduId).ReadPos + 1u) & CANTP_TX_QUEUE_MASK); /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
  }
} /* CanTp_TxQueueProcess() */



/***********************************************************************************************************************
 *  CanTp_TxQueueCancel()
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
 **********************************************************************************************************************/
CANTP_LOCAL FUNC(void, CANTP_CODE) CanTp_TxQueueCancel(PduIdType SduHdl, CanTp_DirectionType Direction)
{
  PduIdType  lTxConfPduId;
  uint8      lQueueCntr;

  /* --- get RxPduId from SduHandle --- */
  if (Direction == CANTP_DIR_TX)
  {
    lTxConfPduId = CanTp_TxCfg_GetTxConfPduId(SduHdl);
  }
  else
  {
    lTxConfPduId = CanTp_RxCfg_GetTxFcConfPduId(SduHdl);
  }


  /* --- if N-PDU is processed by the CanIf: release semaphore and cancel transmission --- */
  if ((CanTp_Data_TxSemaphore(lTxConfPduId).Handle == SduHdl) &&
      (CanTp_Data_TxSemaphore(lTxConfPduId).Direction == Direction))
  {
    /* #30 Release semaphore and cancel N-PDU transmission. */
    CanTp_Data_TxSemaphore(lTxConfPduId).Handle    = CANTP_INVALID_HDL;                                                /* SBSW_CANTP_TXQUEUECANCEL_WRITE_TXSEMAPHORE */
    CanTp_Data_TxSemaphore(lTxConfPduId).Direction = CANTP_DIR_NONE;                                                   /* SBSW_CANTP_TXQUEUECANCEL_WRITE_TXSEMAPHORE */

# if (CANTP_LOLAYER_TC == STD_ON)
    if (Direction == CANTP_DIR_TX)
    {
      CanTp_CanIfCancelTransmit(CANTP_DIR_TX, SduHdl, CanTp_TxCfg_GetLoLayerTxPduId(SduHdl));
    }
    else
    {
      CanTp_CanIfCancelTransmit(CANTP_DIR_RX, SduHdl, CanTp_RxCfg_GetLoLayerTxFcPduId(SduHdl));
    }
#endif

    /* #40 If queue is not empty: try to transmit next entry (call CanTp_TxQueueProcess). */
    if (!CanTp_TxQueueIsEmpty(lTxConfPduId))
    {
      CanTp_TxQueueProcess(lTxConfPduId);
    }
  }
  else
  {
    /* --- if N-PDU is not processed by the CanIf: remove queue entry --- */
    /* #60 Search for matching queue entry and invalidate it. */
    lQueueCntr = CanTp_Data_TxQueue(lTxConfPduId).ReadPos;
    while (lQueueCntr != CanTp_Data_TxQueue(lTxConfPduId).WritePos)
    {
      if ((CanTp_Data_TxQueue(lTxConfPduId).Entries[lQueueCntr].SduHandle == SduHdl) &&
          (CanTp_Data_TxQueue(lTxConfPduId).Entries[lQueueCntr].SduDirection == Direction))
      {
        CanTp_Data_TxQueue(lTxConfPduId).Entries[lQueueCntr].SduHandle = CANTP_INVALID_HDL;                            /* SBSW_CANTP_TXQUEUECANCEL_WRITE_TXSEMAPHORE */ /* SBSW_CANTP_TXQUEUE_WRITE_ENTRY */
        break;
      }

      lQueueCntr = (uint8)((lQueueCntr + 1u) & CANTP_TX_QUEUE_MASK);
    }
  }
} /* CanTp_TxQueueCancel() */
#endif /* CANTP_TRANSMIT_QUEUE == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  CanTp_Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC, CANTP_INIT_DATA) CfgPtr)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
#if (CANTP_USE_INIT_POINTER == STD_ON)
  uint8  lErrorId = CANTP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* NULL pointer check is not always needed and is done later for ECUM error reporting */

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* config pointer is set immediately, but will only be used if the validity check below is passed */
  CanTp_Data_CfgPtr() = CfgPtr;

  /* post-build loadable: report errors to EcuM     */
  /* post-build selectable: only check init pointer */
  if (CfgPtr == NULL_PTR)
  {
    lErrorId = CANTP_E_PARAM_POINTER;
    CanTp_EcuMReportBswError(ECUM_BSWERROR_NULLPTR)
  }
# if (CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
  /* Check generator version compatibility: SPEC00035482 */
  else if (CANTP_GENERATOR_COMPATIBILITY_VERSION != CfgPtr->CompatibilityVersionOfPBConfig)
  {
    CanTp_EcuMReportBswError(ECUM_BSWERROR_COMPATIBILITYVERSION)
  }
  /* Check magic number: SPEC00035483 */
  else if (CANTP_FINAL_MAGIC_NUMBER != CfgPtr->FinalMagicNumberOfPBConfig)
  {
    CanTp_EcuMReportBswError(ECUM_BSWERROR_MAGICNUMBER)
  }
# endif
  else
#endif /* CANTP_USE_INIT_POINTER == STD_ON */
  {
    /* #25 Check validity of the current configuration */
    if (CanTp_Util_CheckConfigValidity() == TRUE)                                                                      /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */ /* COV_CANTP_SILENT_RUNTIME_CHECK */
    {
      /* #30 If all checks are passed, reset all channels and set module state to "initialized". */
      CanTp_ResetChannels();
      CanTp_Data_InitState() = CANTP_STATUS_INITIALIZED;
    }
    /* else: Silent BSW violation detected; DET is already reported within CanTp_Util_CheckConfigValidity() when a deviation is detected */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_USE_INIT_POINTER == STD_ON)
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_INIT, lErrorId)
  }
# else
  /* errors may occur, but aren't reported */
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
#else
  CANTP_DUMMY_STATEMENT(CfgPtr);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif /* CANTP_USE_INIT_POINTER == STD_ON */
} /* CanTp_Init() */



/***********************************************************************************************************************
 *  CanTp_InitMemory()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_InitMemory(void)
{
  /* ----- Implementation -------------------------------------------------------------------- */
  CanTp_Data_InitState() = CANTP_STATUS_NOT_INITIALIZED;
} /* CanTp_InitMemory() */



/***********************************************************************************************************************
 *  CanTp_Shutdown()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_Shutdown(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8  lErrorId = CANTP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #10 Always ensure that the CanTp is initialized (even with disabled DET). */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* #20 Reset all channels and set module state to "shutdown". */
    CanTp_ResetChannels();
    CanTp_Data_InitState() = CANTP_STATUS_SHUTDOWN;
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_SHUTDOWN, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* CanTp_Shutdown() */



#if (CANTP_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  CanTp_GetVersionInfo()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTP_APPL_DATA) versioninfo)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8  lErrorId = CANTP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_CANTP_DET_CHECK TX */
  /* CanTp_GetVersionInfo can be called before initialization of the CanTp module (see CANTP031)  */
  /* Only a NULL pointer check is required */
  if (versioninfo == NULL_PTR)
  {
    lErrorId = CANTP_E_PARAM_POINTER;
  }
  else
# endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* #20 Set versioninfo with corresponding macros from component header. */
    versioninfo->vendorID         = CANTP_VENDOR_ID;                                                                   /* SBSW_CANTP_GETVERSION_WRITE_VERSION */
    versioninfo->moduleID         = CANTP_MODULE_ID;                                                                   /* SBSW_CANTP_GETVERSION_WRITE_VERSION */

    versioninfo->sw_major_version = CANTP_SW_MAJOR_VERSION;                                                            /* SBSW_CANTP_GETVERSION_WRITE_VERSION */
    versioninfo->sw_minor_version = CANTP_SW_MINOR_VERSION;                                                            /* SBSW_CANTP_GETVERSION_WRITE_VERSION */
    versioninfo->sw_patch_version = CANTP_SW_PATCH_VERSION;                                                            /* SBSW_CANTP_GETVERSION_WRITE_VERSION */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_GETVERSIONINFO, lErrorId)
  }
# else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
} /* CanTp_GetVersionInfo() */
#endif /* CANTP_VERSION_INFO_API */



/***********************************************************************************************************************
 *  CanTp_MainFunction()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_MainFunction(void)
{
  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* init checks are done in the direction specific main functions, as these may also be called directly */

  /* ----- Implementation ---------------------------------------------------------------------- */
  CanTp_MainFunctionRx();
  CanTp_MainFunctionTx();
} /* CanTp_MainFunction() */



/***********************************************************************************************************************
 *  CanTp_MainFunctionRx()
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
 **********************************************************************************************************************/
FUNC(void,  CANTP_CODE)   CanTp_MainFunctionRx(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  PduIdType            lRxChannelHdl;
  CanTp_RxStatePtrType pTpRxState;

  /* #10 Ensure that the CanTp is initialized, but do not report an error (SWS_BSW_00037). */
  if (CanTp_Data_InitState() == CANTP_STATUS_INITIALIZED)
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* #20 For each active Rx channel: */
    for (lRxChannelHdl = 0; lRxChannelHdl < CanTp_Cfg_GetNumRxChannels(); lRxChannelHdl++)
    {
      pTpRxState = &CanTp_Data_RxState(lRxChannelHdl);
      /* is channel active (i.e.: occupied by a connection)? */
      if (pTpRxState->RxHdl != CANTP_INVALID_HDL)
      {
        CanTp_EnterCritical();  /* CanTp_MainFunctionRx ~~~~~~~~~~~~~~~~~~~~ */

        /* is it still active? */
        if (pTpRxState->RxHdl != CANTP_INVALID_HDL)
        {
          /* #30 Update channel timer. */
          pTpRxState->Timer--;                                                                                         /* SBSW_CANTP_TASK_WRITE_RXSTATE */

          if (pTpRxState->Timer == 0u)
          {
            /* #40  If timer expired (=0), do the timeout handling according to the current state. */
            switch (pTpRxState->ChannelState)
            {
              /* #50 State = wait for CF: N_Cr timeout occurred, reset connection. */
              case CANTP_RXSTATE_WAIT_CF:
                CanTp_RxInit(pTpRxState, CANTP_NOTIFY_TIMEOUT_C, CANTP_E_RX_TIMEOUT_CR, CANTP_RESET_ALL);              /* SBSW_CANTP_TASK_CALL_RXSTATE */
                break;

              /* #60 State = wait for transmission or TxConfirmation of FC.CTS or FC.WAIT: N_Ar timeout occurred, reset connection. */
              case CANTP_RXSTATE_TRANSMIT_FC_CTS:
              case CANTP_RXSTATE_TRANSMIT_FC_WT:
              case CANTP_RXSTATE_WAIT_TXCONFFC_CTS:
              case CANTP_RXSTATE_WAIT_TXCONFFC_WT:
                CanTp_RxInit(pTpRxState, CANTP_NOTIFY_TIMEOUT_A, CANTP_E_RX_TIMEOUT_AR, CANTP_RESET_ALL);              /* SBSW_CANTP_TASK_CALL_RXSTATE */
                break;

              /* #70 State = wait for transmission or TxConfirmation of FC.OVFL: N_Ar timeout after buffer error, reset connection. */
              case CANTP_RXSTATE_TRANSMIT_FC_OVFL:
              case CANTP_RXSTATE_WAIT_TXCONFFC_OVFL:
                /* coming here after RxBufferProvision returned NO_BUFFER and thus sending a FC.OVFL and missing confirmation. */
                CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);          /* SBSW_CANTP_TASK_CALL_RXSTATE */
                break;

              /* #90 State = wait for buffer. */
              case CANTP_RXSTATE_WAIT_BUFFER_SF:
              case CANTP_RXSTATE_WAIT_BUFFER_FF:
              case CANTP_RXSTATE_WAIT_BUFFER_CF:
                /* #100 Timeout during buffer request; try one last time to get an Rx buffer. */
                CanTp_RxGetBuffer(pTpRxState);                                                                         /* SBSW_CANTP_TASK_CALL_RXSTATE */

                /* #110 If after the call the buffer state is still busy: reset connection. */
                if (pTpRxState->BufferState == CANTP_BUFREQ_E_BUSY)
                {
                  CanTp_RxInit(pTpRxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_INVALID_RX_BUFFER, CANTP_RESET_ALL);        /* SBSW_CANTP_TASK_CALL_RXSTATE */
                }
                break;

              /* #120 State = wait for next FC.WAIT: trigger transmission of next FC.WAIT. */
              case CANTP_RXSTATE_WAIT_NEXT_FCWAIT:
                /* note: WFTmax is checked in CanTp_RxTransmitFrame()) */
                pTpRxState->Timer        = CanTp_RxCfg_GetNAr(pTpRxState->RxHdl);                                      /* SBSW_CANTP_TASK_WRITE_RXSTATE */
                pTpRxState->ChannelState = CANTP_RXSTATE_TRANSMIT_FC_WT;                                               /* SBSW_CANTP_TASK_WRITE_RXSTATE */
                CanTp_RxTransmitFrame(pTpRxState);                                                                     /* SBSW_CANTP_TASK_CALL_RXSTATE */
                break;

              /* #130 Any other state is invalid here, report DET error. */
              default:                                                                                                 /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
                CanTp_DetReportError(CANTP_SID_MAINFUNCTIONRX, CANTP_E_INVALID_RX_STATE)
                break;
            } /* switch(ChannelState) */
          }
          /* #140  If timer is not yet expired (!=0), check if any cyclic actions need to be done: */
          else
          {
#if (CANTP_TRANSMIT_QUEUE == STD_ON)
            /* #150 If N-PDU transmission is queued: try to transmit it now (call CanTp_TxQueueProcess). */
            /* Check this one first to be sure the channel is still active and pTpRxState->TxHdl is valid. If it would */
            /* be done later, CanTp_RxGetBuffer() and CanTp_RxTransmitFrame() may have reset the channel.              */
            /* However, it doesn't matter if the channel is reset in CanTp_TxQueueProcess(), because before the other  */
            /* calls below the channel state is checked anyway.                                                        */
            if ( (CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl) != CANTP_INVALID_HDL) &&
                 (!CanTp_TxQueueIsEmpty(CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl))) )
            {
              CanTp_TxQueueProcess(CanTp_RxCfg_GetTxFcConfPduId(pTpRxState->RxHdl));                                   /* SBSW_CANTP_TXQUEUEPROCESS_CALL_RX */
            }
#endif
            /* #160 If State = wait for buffer or wait for next FC.WAIT: try to get more Rx buffer. */
            if ( ((pTpRxState->ChannelState & CANTP_RXSTATE_WAIT_BUFFER_ANY) == CANTP_RXSTATE_WAIT_BUFFER_ANY) ||
                  (pTpRxState->ChannelState == CANTP_RXSTATE_WAIT_NEXT_FCWAIT) )
            {
              CanTp_RxGetBuffer(pTpRxState);                                                                           /* SBSW_CANTP_TASK_CALL_RXSTATE */
            }

            /* #170 If State = wait for transmission: N-PDU Tx request pending, retry transmission (call CanTp_RxTransmitFrame). */
            if ((pTpRxState->ChannelState & CANTP_RXSTATE_TRANSMIT_FC_ANY) == CANTP_RXSTATE_TRANSMIT_FC_ANY)
            {
              CanTp_RxTransmitFrame(pTpRxState);                                                                       /* SBSW_CANTP_TASK_CALL_RXSTATE */
            }
          }
        }
        /* else: channel not in use (secured check) */
        CanTp_LeaveCritical();  /* CanTp_MainFunctionRx ~~~~~~~~~~~~~~~~~~~~ */
      }
      /* else: channel not in use (preliminary check) */
    }
    /* end of loop through all connections */
  }
  /* else: CanTp not initialized */
} /* CanTp_MainFunctionRx() */  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */



/***********************************************************************************************************************
 *  CanTp_MainFunctionTx()
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
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_MainFunctionTx(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  PduIdType            lTxChannelHdl;
  CanTp_TxStatePtrType pTpTxState;

  /* #10 Ensure that the CanTp is initialized, but do not report an error (SWS_BSW_00037). */
  if (CanTp_Data_InitState() == CANTP_STATUS_INITIALIZED)
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* #20 For each active Tx channel: */
    for (lTxChannelHdl = 0; lTxChannelHdl < CanTp_Cfg_GetNumTxChannels(); lTxChannelHdl++)
    {
      pTpTxState = &CanTp_Data_TxState(lTxChannelHdl);
      /* is channel active (i.e.: occupied by a connection)? */
      if (pTpTxState->TxHdl != CANTP_INVALID_HDL)
      {
        CanTp_EnterCritical();  /* CanTp_MainFunctionTx ~~~~~~~~~~~~~~~~~~~~ */

        /* is it still active? */
        if (pTpTxState->TxHdl != CANTP_INVALID_HDL) /* check will only fail if state changed before critical section have been entered */
        {
          /* #30 Update channel timers (STmin timer, if used, and main timer). */
          if (pTpTxState->STminTimer > 0u)
          {
            pTpTxState->STminTimer--;                                                                                  /* SBSW_CANTP_TASK_WRITE_TXSTATE */

            /* #35 If STmin timer expired (=0) and internal STmin supervision is active, change state to get TxBuffer. */
            if (pTpTxState->STminTimer == 0u)
            {
              /* STmin expired, trigger transmission of CF */
              pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;                                                 /* SBSW_CANTP_TASK_WRITE_TXSTATE */
              /* buffer request will be executed at the end of CanTp_MainFunctionTx */
            }
          }

          pTpTxState->Timer--;                                                                                         /* SBSW_CANTP_TASK_WRITE_TXSTATE */
          if (pTpTxState->Timer == 0u)
          {
            /* #40  If main timer expired (=0), do the timeout handling according to the current state. */
            switch (pTpTxState->ChannelState)
            {
              /* #50 State = wait for FC: N_Bs timeout occurred, reset connection. */
              case CANTP_TXSTATE_WAIT_FC:
                CanTp_TxInit(pTpTxState, CANTP_NOTIFY_TIMEOUT_B, CANTP_E_TX_TIMEOUT_BS);                               /* SBSW_CANTP_TASK_CALL_TXSTATE */
                break;

              /* #60 State = wait for internal or external STmin: STmin expired, proceed like for buffer timeout. */
#if (CANTP_STMIN_BY_APPL == STD_ON)
              case CANTP_TXSTATE_WAIT_STMIN_APPL:
#endif
              case CANTP_TXSTATE_WAIT_STMIN_INTERN:                                                                    /* COV_CANTP_NCS_CONFIG */
                /* Trigger for end of STmin didn't occur within N_Cs! Stop waiting for STmin */
                pTpTxState->STminTimer   = 0;                                                                          /* SBSW_CANTP_TASK_WRITE_TXSTATE */
                pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;                                               /* SBSW_CANTP_TASK_WRITE_TXSTATE */
                /* fall through; then there is one last chance to get a buffer */

              /* #70 State = wait for buffer: */
              case CANTP_TXSTATE_WAIT_BUFFER_SF:                                                                       /* PRQA S 2003 */ /* MD_CanTp_2003 */
              case CANTP_TXSTATE_WAIT_BUFFER_FF:
              case CANTP_TXSTATE_WAIT_BUFFER_CF:
                /* #80 Timeout during buffer request; try one last time to get a Tx buffer. */
                CanTp_TxGetBuffer(pTpTxState);                                                                         /* SBSW_CANTP_TASK_CALL_TXSTATE */
                /* #90 If after the call the buffer state is still busy: N_Cs timeout occurred, reset connection. */
                if (pTpTxState->BufferState == CANTP_BUFREQ_E_BUSY)
                {
                  CanTp_TxInit(pTpTxState, CANTP_NOTIFY_NO_BUFFER, CANTP_E_TX_TIMEOUT_CS);                             /* SBSW_CANTP_TASK_CALL_TXSTATE */
                }
                break;

              /* #100 State = wait for any transmission or TxConfirmation: N_As timeout occurred, reset connection. */
              case CANTP_TXSTATE_TRANSMIT_SF:
              case CANTP_TXSTATE_TRANSMIT_FF:
              case CANTP_TXSTATE_TRANSMIT_CF:
              case CANTP_TXSTATE_WAIT_TXCONF_SF:
              case CANTP_TXSTATE_WAIT_TXCONF_FF:
              case CANTP_TXSTATE_WAIT_TXCONF_CF:
                CanTp_TxInit(pTpTxState, CANTP_NOTIFY_TIMEOUT_A, CANTP_E_TX_TIMEOUT_AS);                               /* SBSW_CANTP_TASK_CALL_TXSTATE */
                break;

              /* #110 Any other state is invalid here, report DET error. */
              default:                                                                                                 /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
                CanTp_DetReportError(CANTP_SID_MAINFUNCTIONTX, CANTP_E_INVALID_TX_STATE)
                break;
            } /* switch(ChannelState) */
          }
          /* #120  If main timer is not yet expired (!=0), check if any cyclic actions need to be done: */
          else
          {
#if (CANTP_TRANSMIT_QUEUE == STD_ON)
            /* #130 If N-PDU transmission is queued: try to transmit it now (call CanTp_TxQueueProcess). */
            /* Check this one first to be sure the channel is still active and pTpTxState->TxHdl is valid. If it would */
            /* be done later, CanTp_TxGetBuffer() and CanTp_TxTransmitFrame() may have reset the channel.              */
            /* However, it doesn't matter if the channel is reset in CanTp_TxQueueProcess(), because before the other  */
            /* calls below the channel state is checked anyway.                                                        */
            if (!CanTp_TxQueueIsEmpty(CanTp_TxCfg_GetTxConfPduId(pTpTxState->TxHdl)))
            {
              CanTp_TxQueueProcess(CanTp_TxCfg_GetTxConfPduId(pTpTxState->TxHdl));                                   /* SBSW_CANTP_TXQUEUEPROCESS_CALL_TX */
            }
#endif
            /* #140 If State = wait for buffer: try to get more Tx buffer. */
            if ((pTpTxState->ChannelState & CANTP_TXSTATE_WAIT_BUFFER_ANY) == CANTP_TXSTATE_WAIT_BUFFER_ANY)
            {
              CanTp_TxGetBuffer(pTpTxState);                                                                           /* SBSW_CANTP_TASK_CALL_TXSTATE */
            }

            /* #150 If State = wait for transmission: N-PDU Tx request pending, retry transmission (call CanTp_TxTransmitFrame). */
            if ((pTpTxState->ChannelState & CANTP_TXSTATE_TRANSMIT_ANY) == CANTP_TXSTATE_TRANSMIT_ANY)
            {
              CanTp_TxTransmitFrame(pTpTxState);                                                                       /* SBSW_CANTP_TASK_CALL_TXSTATE */
            }
          }
        }
        /* else: channel not in use (secured check) */

        CanTp_LeaveCritical();  /* CanTp_MainFunctionTx ~~~~~~~~~~~~~~~~~~~~ */
      }
      /* else: channel not in use (preliminary check) */
    }
    /* end of loop through all connections */
  }
  /* else: CanTp not initialized */
} /* CanTp_MainFunctionTx() */  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */



/***********************************************************************************************************************
 *  CanTp_Transmit()
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8           lErrorId     = CANTP_E_NO_ERROR;                                                                     /* PRQA S 	2981 */ /* MD_CanTp_RedundantAssignment */
  Std_ReturnType  lReturnValue = E_NOT_OK;

  CANTP_DUMMY_STATEMENT(CanTpTxSduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* ----- Development Error Checks ------------------------------------------------------------ */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    /* #10 Always ensure that the CanTp is initialized to avoid start of communication (even with disabled DET). */
    lErrorId = CANTP_E_UNINIT;
  }
#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
  else if (CanTpTxSduId >= CanTp_Cfg_GetNumTxSduIds())                                                                 /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
  else if (CanTpTxInfoPtr == NULL_PTR)                                                                                 /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  {
    lErrorId = CANTP_E_PARAM_POINTER;
  }
# if (CANTP_SUPPORT_LONG_FF != STD_ON)
  /* with standard First Frames, the max data length is limited to 4095 byte */
  else if (CanTpTxInfoPtr->SduLength > CANTP_FF_DL_12BIT)
  {
    lErrorId = CANTP_E_INVALID_TX_LENGTH;
  }
# endif
# if (CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)
  /* in case of post build, some SDUs might not be supported */
  else if (!CanTp_TxSduSnvIsAvailable(CanTpTxSduId))                                                                   /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
# endif
#endif
  else
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* --- Get SDU Handle --- */
    CONST(PduIdType, AUTOMATIC) lTxSduHdl = CanTp_TxGetSduHdlBySduId(CanTpTxSduId);

    /* --- SDU Length Check --- */
    /* #40 If requested length is zero, do nothing, ignore the transmit request and return E_NOT_OK. */
    if (CanTpTxInfoPtr->SduLength > 0u)
    {
      CanTp_EnterCritical();  /* CanTp_Transmit ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

      /* --- Half Duplex Check --- */
#if (CANTP_TX_HAS_HALF_DUPLEX == STD_ON)
      if (CanTp_TxCheckChannelMode(lTxSduHdl) == E_OK)
#endif
      {
        /* --- Start Transmission --- */
        /* #60 If half duplex check is passed, setup a new Tx connection for the requested N-SDU. */
        lReturnValue = CanTp_TxStartConnection(CanTpTxSduId, lTxSduHdl, CanTpTxInfoPtr->SduLength, CanTpTxInfoPtr);    /* SBSW_CANTP_TXSTARTCONNECTION_CALL_PDUINFO */
      }
      /* else: half duplex and Rx side is busy */

      CanTp_LeaveCritical();  /* CanTp_Transmit ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    }
    /* else: SduLength is zero, do nothing */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)                                                                                    /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */
  {
    CanTp_DetReportError(CANTP_SID_TRANSMIT, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return lReturnValue;
} /* CanTp_Transmit() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */



/***********************************************************************************************************************
 *  CanTp_RxIndication()
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
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 lErrorId = CANTP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    /* #10 Always ensure that the CanTp is initialized to avoid start of communication (even with disabled DET). */
    lErrorId = CANTP_E_UNINIT;
  }
#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
  else if (RxPduId >= CanTp_Cfg_GetNumRxPdus())
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
  else if (PduInfoPtr == NULL_PTR)
  {
    lErrorId = CANTP_E_PARAM_POINTER;
  }
  else if (PduInfoPtr->SduDataPtr == NULL_PTR)
  {
    lErrorId = CANTP_E_PARAM_POINTER;
  }
#endif
  else
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    PduIdType                  lSduHdl;
    uint8                      lReceivedFrameType;

    /* --- Get N-SDU and Direction --- */
#if (CANTP_SUPPORT_MULTIPLE_ADDRESSING == STD_ON)
    /* avoid compiler warnings for uninitialized variables */
    lSduHdl            = CANTP_INVALID_HDL;
    lReceivedFrameType = CANTP_PCI_TYPE_INVALID;                                                                       /* PRQA S 2982 */ /* MD_CanTp_RedundantAssignment */

    switch(CanTp_Cfg_GetAddressingTypeByRxPdu(RxPduId))
    {
      /*#40  Standard and Normal Fixed Addressing: get frame type from 1st byte of the received frame. */
      case CANTP_ADDRESS_FORMAT_STANDARD:
      case CANTP_ADDRESS_FORMAT_NORMALFIXED:                                                                           /* COV_CANTP_NORMALFIXED_ADDRESSING */
        lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[0] & CANTP_PCI_TYPE_MASK);
        /* #50 Get SduHdl from the configuration tables, depending on the RxPduId and the frame type. */
        lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
        break;

      /* #70  Extended or Mixed11 or Mixed29 Addressing: get address from 1st byte and frame type from 2st byte of the received frame. */
      case CANTP_ADDRESS_FORMAT_EXTENDED:
      case CANTP_ADDRESS_FORMAT_MIXED11:                                                                               /* COV_CANTP_MIXED11_ADDRESSING */
      case CANTP_ADDRESS_FORMAT_MIXED29:                                                                               /* COV_CANTP_MIXED29_ADDRESSING */
        lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[1] & CANTP_PCI_TYPE_MASK);

        /* #80  If connection is generic:
         *        Get SduHdl from the configuration tables, depending on the RxPduId and the frame type (1:1 PDU-to-SDU mapping).
         *      Othewise:
         *        Get SduHdl from the configuration tables, depending on the RxPduId, the frame type and the address.
         */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
        if (CanTp_Cfg_IsGenericConnectionByRxPdu(RxPduId))
        {
          lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
        }
        else
#endif
        {
          lSduHdl = CanTp_Cfg_GetSduHdlByRxPduAddress(RxPduId, lReceivedFrameType, PduInfoPtr->SduDataPtr[0]);
        }
        break;

      /* #100 Any other addressing format: ignore received frame. */
      default:                                                                                                         /* COV_CANTP_DEFAULT_BRANCH */
        /* No DET is reported her because in theory, this may happen when the PduMap entry has been removed at post-build time. */
        /* With the current generator, the addressing format is generated as 0 (= Standard Addressing), so even with post-build */
        /* this branch will never be reached.                                                                                   */
        break;
    } /* switch(AddressFormat) */
#else /* CANTP_MULTIPLE_ADDRESSING */
# if ((CANTP_SUPPORT_STANDARD_ADDRESSING == STD_ON) || (CANTP_SUPPORT_NORMALFIXED_ADDRESSING == STD_ON))
    lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[0] & CANTP_PCI_TYPE_MASK);
    lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
# else
    lReceivedFrameType = (uint8)(PduInfoPtr->SduDataPtr[1] & CANTP_PCI_TYPE_MASK);
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
    if (CanTp_Cfg_IsGenericConnectionByRxPdu(RxPduId))
    {
      lSduHdl = CanTp_Cfg_GetSduHdlByRxPduOnly(RxPduId, lReceivedFrameType);
    }
    else
#endif
    {
      lSduHdl = CanTp_Cfg_GetSduHdlByRxPduAddress(RxPduId, lReceivedFrameType, PduInfoPtr->SduDataPtr[0]);
    }
# endif
#endif

    /* #105 If required, notify all the received Mixed11 SFs and FFs (even those without a valid N_AE) to the Dcm. */
#if ((CANTP_DCM_REQUEST_DETECT == STD_ON) && (CANTP_MIXED11_ADDRESSING == STD_ON))
# if (CANTP_SUPPORT_MULTIPLE_ADDRESSING == STD_ON)
    if ((CanTp_Cfg_GetAddressingTypeByRxPdu(RxPduId) == CANTP_ADDRESS_FORMAT_MIXED11) &&
        ((lReceivedFrameType == CANTP_PCI_TYPE_SF) || (lReceivedFrameType == CANTP_PCI_TYPE_FF)))
# else
    if ((lReceivedFrameType == CANTP_PCI_TYPE_SF) || (lReceivedFrameType == CANTP_PCI_TYPE_FF))
# endif
    {
      CanTp_DcmForwardNAE(RxPduId, PduInfoPtr->SduDataPtr[0]);
    }
#endif

    /* #110  If SduHdl could be retrieved, prepare the payload info and metadata info for CanTp_CanIfRxIndication(). */
    if (lSduHdl != CANTP_INVALID_HDL)                                                                                  /* COV_CANTP_SINGLE_CHANNEL_PDU */
    {
      PduInfoType lPayloadInfo;
      PduInfoType lMetadataInfo;
      
      lPayloadInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
      lMetadataInfo.SduLength = CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId);

#if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
      if (CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId) != 0u)
      {
        lPayloadInfo.SduLength = PduInfoPtr->SduLength - CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId);
        lMetadataInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[PduInfoPtr->SduLength - CanTp_Cfg_GetPduMetadataLengthByRxPdu(RxPduId)];
      }
      else
#endif
      {
        lPayloadInfo.SduLength = PduInfoPtr->SduLength;
        lMetadataInfo.SduDataPtr = PduInfoPtr->SduDataPtr; /* The pointer shall not be used, but remain within-bounds by pointing to the start of the payload. */
      }

      CanTp_CanIfRxIndication(lSduHdl, lReceivedFrameType, &lPayloadInfo, &lMetadataInfo);                             /* SBSW_CANTP_CANIFRXINDICATION_CALL_PDUINFO */
    }
#if ((CANTP_CONFIGURATION_VARIANT == CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) || (CANTP_POSTBUILD_VARIANT_SUPPORT == STD_ON))
    /* #115 Otherwise, if the Rx N-PDU is not related to any N-SDU, prepare to report a DET error. */
    else if ((!CanTp_CanIfRxPduHasTxSduRef(RxPduId)) && (!CanTp_CanIfRxPduHasRxSduRef(RxPduId)))                       /* COV_CANTP_PDU_REF */
    {
      lErrorId = CANTP_E_INVALID_RX_ID;      
    }
    else
    {
      /* Just ignore the Rx N-PDU without reporting a DET error. */
    }
#endif
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_RXINDICATION, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* CanTp_RxIndication() */  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */



/***********************************************************************************************************************
 *  CanTp_TxConfirmation()
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
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 lErrorId = CANTP_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else if (TxPduId >= CanTp_Cfg_GetNumTxConfPdus())
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
  else
#endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    PduIdType            lSduHdl;
    CanTp_DirectionType  lSduDir;

    CanTp_EnterCritical();  /* CanTp_TxConfirmation ~~~~~~~~~~~~~~~~~~~~~~ */

    /* --- Read and release semaphore --- */
    lSduHdl = CanTp_Data_TxSemaphore(TxPduId).Handle;
    lSduDir = CanTp_Data_TxSemaphore(TxPduId).Direction;

    /* release semaphore */
    CanTp_Data_TxSemaphore(TxPduId).Handle    = CANTP_INVALID_HDL;                                                     /* SBSW_CANTP_TXCONFIRMATION_WRITE_TXSEMAPHORE */
    CanTp_Data_TxSemaphore(TxPduId).Direction = CANTP_DIR_NONE;                                                        /* SBSW_CANTP_TXCONFIRMATION_WRITE_TXSEMAPHORE */

#if (CANTP_TRANSMIT_QUEUE == STD_ON)
    /* ... and process next queue entry, if there is one */
    if (!CanTp_TxQueueIsEmpty(TxPduId))
    {
      CanTp_TxQueueProcess(TxPduId);
    }
#endif

    CanTp_LeaveCritical();  /* CanTp_TxConfirmation ~~~~~~~~~~~~~~~~~~~~~~ */

    /* --- process TxConfirmation of Rx or Tx connection --- */
    /* #50 If semaphore was locked by a valid and active Tx N-SDU, for which TxPduId is configured as TxPdu. */
    if (lSduHdl != CANTP_INVALID_HDL)
    {
      if (lSduDir == CANTP_DIR_TX)
      {
#if (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
        /* TX direction */
        if (CanTp_TxCfg_GetTxConfPduId(lSduHdl) == TxPduId)                                                            /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */ /* COV_CANTP_INVALID_TXCONFPDU */
        {
          CanTp_TxStatePtrType pTpTxState;
          CanTp_EnterCritical();  /* CanTp_TxConfirmation ~~~~~~~~~~~~~~~~ */

          pTpTxState = CanTp_TxGetActiveChannelPtr(lSduHdl);
          if (pTpTxState != NULL_PTR)
          {
            /* #60 Call debugging call-out and process confirmation of a transmitted SF, FF or CF frame. */
            CanTp_ApplFrameTxConfirmation(CanTp_TxCfg_GetLoLayerTxPduId(lSduHdl))                                      /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */
            CanTp_CanIfTxConfirmation(pTpTxState);                                                                     /* SBSW_CANTP_CANIFTXCONFIRMATION_CALL_TXTXSTATE */
          }
          /* else: channel is not / no longer active; ignore confirmation */

          CanTp_LeaveCritical();  /* CanTp_TxConfirmation ~~~~~~~~~~~~~~~~ */
        }
        /* else: PduId does not match; ignore confirmation */
#endif /* (CANTP_TX_OPTIMIZATION != CANTP_OPT_ZERO_SDU) */
      }
      /* #70 If semaphore was locked by a valid and active Rx N-SDU, for which TxPduId is configured as TxFcPdu. */
      else
      {
#if (CANTP_RX_OPTIMIZATION != CANTP_OPT_ZERO_SDU)                                                                      /* COV_CANTP_ROBUSTNESS_CASE TX */
        /* RX direction */
        if (CanTp_RxCfg_GetTxFcConfPduId(lSduHdl) == TxPduId)                                                          /* PRQA S 2991, 2995 */ /* MD_CanTp_ExpressionAlwaysTrue, MD_CanTp_OperationAlwaysTrue */ /* COV_CANTP_INVALID_TXCONFPDU */
        {
          CanTp_RxStatePtrType pTpRxState;

          CanTp_EnterCritical();  /* CanTp_TxConfirmation ~~~~~~~~~~~~~~~~ */

          pTpRxState = CanTp_RxGetActiveChannelPtr(lSduHdl);
          if (pTpRxState != NULL_PTR)
          {
            /* #80 Call debugging call-out and process confirmation of a transmitted FC frame. */
            CanTp_ApplFrameTxConfirmation(CanTp_RxCfg_GetLoLayerTxFcPduId(lSduHdl))                                      /* SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO */
            CanTp_CanIfTxConfirmationFC(pTpRxState);                                                                   /* SBSW_CANTP_CANIFTXCONFIRMATION_CALL_RXTXSTATE */
          }
          /* else: channel is not / no longer active; ignore confirmation */

          CanTp_LeaveCritical();  /* CanTp_TxConfirmation ~~~~~~~~~~~~~~~~ */
        }
        /* else: PduId does not match; ignore confirmation */
#endif
      }
    }
    /* else: semaphore contains invalid handle; ignore confirmation */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_TXCONFIRMATION, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* CanTp_TxConfirmation() */  /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */



#if (CANTP_ENABLE_CHANGE_PARAM == STD_ON)
/***********************************************************************************************************************
 *  CanTp_ChangeParameter()
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType  lReturnValue = E_NOT_OK;
  uint8           lErrorId     = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(id);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else if (id >= CanTp_Cfg_GetNumRxSduIds())
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
  else if ((parameter != TP_STMIN) && (parameter != TP_BS))
  {
    lErrorId = CANTP_E_PARAM_ID;
  }
# if (CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)
  /* in case of post build, some SDUs might not be supported */
  else if (!CanTp_RxSduSnvIsAvailable(id))                                                                             /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
# endif
  else
#endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* --- Get SDU Handle --- */
    CONST(PduIdType, AUTOMATIC) lRxSduHdl = CanTp_RxGetSduHdlBySduId(id);

    CanTp_EnterCritical();  /* CanTp_ChangeParameter ~~~~~~~~~~~~~~~~~~~~~ */

    /* #40 Only accept the request if the connection is not active. Otherwise reject it and return E_NOT_OK. */
    if (CanTp_RxChannelIsIdle(lRxSduHdl) == TRUE)
    {
      /* --- Set the requested parameter --- */
      /* #60 STmin: if the value is not reserved, store it and return E_OK. Otherwise, return E_NOT_OK. */
      if (parameter == TP_STMIN)
      {
        /* STmin normalization */
        if ( ((value > CANTP_STMIN_MILLISEC_MAX) && (value < CANTP_STMIN_MICROSEC_MIN)) ||
              (value > CANTP_STMIN_MICROSEC_MAX) )
        {
          /* Reserved value */
          lErrorId = CANTP_E_PARAM_ID;
        }
        else
        {
          CanTp_Data_DynFcParam(lRxSduHdl).STmin = (uint8)value;                                                       /* SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_INDEX */ /* SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_SIZE */
          lReturnValue = E_OK;
        }
      }

      /* #70 BS: the value is always valid, store it and return E_OK. */
      else /* (parameter == TP_BS) */
      {
        CanTp_Data_DynFcParam(lRxSduHdl).BS = (uint8)value;                                                            /* SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_INDEX */ /* SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_SIZE */
        lReturnValue = E_OK;
      }
    }
    /* else: busy reception */

    CanTp_LeaveCritical();  /* CanTp_ChangeParameter ~~~~~~~~~~~~~~~~~~~~~ */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_CHANGEPARAMETER, lErrorId)
  }
#else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return lReturnValue;
} /* CanTp_ChangeParameter() */  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* CANTP_ENABLE_CHANGE_PARAM == STD_ON */



#if (CANTP_ENABLE_READ_PARAM == STD_ON)
/***********************************************************************************************************************
 *  CanTp_ReadParameter()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16* value)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType  lReturnValue;
  uint8           lErrorId = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(id);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_CANTP_DET_CHECK TX */
  /* this function will only fail if development error detection is enabled */
  lReturnValue = E_NOT_OK;

  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else if (id >= CanTp_Cfg_GetNumRxSduIds())
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
  else if ((parameter != TP_STMIN) && (parameter != TP_BS))
  {
    lErrorId = CANTP_E_PARAM_ID;
  }
  else if (value == NULL_PTR)
  {
    lErrorId = CANTP_E_PARAM_POINTER;
  }
# if (CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)
  /* in case of post build, some SDUs might not be supported */
  else if (!CanTp_RxSduSnvIsAvailable(id))                                                                             /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
# endif
  else
#endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    /* --- Get SDU Handle --- */
    CONST(PduIdType, AUTOMATIC) lRxSduHdl = CanTp_RxGetSduHdlBySduId(id);

    lReturnValue = E_OK;

    /* --- Read requested parameter --- */
    /* #40 Set the out parameter to the current value of the requested TP parameter (STmin or BS) and return E_OK. */
    if (parameter == TP_STMIN)
    {
      *value = CanTp_RxGetCurrentSTmin(lRxSduHdl);                                                                     /* SBSW_CANTP_READPARAMETER_WRITE_VALUE */
    }
    else /* (parameter == TP_BS) */
    {
      *value = CanTp_RxGetCurrentBS(lRxSduHdl);                                                                        /* SBSW_CANTP_READPARAMETER_WRITE_VALUE */
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_READPARAMETER, lErrorId)
  }
# else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return lReturnValue;
} /* CanTp_ReadParameter() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANTP_ENABLE_READ_PARAM == STD_ON */



#if (CANTP_TC == STD_ON)
/***********************************************************************************************************************
 *  CanTp_CancelTransmit()
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmit(PduIdType CanTpTxSduId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType   lReturnValue = E_NOT_OK;
  uint8            lErrorId     = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(CanTpTxSduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* ----- Development Error Checks ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_CANTP_DET_CHECK TX */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else if (CanTpTxSduId >= CanTp_Cfg_GetNumTxSduIds())
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#  if (CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)
  /* in case of post build, some SDUs might not be supported */
  else if (!CanTp_TxSduSnvIsAvailable(CanTpTxSduId))                                                                   /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#  endif
  else
# endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    CanTp_TxStatePtrType pTpTxState;

    /* --- Get SDU Handle --- */
    CONST(PduIdType, AUTOMATIC) lTxSduHdl = CanTp_TxGetSduHdlBySduId(CanTpTxSduId);                                    /* PRQA S 2983 */ /* MD_CanTp_RedundantAssignment */

    /* --- Check Cancellation Conditions --- */
    /* #40 If the SDU specific cancellation is enabled, if a transmission is active, if not a single frame or the last frame is transmitted: */
    if (CanTp_TxCfg_HasTxCancel(lTxSduHdl))                                                                            /* COV_CANTP_TC_ACTIVATION */
    {
      CanTp_EnterCritical();  /* CanTp_CancelTransmit ~~~~~~~~~~~~~~~~~~~~ */                                          /* PRQA S 2880 */ /* MD_MSR_Unreachable */

      pTpTxState = CanTp_TxGetActiveChannelPtr(lTxSduHdl);
      if (pTpTxState != NULL_PTR)                                                                                      /* COV_CANTP_TC_ACTIVATION */
      {

        /* is transmission segmented? */
        if (pTpTxState->DataLength > CanTp_TxCfg_GetMaxSFDataLength(lTxSduHdl))                                        /* COV_CANTP_TC_ACTIVATION */
        {

          /* can it still be cancelled (last frame not yet transmitted)? */
          if (pTpTxState->DataIndex < pTpTxState->DataLength)                                                          /* COV_CANTP_TC_ACTIVATION */
          {

            /* #50 Reset connection and return E_OK. */
            CanTp_TxInit(pTpTxState, CANTP_NOTIFY_CANCEL_OK, CANTP_E_NO_ERROR);                                        /* SBSW_CANTP_TXINIT_CALL_TXSTATE */
            lReturnValue = E_OK;
          }
          /* else: last CF already given to CanIf */
        }
        /* else: unsegmented transmission */
      }
      else
      {
        /* no transmission in progress */
        lErrorId = CANTP_E_OPER_NOT_SUPPORTED;
      }

      CanTp_LeaveCritical();  /* CanTp_CancelTransmit ~~~~~~~~~~~~~~~~~~~~ */
    }
    /* else: connection specific cancellation disabled; this may happen in post-build            */
    /*       configurations, or the API is required by another module but not used.              */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_CANCELTRANSMIT, lErrorId)
  }
# else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return lReturnValue;
} /* CanTp_CancelTransmit() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANTP_TC == STD_ON */



#if (CANTP_RC == STD_ON)
/***********************************************************************************************************************
 *  CanTp_CancelReceive()
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
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceive(PduIdType CanTpRxSduId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType lReturnValue = E_NOT_OK;
  uint8          lErrorId     = CANTP_E_NO_ERROR;

  CANTP_DUMMY_STATEMENT(CanTpRxSduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* ----- Development Error Checks ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_CANTP_DET_CHECK TX */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else if (CanTpRxSduId >= CanTp_Cfg_GetNumRxSduIds())
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
#  if (CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)
  /* in case of post build, some SDUs might not be supported */
  else if (!CanTp_RxSduSnvIsAvailable(CanTpRxSduId))                                                                   /* COV_CANTP_POSTBUILD_DELETED XF */
  {
    lErrorId = CANTP_E_INVALID_RX_ID;
  }
#  endif
  else
# endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    CanTp_RxStatePtrType pTpRxState;

    /* --- Get SDU Handle --- */
    CONST(PduIdType, AUTOMATIC) lRxSduHdl = CanTp_RxGetSduHdlBySduId(CanTpRxSduId);

    CanTp_EnterCritical();  /* CanTp_CancelReceive ~~~~~~~~~~~~~~~~~~~~~~~ */

    /* --- Check Cancellation Conditions --- */
    /* #40 If a reception is active, and if not a single frame or the last frame is received: */
    pTpRxState = CanTp_RxGetActiveChannelPtr(lRxSduHdl);
    if (pTpRxState != NULL_PTR)
    {

      /* is reception segmented? */
      if (pTpRxState->FrameType != CANTP_FRAME_SF)
      {

        /* can it still be cancelled (last frame not yet received)? */
        if ((pTpRxState->DataIndex + pTpRxState->PayloadLength) < pTpRxState->DataLength)
        {

          /* #50 Reset connection and return E_OK. */
          CanTp_RxInit(pTpRxState, CANTP_NOTIFY_CANCEL_OK, CANTP_E_NO_ERROR, CANTP_RESET_ALL);                         /* SBSW_CANTP_RXINIT_CALL_RXSTATE */
          lReturnValue = E_OK;
        }
        /* else: last CF already received but not yet copied (CANTP262) */
      }
      /* else: unsegmented reception */
    }
    else
    {
      /* no reception in progress */
      lErrorId = CANTP_E_OPER_NOT_SUPPORTED;
    }

    CanTp_LeaveCritical();  /* CanTp_CancelReceive ~~~~~~~~~~~~~~~~~~~~~~~ */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_CANCELRECEIVE, lErrorId)
  }
# else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  return lReturnValue;
} /* CanTp_CancelReceive() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANTP_RC == STD_ON */



#if (CANTP_STMIN_BY_APPL == STD_ON)
/***********************************************************************************************************************
 *  CanTp_StopSeparationTime()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_StopSeparationTime(PduIdType CanTpTxSduId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8          lErrorId;

  CANTP_DUMMY_STATEMENT(CanTpTxSduId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */

  /* ----- Development Error Checks ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_DETECT == STD_ON)                                                                                /* COV_CANTP_DET_CHECK TX */
  if (CanTp_Data_InitState() != CANTP_STATUS_INITIALIZED)
  {
    lErrorId = CANTP_E_UNINIT;
  }
  else if (CanTpTxSduId >= CanTp_Cfg_GetNumTxSduIds())
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#  if (CANTP_CONFIGURATION_VARIANT != CANTP_CONFIGURATION_VARIANT_PRECOMPILE)
  /* in case of post build, some SDUs might not be supported */
  else if (!CanTp_TxSduSnvIsAvailable(CanTpTxSduId))
  {
    lErrorId = CANTP_E_INVALID_TX_ID;
  }
#  endif
  else
# endif
  {

    /* ----- Implementation -------------------------------------------------------------------- */
    CanTp_TxStatePtrType pTpTxState;

    /* --- Get SDU Handle --- */
    CONST(PduIdType, AUTOMATIC) lTxSduHdl = CanTp_TxGetSduHdlBySduId(CanTpTxSduId);

    /* --- Check that connection is in correct state --- */
    lErrorId = CANTP_E_INVALID_TX_STATE;

    CanTp_EnterCritical();  /* CanTp_StopSeparationTime ~~~~~~~~~~~~~~~~~~~~~~~ */

    pTpTxState = CanTp_TxGetActiveChannelPtr(lTxSduHdl);
    if (pTpTxState != NULL_PTR)
    {
      if (pTpTxState->ChannelState == CANTP_TXSTATE_WAIT_STMIN_APPL)
      {

        /* --- Prepare for CF transmission --- */
        lErrorId = CANTP_E_NO_ERROR;
        /* timer doesn't have to be reloaded, buffer handling must be completed in the remaining time of N_Cs */
        pTpTxState->ChannelState = CANTP_TXSTATE_WAIT_BUFFER_CF;                                                       /* SBSW_CANTP_STOPSEPARATIONTIME_WRITE_TXSTATE */
        CanTp_TxGetBuffer(pTpTxState);                                                                                 /* SBSW_CANTP_STOPSEPARATIONTIME_WRITE_TXSTATE */
      }
      /* else: connection is active, but not waiting for a STmin trigger! */
    }
    /* else: connection is not active at all */

    CanTp_LeaveCritical();  /* CanTp_StopSeparationTime ~~~~~~~~~~~~~~~~~~~~~~~ */
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
  if (lErrorId != CANTP_E_NO_ERROR)
  {
    CanTp_DetReportError(CANTP_SID_STOPSEPARATIONTIME, lErrorId)
  }
# else
  CANTP_DUMMY_STATEMENT(lErrorId);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

} /* CanTp_StopSeparationTime() */  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANTP_STMIN_BY_APPL == STD_ON */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ------------------------------------------------------------------------------------------------------------------ */
/* Justification for module-specific MISRA deviations:
  MD_CanTp_0841:
    Description: Rule 19.6: #undef shall not be used
    Reason:      usability and compatibility; #undef is used here to override a generate switch by user config
    Risk:        none
    Prevention:  N/A

  MD_CanTp_2003
    Description: Rule 15.2: An unconditional break statement shall terminate every non-empty switch clause.
    Reason:      The break statement of the previous case is intentionally omitted to avoid doubled code (fall-though).
    Risk:        none
    Prevention:  N/A

  MD_CanTp_ReturnPaths:
    Reason:      More than one return statement for better readability (e.g. less if-nesting).
    Risk:        None
    Prevention:  N/A

  MD_CanTp_3333:
    Description: Rule 14.6: A break statement is being used to exit from a switch case block but is not the final statement in the block.
    Reason:      break statement that is not at the end of a case block is used for a better readability and less resource consumption.
    Risk:        none
    Prevention:  N/A

  MD_CanTp_ExpressionAlwaysTrue:
    Reason:      Optimizations in some configurations lead to a constant expression.
    Risk:        None, even in configurations where the expresion is always true.
    Prevention:  verify by inspection that there is a configuration where the state is not always true

  MD_CanTp_OperationAlwaysTrue:
    Reason:      Optimizations in some configurations lead to a constant operation.
    Risk:        None, even in configurations where the operation is always true.
    Prevention:  N/A

  MD_CanTp_3447:
    Description: Rule 8.8: identifier has external linkage but this declaration is not in a header file.
    Reason:      local function declared without 'static', as in some configs it is externally visible and code coverage analysis may be erroneous if two different declarations are used
    Risk:        none
    Prevention:  N/A

  MD_CanTp_3673:
    Description: Rule 16.7: The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'.
    Reason:      pointer parameter is not defined here as const since in some configuration write access is needed
    Risk:        none, because this is an internal function with limited use case
    Prevention:  N/A.

  MD_CanTp_MissingIdentifier:
    Reason:     Different identifiers are used by the lower layers for the first parameter of the transmit functions. 
    Risk:       None
    Prevention: N/A

  MD_CanTp_RedundantAssignment:
    Reason:     Avoid decreasing readability and/or avoid warnings from some compilers.
    Risk:       None, even in configurations where the assignment is actually redundant.
    Prevention: N/A

  MD_CanTp_RedundantOperation:
    Reason:     Avoid complicated preprocessor logic that would decrease readability.
    Risk:       None, even in configurations where a redundant operation actually takes place.
    Prevention: N/A

  MD_CanTp_CheckCfgExpressionAlwaysFalse:
    Reason:     These checks must always be done for SafeBSW, but are true only with invalid configurations. 
    Risk:       None, since the checks are tested in configurations using a config-pointer.
    Prevention: N/A

  MD_CanTp_CheckCfgOperationAlwaysFalse:
    Reason:     These checks must always be done for SafeBSW, but are true only with invalid configurations. 
    Risk:       None, since the checks are tested in configurations using a config-pointer.
    Prevention: N/A

*/


/* ------------------------------------------------------------------------------------------------------------------ */
/* Coverage Justifications                                                                                            */
/* ------------------------------------------------------------------------------------------------------------------ */

/* COV_JUSTIFICATION_BEGIN
 *
--- Preprocessor Coverage Justifications ------------------------------------------------------------------------------
\ID COV_CANTP_EXCLUDED_FEATURES
  \REASON The preprocessor switch is related to a feature which is excluded for SafeBSW; it must be properly set by GenTool or UserConfig (see also [CM_CANTP_PRECOMPILEOPTIONS]).

\ID COV_CANTP_UNIT_TEST
  \REASON Static functions are made externally visible for test purposes (unit tests).

\ID COV_CANTP_ROBUSTNESS_CASE
  \REASON The condition is only covered in configuration where one direction is missing. This use case is practically not relevant and excluded for SafeBSW.

\ID COV_CANTP_DET_CHECK
  \REASON DET has to be enabled for SafeBSW. A MSSV Plugin enforces this configuration.

\ID COV_CANTP_MODIFIED_STMIN_HANDLING
  \REASON This point is reached only if the surrounding macro CANTP_MODIFIED_RES_STMIN_HANDLING is set to STD_ON. In SafeBSW this is possible only if the macro CANTP_REJECT_FC_WITH_RES_STMIN is set to STD_ON.

--- Condition Coverage Justifications ---------------------------------------------------------------------------------
\ID COV_CANTP_RESERVED_STMIN
  \ACCEPT TX tx tx
  \REASON Usage of reserved STmin can be disabled by precompile switch, so in this case no all conditions will be fullfilled.

\ID COV_CANTP_CONSTANT_PARAMETER
  \ACCEPT TX
  \ACCEPT XF
  \REASON Parameters of internal functions which are passed as parameters can be constant in some configurations.

\ID COV_CANTP_POSTBUILD_DELETED
  \REASON This runtime check requires that connections have been deleted at post-build time, which is not part of all post-build configurations

\ID COV_CANTP_ONLY_PHYSICAL
  \REASON This condition is always true in configurations containing a single physical Tx SDU.

\ID COV_CANTP_TC_ACTIVATION
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XX
  \REASON When SDU specific Tx cancellation is enabled/disabled and only one Tx connection exists (which is a standard use case), parts of CanTp_CancelTransmit will never/always be executed.

\ID COV_CANTP_INVALID_FRAME_TYPE
  \ACCEPT X
  \REASON If dynamic channel assignment is used, invalid frames are already detect before the frame type switch-case, because the connection is not mapped to a channel.

\ID COV_CANTP_MIXED11_ADDRESSING
  \ACCEPT X
  \REASON Configurations with multiple addressing, but without mixed11, will not reach this code. However, this case is tested in other configuration.

\ID COV_CANTP_MIXED29_ADDRESSING
  \ACCEPT X
  \REASON Configurations with multiple addressing, but without mixed29, will not reach this code. However, this case is tested in other configuration.

\ID COV_CANTP_NORMALFIXED_ADDRESSING
  \ACCEPT X
  \REASON Configurations with multiple addressing, but without normal fixed, will not reach this code. However, this case is tested in other configuration.

\ID COV_CANTP_NCS_CONFIG
  \ACCEPT XX
  \REASON To reach this switch case, a too small N_Cs value has to be configured. Since this is not the regular case, it is only done in some but not in all configurations.

\ID COV_CANTP_DEFAULT_BRANCH
  \ACCEPT X
  \REASON Rule 15.3 requires a default case at the end of each switch statement. 

\ID COV_CANTP_SINGLE_CHANNEL_PDU
  \ACCEPT TX
  \REASON The passed PDU will always match a configured PDU if DET checks are active (which is mandatory for SafeBSW), and if only one Rx or Tx PDU is configured (which is a common diagnostic use case).

\ID COV_CANTP_PDU_REF
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \ACCEPT XF tf xf
  \ACCEPT XF xf xx
  \ACCEPT XF tx xf
  \REASON The reference from RxPdu to at least one RxSdu or TxSdu usually exists, so the related check will never fail in some configurations. However, specific configurations where this is tested exist.

\ID COV_CANTP_INVALID_TXCONFPDU
  \ACCEPT TX
  \REASON In some configurations, the received TxConfPdu will always match the configured TxConfPdu here, because validity is already ensured by previous checks. This happens especially when only on Sdus per direction is configured.

\ID COV_CANTP_SILENT_RUNTIME_CHECK
  \ACCEPT TX
  \REASON The check is used to verify the validity of the generated configuration data. This check can only fail with an erroneous generator.

\ID COV_CANTP_LOLAYERFCT_CHECK
  \REASON The check could have the same result in configurations where not all the supported lower layers are used. The result could change if during the post-build phase a previously unused lower layer becomes active. 

COV_JUSTIFICATION_END */



/* ------------------------------------------------------------------------------------------------------------------ */
/* Silent BSW Justification                                                                                           */
/* ------------------------------------------------------------------------------------------------------------------ */
/* Naming Convention:
 * ID_SBSW_CANTP_<function>_CALL_<parameter>: justification for a call to <function> with a specific <parameter>.
 * ID_SBSW_CANTP_<function>_WRITE_<object>:   justification for write access to any <object> within <function>
 *
 * <function> may also refer to "internal", which can be any an static CanTp function, or to a feature / functionality.
 */
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CANTP_INTERNAL_WRITE_RXSTATE
  \DESCRIPTION    The pTpRxState pointer is used in an internal function for write access. It is passed to this function
                  as a parameter and expected to valid. Pointer validity is analyzed at the function call.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_INTERNAL_CALL_RXSTATE
  \DESCRIPTION    The pTpRxState pointer is used in an internal function as parameter to another function. It is passed to
                  this function as a parameter and expected to valid. Pointer validity is analyzed at the function call.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_INTERNAL_WRITE_TXSTATE
  \DESCRIPTION    The pTpTxState pointer is in an internal function for write access and/or as parameter to another
                  function. It passed to this function as a parameter and expected to valid.
                  Pointer validity is analyzed at the function call.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_INTERNAL_CALL_TXSTATE
  \DESCRIPTION    The pTpTxState pointer is used in an internal function as parameter to another function. It is passed to
                  this function as a parameter and expected to valid. Pointer validity is analyzed at the function call.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_INTERNAL_WRITE_CALCBS
  \DESCRIPTION    Write access to the CanTp_CalcBS array, indexed by the RxHdl. RxHdl is part of the struct referenced
                  by the pTpRxState pointer, which is a function parameter here and expected to refer to a valid and
                  initialized channel state. This implies that RxHdl is < CanTp_Cfg_GetNumRxHdls, which is mapped to
                  CanTp_GetSizeOfRxSduCfg in CanTp_Priv.h.
                  The CanTp_CalcBS array must therefore have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_TASK_WRITE_RXSTATE
  \DESCRIPTION    In CanTp_MainFunctionRx, the pTpRxState pointer is used for write access. It is initialized to the RxState
                  array, indexed by lRxChannelHdl, which iterates between 0 and (CanTp_Cfg_GetNumRxChannels-1).
                  CanTp_Cfg_GetNumRxChannels is mapped to CanTp_GetSizeOfRxState in CanTp_Priv.h.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TASK_CALL_RXSTATE
  \DESCRIPTION    In CanTp_MainFunctionRx, the pTpRxState pointer is used as function parameter to other internal functions.
                  The pointer is initialized before (see [SBSW_CANTP_TASK_WRITE_RXSTATE]), and it is ensured that the
                  state is initialized (RxHdl != invalid).
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TASK_WRITE_TXSTATE
  \DESCRIPTION    In CanTp_MainFunctionTx, the pTpTxState pointer is used for write access. It is initialized to the TxState
                  array, indexed by lTxChannelHdl, which iterates between 0 and (CanTp_Cfg_GetNumTxChannels-1).
                  CanTp_Cfg_GetNumTxChannels is mapped to CanTp_GetSizeOfTxState in CanTp_Priv.h.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TASK_CALL_TXSTATE
  \DESCRIPTION    In CanTp_MainFunctionTx, the pTpTxState pointer is used as function parameter to other internal functions.
                  The pointer is initialized before (see [SBSW_CANTP_TASK_WRITE_TXSTATE]), and it is ensured that the
                  state is initialized (TxHdl != invalid).
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_MEMCPY_WRITE_DEST
  \DESCRIPTION    The pointer pDest and the upper limit for the used index (Count) are parameters of the function and expected
                  to be valid and consistent.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_MEMCPY_CALL_PAYLOAD
  \DESCRIPTION    Call to CanTp_Util_MemCpy in order to copy the payload of a received frame to the RxState struct.
                  The parameters Dest and Count must be valid and consistent.
                  - pDest parameter is valid since it references the Payload array of the RxState struct. The array
                    size is CANTP_MAX_PAYLOAD_LENGTH, which is generated. For the validity of pTpRxState, see
                    [SBSW_CANTP_INTERNAL_WRITE_RXSTATE]
                  - Count parameter pTpRxState->PayloadLength is set in different sections of the code but can never be
                    larger than CanTp_RxCfg_GetMaxPayload.
  \COUNTERMEASURE \R [CM_CANTP_RXMAXPAYLOADLENGTH]

\ID SBSW_CANTP_MEMCPY_CALL_FCDATA
  \DESCRIPTION    Call to CanTp_Util_MemCpy in order to copy a flow control frame to the TxState struct. The parameters
                  pDest and Count must be valid and consistent.
                  - pDest parameter is valid since it references the FCData array of the TxState struct. The array size
                    is 4. For validity of TxState pointer, see [SBSW_CANTP_INTERNAL_WRITE_TXSTATE].
                  - Count parameter is calculated as CANTP_PCI_LENGTH_FC + lAddressingOffset, where CANTP_PCI_LENGTH_FC
                    is 3 and Addressing Offset can only be 1 or 0.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_MEMCPY_CALL_TXQUEUE
  \DESCRIPTION    Call to CanTp_Util_MemCpy in order to copy a CanTp frame to the TxQueue. The parameters pDest and
                  Count must be valid and consistent.
                  - pDest parameter is valid since it references the SduData array of the CanTp_TxQueueEntryType. The
                    array size is CANTP_MAX_FRAME_LENGTH.
                  - Count parameter is derived from the PaddingLength and SduLength values, which are passed to
                    CanTp_CanIfTransmit and are expected to be consistent with the SduDataPtr. The largest array which
                    is referenced by SduDataPtr (see [SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR]) has a size of
                    CANTP_MAX_FRAME_LENGTH.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_MEMCPY_CALL_TXFRAMEDATA
  \DESCRIPTION    Call to CanTp_Util_MemCpy from CanTp_TxTransmitFrame. The content of parameters pDest and Count must be valid
                  and consistent. The consistency is also needed at other code locations and is justified with
                  [SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR].
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_MEMCPY_CALL_TXFRAMEMETADATA
  \DESCRIPTION    Call to CanTp_Util_MemCpy from CanTp_TxTransmitFrame to append metadata to a PDU. The passed pDest parameter
                  (&pTpData->SduDataPtr[pTpData->SduLength]) points to the first element after the CAN frame payload. The
                  passed Count parameter contains the metadata's length. The pointer pTpData->SduDataPtr must point to an
                  array of length (CANTP_FRAME_FC_MAX_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH) or
                  (CANTP_MAX_FRAME_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH).
  \COUNTERMEASURE \R [CM_CANTP_MAXPDUMETADATALENGTH]

\ID SBSW_CANTP_MEMCPY_CALL_TXSDUMETADATA
  \DESCRIPTION    Call to CanTp_Util_MemCpy from CanTp_TxTransmitFrame to store the extracted Tx SDU metadata. The passed
                  pDest parameter (pTpTxState->SduMetadata) points to an array of lenght CANTP_MAX_SDU_METADATA_LENGTH.
                  The passed pSrc (CanTpTxInfoPtr->SduDataPtr) is assumed to be valid and forwarded unchanged. The passed
                  metadata length is less than or equal to CANTP_MAX_SDU_METADATA_LENGTH, which is generated depending on
                  the available addressing modes.
  \COUNTERMEASURE \R [CM_CANTP_MAXSDUMETADATALENGTH]

\ID SBSW_CANTP_RXINIT_WRITE_TXSEMAPHORE
  \DESCRIPTION    Write access to the CanTp_TxSemaphores array. The index is read by CanTp_RxCfg_GetTxFcConfPduId(RxHdl).
                  RxHdl is part of the struct referenced by the pTpRxState pointer, which is expected to refer to a valid
                  Rx state.
                  The write access only occurs for flow controls, i.e. the TA-Type of the connection must be 'physical'
                  The value read from the configuration must always be < CanTp_GetSizeOfTxSemaphores.
  \COUNTERMEASURE \R [CM_CANTP_RXCFG_TXFCCONFPDUIDS]

\ID SBSW_CANTP_RXINIT_WRITE_CHANNELMAP
  \DESCRIPTION    With dynamic channel assignment, the RxHdl from the Rx state struct is used as index for CanTp_RxChannelMap.
                  CanTp_RxInit expects the state struct pointer to be valid and initialized, which implies that RxHdl
                  is < CanTp_Cfg_GetNumRxHdls.
                  Since CanTp_Cfg_GetNumRxHdls is mapped to CanTp_GetSizeOfRxSduCfg in CanTp_Priv.h, the CanTp_RxChannelMap
                  array must have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_RXINIT_CALL_RXSTATE
  \DESCRIPTION    pTpRxState is used as function parameter to CanTp_RxInit in order to reset the connection. The pointer is
                  retrieved by CanTp_RxGetActiveChannelPtr and checked to be not NULL.
                  The handle parameter to get the channel must be valid. It is retrieved via the CanTp_RxSduSnv2Hdl
                  indirection table (macro CanTp_RxGetSduHdlBySduId). The range and the availability (in case of post
                  build) of CanTpRxSduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_TXINIT_WRITE_TXSEMAPHORE
  \DESCRIPTION    Write access to the CanTp_TxSemaphores array. The index is read by CanTp_TxCfg_GetTxConfPduId(TxHdl).
                  TxHdl is part of the struct referenced by the pTpTxState pointer, which is expected to refer to a valid
                  Tx state.
                  The value read from the configuration must always be < CanTp_GetSizeOfTxSemaphores.
  \COUNTERMEASURE \R [CM_CANTP_TXCFG_TXCONFPDUIDS]

\ID SBSW_CANTP_TXINIT_WRITE_CHANNELMAP
  \DESCRIPTION    With dynamic channel assignment, the TxHdl from the Tx state struct is used as index for CanTp_TxChannelMap.
                  CanTp_TxInit expects the state struct pointer to be to be valid and initialized, which implies that TxHdl
                  is < CanTp_Cfg_GetNumTxHdls.
                  Since CanTp_Cfg_GetNumTxHdls is mapped to CanTp_GetSizeOfTxSduCfg in CanTp_Priv.h, the CanTp_TxChannelMap
                  array must have the same size as CanTp_TxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_TXARRAYSIZES]

\ID SBSW_CANTP_TXSTART_CALL_TXSTATE
  \DESCRIPTION    In CanTp_TxStartConnection an internal function is called, where the TpTxState parameter is retrieved
                  through CanTp_TxGetFreeChannelPtr and checked to be not NULL.
                  The handle parameter to get the channel must be valid. It is passed to CanTp_TxStartConnection() in
                  CanTp_Transmit. There it is derived from the CanTpTxSduId parameter via the CanTp_TxSduSnv2Hdl indirection
                  table (macro CanTp_TxGetSduHdlBySduId) and CanTp_TxGetChannelPtr.
                  The range and the availability (in case of post build) of CanTpTxSduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_TXSTART_WRITE_TXSTATE
  \DESCRIPTION    In CanTp_TxStartConnection a write access to the TpTxState pointer occurs, which is retrieved through
                  CanTp_TxGetFreeChannelPtr and checked to be not NULL.
                  The handle parameter to get the channel must be valid. It is passed to CanTp_TxStartConnection() in
                  CanTp_Transmit. There it is derived from the CanTpTxSduId parameter via the CanTp_TxSduSnv2Hdl indirection
                  table (macro CanTp_TxGetSduHdlBySduId) and CanTp_TxGetChannelPtr.
                  The range and the availability (in case of post build) of CanTpTxSduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_TXINIT_CALL_TXSTATE
  \DESCRIPTION    pTpTxState is used as function parameter to CanTp_TxInit in order to reset the connection. The pointer is
                  retrieved by CanTp_TxGetActiveChannelPtr and checked to be not NULL.
                  The handle parameter to get the channel must be valid. It is retrieved via the CanTp_TxSduSnv2Hdl
                  indirection table (macro CanTp_TxGetSduHdlBySduId). The range and the availability (in case of post
                  build) of CanTpTxSduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_RXINITSTATE_CALL_SDUHDL
  \DESCRIPTION    Call to CanTp_RxInitState with static channel assignment. The pointer parameter references
                  CanTp_RxState[SduHdl]. SduHdl iterates from 0 to (CanTp_Cfg_GetNumRxHdls-1), where CanTp_Cfg_GetNumRxHdls
                  is mapped to CanTp_GetSizeOfRxSduCfg in CanTp_Priv.h.
                  Therefore CanTp_RxState must have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_RXINITSTATE_CALL_CHANNELHDL
  \DESCRIPTION    Call to CanTp_RxInitState. The pointer parameter references CanTp_RxState[ChannelHdl]. ChannelHdl
                  iterates from 0 to (CanTp_Cfg_GetNumRxChannels-1), where CanTp_Cfg_GetNumRxChannels is mapped to
                  CanTp_GetSizeOfRxState and can be assumed to be in range.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXINITSTATE_CALL_SDUHDL
  \DESCRIPTION    Call to CanTp_TxInitState with static channel assignment. The pointer parameter references
                  CanTp_TxState[SduHdl]. SduHdl iterates from 0 to (CanTp_Cfg_GetNumTxHdls-1), where CanTp_Cfg_GetNumTxHdls
                  is mapped to CanTp_GetSizeOfTxSduCfg in CanTp_Priv.h.
                  Therefore CanTp_TxState must have the same size as CanTp_TxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_TXARRAYSIZES]

\ID SBSW_CANTP_TXINITSTATE_CALL_CHANNELHDL
  \DESCRIPTION    Call to CanTp_TxInitState. The pointer parameter references CanTp_TxState[ChannelHdl]. ChannelHdl
                  iterates from 0 to (CanTp_Cfg_GetNumTxChannels-1), where CanTp_Cfg_GetNumTxChannels is mapped to
                  CanTp_GetSizeOfTxState and can be assumed to be in range.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXQUEUE_WRITE_ENTRY
  \DESCRIPTION    When using the TxQueue, accesses to the queue entries are encapsulated by macros. These macros return
                  an element of the CanTp_TxQueue.Entries array, which is of the size CANTP_TX_QUEUE_SIZE.
                  The index used by the macros is either CanTp_TxQueue.ReadPos or CanTp_TxQueue.WritePos.
                  It have been verified by review that these values are either set to zero, or a bit masked upon
                  modification is used to ensure that the value doesn't exceed the array size. The TxConfPduId used as index is also
                  expected to be valid.
  \COUNTERMEASURE \R [CM_CANTP_TXCFG_TXCONFPDUIDS]

\ID SBSW_CANTP_TXQUEUECANCEL_WRITE_TXSEMAPHORE
  \DESCRIPTION    TxConfPduId is used for write accesses to CanTp_TxSemaphores and CanTp_TxQueue. The PduId is read by
                  CanTp_TxCfg_GetTxConfPduId / CanTp_RxCfg_GetTxFcConfPduId, according to the SduHdl and Direction parameters.
                  CanTp_TxQueueCancel expects that both parameters are valid and consistent.
                  For Rx N-SDUs, the semaphore is only used for flow controls, i.e. the TA-Type of the connection must be 'physical'
  \COUNTERMEASURE \R [CM_CANTP_TXCFG_TXCONFPDUIDS]
                  \R [CM_CANTP_RXCFG_TXFCCONFPDUIDS]

\ID SBSW_CANTP_TXQUEUCANCEL_CALL_RX
  \DESCRIPTION    A Call to CanTp_TxQueueCancel expects a valid Rx or Tx handle, depending on the direction. Here the
                  function is called with direction = Rx, and RxHdl is part of the struct referenced by the pTpRxState
                  pointer, which is a function parameter here and expected to refer to a valid Rx state.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXQUEUCANCEL_CALL_TX
  \DESCRIPTION    A Call to CanTp_TxQueueCancel expects a valid Rx or Tx handle, depending on the direction. Here the
                  function is called with direction = Tx, and TxHdl is part of the struct referenced by the pTpTxState
                  pointer, which is a function parameter here and expected to refer to a valid Rx state.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXQUEUEPROCESS_WRITE_TXSEMAPHORE
  \DESCRIPTION    TxConfPduId is used for write accesses to CanTp_TxSemaphores and CanTp_TxQueue. The PduId is
                  passed as parameter and expected to be < CanTp_Cfg_GetNumTxConfPdus, which is mapped to
                  CanTp_GetSizeOfTxSemaphores in CanTp_Priv.h.
                  The CanTp_TxQueue array must therefore have the same size as CanTp_TxSemaphores.
  \COUNTERMEASURE \R [CM_CANTP_TXCONFARRAYSIZES]

\ID SBSW_CANTP_RXTXINIT_CALL_QUEUEDHDL
  \DESCRIPTION    A handle, which have been read from the TxQueue, is used to get the state pointer which is used as
                  parameter for CanTp_RxInit/CanTpTxInit, depending on the queued direction.
                  All values, which are read from the queue, can be assumed as valid here (see analysis for
                  [SBSW_CANTP_CANIFTRANSMIT_CALL_TXQUEUE] and [SBSW_CANTP_TXQUEUE_WRITE_ENTRY]).
                  Both values (Handle and Direction) are only written to the queue in CanTp_CanIfTransmitFrame. There
                  the values are passed as parameters and are expected to be correct and consistent.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXQUEUEPROCESS_CALL_RX
  \DESCRIPTION    CanTp_TxQueueProcess is called by CanTpMainFunctionRx, where the TxConfPduId parameter is read by
                  CanTp_RxCfg_GetTxFcConfPduId. The index is already checked before to be not invalid.
  \COUNTERMEASURE \R [CM_CANTP_RXCFG_TXFCCONFPDUIDS]

\ID SBSW_CANTP_RXTRANSMITFRAME_WRITE_SDUDATAPTR
  \DESCRIPTION    Write access to SduDataPtr, either with constant or calculated index. The pointer itself is
                  initialized at the beginning of CanTp_RxFrame to the local array lFCBuffer with size
                  CANTP_FRAME_FC_MAX_LENGTH, which is at least 4. The max offset for write accesses to SduDataPtr
                  is (SduLength + CANTP_FRAME_OFFSET_FC_STMIN). SduLength can here be 0 or 1,
                  CANTP_FRAME_OFFSET_FC_STMIN is 2 --> sum is always below array size
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR
  \DESCRIPTION    Write access to SduDataPtr, either with constant or calculated index. The pointer is also used in
                  different function calls.
                  - the pointer itself is initialized at the beginning of CanTp_TxTransmitFrame to the local array
                    lTxFrameDataBuffer with size CANTP_MAX_FRAME_LENGTH.
                  - the max pointer offset for write accesses and usage with MemCopy is
                    (PCIOffset + AddressOffset + MaxPayloadLength), which have to be less than CANTP_MAX_FRAME_LENGTH.
                    --> PCIOffset depends on the frame type.
                    --> AddressOffset depends on the Addressing offset
                    --> MaxPayloadLength is read from config by CanTp_TxCfg_GetMaxPayload
                    FrameType | PCIOffset | AddressOffset | PayloadLength        ||                 Requirement
                    ----------+-----------+---------------+----------------------++-----------------------------------------------
                    .. SF ... | ... 1 ... | 0 (std) ..... | MaxPayloadLength ... || (MaxPayloadLength + 1) <= CANTP_MAX_FRAME_LENGTH
                    .. SF ... | ... 1 ... | 1 (ext / mix) | MaxPayloadLength ... || (MaxPayloadLength + 2) <= CANTP_MAX_FRAME_LENGTH
                    .. LSF... | ... 2 ... | 0 (std) ..... | MaxPayloadLength - 1 || (MaxPayloadLength + 1) <= CANTP_MAX_FRAME_LENGTH
                    .. LSF... | ... 2 ... | 1 (ext / mix) | MaxPayloadLength - 1 || (MaxPayloadLength + 2) <= CANTP_MAX_FRAME_LENGTH
                    .. FF.... | ... 2 ... | 0 (std) ..... | MaxPayloadLength - 1 || (MaxPayloadLength + 1) <= CANTP_MAX_FRAME_LENGTH
                    .. FF.... | ... 2 ... | 1 (ext / mix) | MaxPayloadLength - 1 || (MaxPayloadLength + 2) <= CANTP_MAX_FRAME_LENGTH
                    .. LFF... | ... 6 ... | 0 (std) ..... | MaxPayloadLength - 5 || (MaxPayloadLength + 1) <= CANTP_MAX_FRAME_LENGTH
                    .. LFF... | ... 6 ... | 1 (ext / mix) | MaxPayloadLength - 5 || (MaxPayloadLength + 2) <= CANTP_MAX_FRAME_LENGTH
                    .. CF.... | ... 1 ... | 0 (std) ..... | MaxPayloadLength ... || (MaxPayloadLength + 1) <= CANTP_MAX_FRAME_LENGTH
                    .. CF.... | ... 1 ... | 1 (ext / mix) | MaxPayloadLength ... || (MaxPayloadLength + 2) <= CANTP_MAX_FRAME_LENGTH
  \COUNTERMEASURE \R [CM_CANTP_TXMAXFRAMELENGTH]

\ID SBSW_CANTP_STOPSEPARATIONTIME_WRITE_TXSTATE
  \DESCRIPTION    The TpTxState pointer is used as function parameter and for write access. The pointer is retrieved by
                  CanTp_TxGetActiveChannelPtr and checked to be not NULL.
                  To get a valid pointer, the handle parameter to get the channel must be valid. It is retrieved via
                  the CanTp_TxSduSnv2Hdl indirection table (macro CanTp_TxGetSduHdlBySduId). The range and the availability
                  (in case of post build) of CanTpTxSduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_RXGETFREECHANNEL_WRITE_CHANNELMAP
  \DESCRIPTION    Write access to the CanTp_RxChannelMap array, indexed by the RxHdl parameter. CanTp_RxGetFreechannelPtr
                  expects RxHdl to be < CanTp_Cfg_GetNumRxHdls, which is mapped to CanTp_GetSizeOfRxSduCfg in CanTp_Priv.h.
                  The CanTp_RxChannelMap array must therefore have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_RXGETFREECHANNEL_WRITE_STATE
  \DESCRIPTION    Write access to pTpRxState pointer, which is initialized before, depending on the channel assignment:
                  - dynamic: pointer is set to CanTp_RxState array, indexed by lRxChannelHdl, which iterates between 0
                    and (CanTp_Cfg_GetNumRxChannels-1). CanTp_Cfg_GetNumRxChannels is mapped to CanTp_GetSizeOfRxState
                    in CanTp_Priv.h, so lRxChannelHdl is always in range.
                  - static: pointer is set to CanTp_RxState array, indexed by RxHdl parameter. RxHdl is expected to
                    be < CanTp_Cfg_GetNumRxHdls, which is mapped to CanTp_GetSizeOfRxSduCfg in CanTp_Priv.h.
                    The CanTp_RxState array must therefore have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_TXGETFREECHANNEL_WRITE_CHANNELMAP
  \DESCRIPTION    Write access to the CanTp_TxChannelMap array, indexed by the TxHdl parameter. CanTp_TxGetFreechannelPtr
                  expects TxHdl to be < CanTp_Cfg_GetNumTxHdls, which is mapped to CanTp_GetSizeOfTxSduCfg in CanTp_Priv.h.
                  The CanTp_TxChannelMap array must therefore have the same size as CanTp_TxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_TXARRAYSIZES]

\ID SBSW_CANTP_TXGETFREECHANNEL_WRITE_STATE
  \DESCRIPTION    Write access to pTpTxState pointer, which is initialized before, depending on the channel assignment:
                  - dynamic: pointer is set to CanTp_TxState array, indexed by lTxChannelHdl, which iterates between 0
                    and (CanTp_Cfg_GetNumTxChannels-1). CanTp_Cfg_GetNumTxChannels is mapped to CanTp_GetSizeOfTxState
                    in CanTp_Priv.h, so lTxChannelHdl is always in range.
                  - static: pointer is set to CanTp_TxState array, indexed by TxHdl parameter. TxHdl is expected to
                    be < CanTp_Cfg_GetNumTxHdls, which is mapped to CanTp_GetSizeOfTxSduCfg in CanTp_Priv.h.
                    The CanTp_TxState array must therefore have the same size as CanTp_TxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_TXARRAYSIZES]

\ID SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TPDATAPTR
  \DESCRIPTION    The TpDataPtr parameter, as well as the SduDataPtr and SduLength, which are part of the referenced
                  struct, are expected to be valid and consistent. The padding length from the PduTxData pointer is
                  always expected to be less than or equal to the length of the buffer referenced by the SduDataPtr.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_CANIFTRANSMITFRAME_WRITE_TXSEMAPHORE
  \DESCRIPTION    The TxConfPduId, which is part of the struct referenced by the PduTxData pointer parameter, is used as
                  array index for the CanTp_TxSemaphores and CanTp_TxQueue arrays. It is expected to be < CanTp_Cfg_GetNumTxConfPdus,
                  which is mapped to CanTp_GetSizeOfTxSemaphores in CanTp_Priv.h.
                  The CanTp_TxQueue array must therefore have the same size as CanTp_TxSemaphores.
  \COUNTERMEASURE \R [CM_CANTP_TXCONFARRAYSIZES]

\ID SBSW_CANTP_CANIFTRANSMITFRAME_CALL_TXDATA
  \DESCRIPTION    Call to CanTp_CanIfTransmitFrame for a SF, FF or CF. The following constraints given in the function
                  description must be fulfilled:
                  - "pTpData and pTpData->SduDataPtr are valid pointers": both pointers reference local variables. -> ok
                  - "pTpData->SduLength is less or equal pPduTxData->PaddingLength":
                    This is guaranteed by CanTp_Util_PaddingLength, which calculates the PaddingLength. -> ok
                  - "pPduTxData->PaddingLength must not exceed the size of the array referenced by pTpData->SduDataPtr":
                    the consistency is also needed at other code locations and is justified with
                    [see SBSW_CANTP_TXTRANSMITFRAME_WRITE_SDUDATAPTR].
                  - "pPduTxData->TxConfPduId is a valid CanTp TxConfPduId (< CanTp_Cfg_GetNumTxConfPdus)":
                    TxConfPduId is read from the configuration by CanTp_TxCfg_GetTxConfPduId.
                  - "pPduTxData->SduHdl and pPduTxData->SduDirection must refer to a valid Rx / Tx handle": SduHdl is
                    set to TxHdl, which is valid in this context, and SduDirection is set to CANTP_DIR_TX accordingly.
  \COUNTERMEASURE \R [CM_CANTP_TXCFG_TXCONFPDUIDS]

\ID SBSW_CANTP_CANIFTRANSMITFRAME_CALL_FCDATA
  \DESCRIPTION    Call to CanTp_CanIfTransmitFrame for a flow control frame. The following constraints given in the
                  function description must be fulfilled:
                  - "pTpData and pTpData->SduDataPtr are valid pointers": both pointers reference local variables. -> ok
                  - "pTpData->SduLength is less or equal pPduTxData->PaddingLength":
                    This is guaranteed by CanTp_Util_PaddingLength, which calculates the padding length. -> ok
                  - "pPduTxData->PaddingLength must not exceed the size of the array referenced by pTpData->SduDataPtr":
                    SduDataPtr reference lFCBuffer, which is of size CANTP_FRAME_FC_MAX_LENGTH. This can be 4 or 8,
                    depending on padding activation.
                    PaddingLength is calculated by CanTp_Util_PaddingLength and either equals lFCFrameData.SduLength
                    (can be 3 or 4) or is 8 (padding active). -> ok
                  - "pPduTxData->TxConfPduId is a valid CanTp TxConfPduId (< CanTp_Cfg_GetNumTxConfPdus)":
                    TxConfPduId is read from the configuration tables by CanTp_RxCfg_GetTxFcConfPduId.
                  - "pPduTxData->SduHdl and pPduTxData->SduDirection must refer to a valid Rx / Tx handle": SduHdl is
                    set to RxHdl, which is valid in this context, and SduDirection is set to CANTP_DIR_RX accordingly.
  \COUNTERMEASURE \R [CM_CANTP_RXCFG_TXFCCONFPDUIDS]

\ID SBSW_CANTP_CANIFRXINDICATIONCF_WRITE_TXSEMAPHORE
  \DESCRIPTION    Write access to CanTp_TxSemaphores array. The index is read by CanTp_RxCfg_GetTxFcConfPduId(RxHdl).
                  RxHdl is a parameter and expected to be < CanTp_Cfg_GetNumRxHdls, which is mapped to CanTp_GetSizeOfRxSduCfg
                  in CanTp_Priv.h and can therefore be assumed to be in range.
                  The write access only occurs for flow controls, i.e. the TA-Type of the connection must be 'physical'.
                  The value read from the configuration must always be < CanTp_GetSizeOfTxSemaphores.
  \COUNTERMEASURE \R [CM_CANTP_RXCFG_TXFCCONFPDUIDS]

\ID SBSW_CANTP_CANIFRXINDICATION_CALL_PDUINFO
  \DESCRIPTION    The passed pointers are valid, since they both point to local PduInfoType structs.
                  SduHdl is passed to CanTp_CanIfRxIndication in order process a reception. The SduHdl is derived from
                  RxPduId, the frame type and the address by the function CanTp_Cfg_GetSduHdlByRxPduOnly and
                  CanTp_Cfg_GetSduHdlByRxPduAddress. These function which utilizes the CSL macros to resolve the indirections
                  from CanTp_RxPduMap to CanTp_RxSduCfg/CanTp_RxSduCfg:
                   - CanTp_GetRxSduCfgInd
                   - CanTp_GetRxSduCfgIndStartIdxOfRxPduMap
                   - CanTp_GetRxSduCfgIndEndIdxOfRxPduMap
                   - CanTp_GetTxSduCfgInd
                   - CanTp_GetTxSduCfgIndStartIdxOfRxPduMap
                   - CanTp_GetTxSduCfgIndEndIdxOfRxPduMap
                  The range and of RxPduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_CANIFRXINDICATION_CALL_RXSTATE
  \DESCRIPTION    The pTpRxState pointer is set to the RxState array through CanTp_RxGetFreeChannel / Canp_RxGetActiveChannel.
                  The SduHdl, which is used for this, is derived in CanTp_RxIndication from RxPduId, the frame type and the
                  address by the function CanTp_Cfg_GetSduHdlByRxPduOnly and CanTp_Cfg_GetSduHdlByRxPduAddress.
                  For Rx direction, these functions utilize the following CSL macros to resolve the indirections and retrieve
                  a valid RxHdl:
                   - CanTp_GetRxSduCfgInd
                   - CanTp_GetRxSduCfgIndStartIdxOfRxPduMap
                   - CanTp_GetRxSduCfgIndEndIdxOfRxPduMap
                  The range and of RxPduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_CANIFRXINDICATION_CALL_TXSTATE
  \DESCRIPTION    The pTpTxState pointer is set to the TxState array through Canp_TxGetActiveChannel. The SduHdl, which
                  is used for this, is derived in CanTp_RxIndication from RxPduId, the frame type and the address by
                  the function CanTp_Cfg_GetSduHdlByRxPduOnly and CanTp_Cfg_GetSduHdlByRxPduAddress.
                  For Tx direction, these functions utilize the following CSL macros to resolve the indirections and retrieve
                  a valid TxHdl:
                   - CanTp_GetTxSduCfgInd
                   - CanTp_GetTxSduCfgIndStartIdxOfRxPduMap
                   - CanTp_GetTxSduCfgIndEndIdxOfRxPduMap
                  The range and of RxPduId is verified by DET.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_CANIFTXCONFIRMATION_CALL_RXTXSTATE
  \DESCRIPTION    CanTp_CanIfTxConfirmationFC is called from CanTp_TxConfirmation. The pTpRxState pointer is set to the
                  RxState array through Canp_RxGetActiveChannel. The SduHdl, which is used for this, read from
                  CanTp_TxSemaphores and checked to be no "invalid handle".
                  Precondition for a reliable SduHdl is that TxPduId, which is used as index for CanTp_TxSemaphores, is
                  valid.
                  The only location in code where CanTp_TxSemaphores.Handle is set to a different value than "invalid" is in
                  CanTp_CanIfTransmit, which expects a valid Rx/Tx handle according to the direction.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_CANIFTXCONFIRMATION_CALL_TXTXSTATE
  \DESCRIPTION    CanTp_CanIfTxConfirmation is called from CanTp_TxConfirmation. The pTpTxState pointer is set to the
                  TxState array through Canp_TxGetActiveChannel. The SduHdl, which is used for this, read from
                  CanTp_TxSemaphores and checked to be no "invalid handle".
                  Precondition for a reliable SduHdl is that TxPduId, which is used as index for CanTp_TxSemaphores, is
                  valid.
                  The only location in code where CanTp_TxSemaphores.Handle is set to a different value than "invalid" is in
                  CanTp_CanIfTransmit, which expects a valid Rx/Tx handle according to the direction.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_RESETCHANNELS_WRITE_RXHDL
  \DESCRIPTION    CanTp_ResetChannels iterates between 0 and (CanTp_Cfg_GetNumRxHdls-1) and resets for each Rx SduHdl the
                  according entries in the CanTp_RxChannelMap and CanTp_DynFCParameters arrays.
                  CanTp_Cfg_GetNumRxHdls is mapped to CanTp_GetSizeOfRxSduCfg in CanTp_Priv.h.
                  The CanTp_RxChannelMap and CanTp_DynFCParameters arrays must therefore have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_RESETCHANNELS_WRITE_TXHDL
  \DESCRIPTION    CanTp_ResetChannels iterates between 0 and (CanTp_Cfg_GetNumTxHdls-1) and resets for each Tx SduHdl the
                  according entries in the TxChannelMap array.
                  CanTp_Cfg_GetNumTxHdls is mapped to CanTp_GetSizeOfTxSduCfg in CanTp_Priv.h.
                  The CanTp_TxChannelMap array must therefore have the same size as CanTp_TxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_TXARRAYSIZES]

\ID SBSW_CANTP_RESETCHANNELS_WRITE_TXSEMAPHORE
  \DESCRIPTION    CanTp_ResetChannels iterates between 0 and (CanTp_Cfg_GetNumTxConfPdus-1) and resets for each TxConfPdu
                  the entries of the CanTp_TxSemaphores and CanTp_TxQueue arrays.
                  CanTp_Cfg_GetNumTxConfPdus is mapped to CanTp_GetSizeOfTxSemaphores in CanTp_Priv.h.
                  The CanTp_TxQueue array must therefore have the same size as CanTp_TxSemaphores.
  \COUNTERMEASURE \R [CM_CANTP_TXCONFARRAYSIZES]

\ID SBSW_CANTP_RESETCHANNELS_WRITE_QUEUEENTRY
  \DESCRIPTION    Write access to the CanTp_TxQueue.Entries array. The array size and the loop boundary are both
                  CANTP_TX_QUEUE_SIZE, which is not generated but defined locally.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_INDEX
  \DESCRIPTION    Write to the CanTp_DynFCParameters array. The index is derived from the id parameter via the the
                  CanTp_RxSduSnv2Hdl indirection table (macro CanTp_RxGetSduHdlBySduId).
                  The range of the id parameter is verified by DET to be < CanTp_Cfg_GetNumRxSduIds.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_SIZE
  \DESCRIPTION    CanTp_ChangeParameter writes to the CanTp_DynFCParameters array, where the index is a valid index to
                  CanTp_RxSduCfg (derived from ComStackLib indirection, see [SBSW_CANTP_CHANGEPARAMETER_WRITE_DYNFCPARAM_INDEX]
                  The CanTp_DynFCParameters array must therefore have the same size as CanTp_RxSduCfg.
  \COUNTERMEASURE \R [CM_CANTP_RXARRAYSIZES]

\ID SBSW_CANTP_READPARAMETER_WRITE_VALUE
  \DESCRIPTION    The CanTp_ReadParameter writes to the 'value' pointer parameter.
                  General assumption for SafeBSW: the caller ensures that the memory referenced by the pointer is valid.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_GETVERSION_WRITE_VERSION
  \DESCRIPTION    The CanTp_GetVersionInfo writes to the 'versioninfo' pointer parameter.
                  General assumption for SafeBSW: the caller ensures that the memory referenced by the pointer is valid.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXCONFIRMATION_WRITE_TXSEMAPHORE
  \DESCRIPTION    In CanTp_TxConfirmation, the parameter TxPduId is used as index for the CanTp_TxSemaphores array. It
                  is checked by DET that is is < CanTp_Cfg_GetNumTxConfPdus, which is mapped to CanTp_GetSizeOfTxSemaphores
                  in CanTp_Priv.h.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_PDURCOPYRXDATA_CALL_PDUINFO
  \DESCRIPTION    PduR_CanTpCopyRxData is called two pointer parameters.
                  - the PduInfo pointer refers to a local variable and is therefore valid. The PduInfoStruct contains
                    also the SduDataPtr which is initialized to the payload array of the RxState struct. The max value
                    of the according SduDataLength is read from config by CanTp_RxCfg_GetMaxPayload. It must be checked
                    that it does not exceed the size of the Payload array (CANTP_MAX_PAYLOAD_LENGTH).
                    In some cases, the SduLength is set to zero and the SduDataPointer remains uninitialized. It is
                    expected, as documented in the SWS, that the upper layer does not access the SduDataPtr for a copy
                    request with 0 bytes.
                  - the buffer size pointer refers to an element of CanTp_RxState, which is valid in this context
  \COUNTERMEASURE \R [CM_CANTP_RXMAXPAYLOADLENGTH]

\ID SBSW_CANTP_PDURCOPYTXDATA_CALL_PDUINFO
  \DESCRIPTION    PduR_CanTpCopyTxData is called with three pointer parameters.
                  - the PduInfo pointer refers to a local variable and is therefore valid. The PduInfoStruct contains
                    also the SduDataPtr which is initialized to the payload array of the TxState struct. The max value
                    of the according SduDataLength is read from config by CanTp_TxCfg_GetMaxPayload. It must be checked
                    that this does not exceed the size of the Payload array (CANTP_MAX_PAYLOAD_LENGTH).
                  - the retry pointer is not supported and passed as NULL (as specified by AUTOSAR)
                  - the available data pointer refers to a local variable
  \COUNTERMEASURE \R [CM_CANTP_TXMAXPAYLOADLENGTH]

\ID SBSW_CANTP_PDURSTARTOFRECEPTION_CALL_RXSTATE
  \DESCRIPTION    PduR_CanTpStartOfReception is called with several pointer parameters.
                  - the PduInfo pointer (if available; see definition of CanTp_PduRStartOfReception macro) is always NULL.
                  - the other parameters are derived from the pTpTxState pointer, which is valid in this context.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_CANIFTRANSMIT_CALL_TXQUEUE
  \DESCRIPTION    CanIf_Transmit is called with parameters that have been read from CanTp_TxQueue[ReadPosition]. It is
                  checked before that no invalid handle is stored at the read position, so the data which is read
                  from the queue can assumed to be valid. Out of bound read accesses are prevented by using a bit mask
                  whenever ReadPos is modified (see also [SBSW_CANTP_TXQUEUE_WRITE_ENTRY].
                  The only location in code where a valid queue entry is written is in CanTp_CanIfTransmitFrame. There
                  it is filled with the same values which are used for the according CanIf_Transmit call.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_CANIFTRANSMIT_CALL_TPDATA
  \DESCRIPTION    CanIf_Transmit is called from CanTp_CanIfTransmitFrame. The parameters are parameters of
                  CanTp_CanIfTransmitFrame and expected to be valid and consistent.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_APPLNOTIFICATION_CALL_PDUINFO
  \DESCRIPTION    Call of a proprietary debugging call-out. All variables and values used as parameters are also used
                  elsewhere for "real" APIs. Please refer to those for justification, analysis and countermeasures.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_LOLAYERTRANSMIT_FCTPTR
  \DESCRIPTION    A lower layer's Transmit function is called by dereferencing a pointer from the component's generated
                  data. Pointers related to Transmit functions of the lower layers are always expected to be valid.
  \COUNTERMEASURE \R [CM_CANTP_LOLAYERTRANSMITFCT]

\ID SBSW_CANTP_LOLAYERCANCELTRANSMIT_FCTPTR
  \DESCRIPTION    A lower layer's CancelTransmit function is called by dereferencing a pointer from the component's
                  generated data. Pointers related to CancelTransmit functions could be null if a CancelTransmit
                  function is not provided by the lower layer.
  \COUNTERMEASURE \R [CM_CANTP_LOLAYERCANCELTRASNMITFCT]

\ID SBSW_CANTP_TXSDUMETADATAMATCH_WRITE_LOCALBUFFER
  \DESCRIPTION    The local buffer where the SDU metadata is assembled has length CANTP_MAX_SDU_METADATA_LENGTH.
                  CANTP_MAX_SDU_METADATA_LENGTH is generated based on the available addressing modes.
  \COUNTERMEASURE \R [CM_CANTP_MAXSDUMETADATALENGTH]

\ID SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PDEST
  \DESCRIPTION    The parameter pDest passed to CanTp_Util_RxAssembleSduMetadata must be a pointer to an array of length
                  CANTP_MAX_SDU_METADATA_LENGTH. CANTP_MAX_SDU_METADATA_LENGTH is generated based on the available
                  addressing modes.
  \COUNTERMEASURE \R [CM_CANTP_MAXSDUMETADATALENGTH]

\ID SBSW_CANTP_RXASSEMBLESDUMETADATA_WRITE_PLENGTH
  \DESCRIPTION    The parameter pLength passed to CanTp_Util_RxAssembleSduMetadata is expected to be a valid pointer.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_INTERN_WRITE_PDUMETADATA
  \DESCRIPTION    The members FcPduMetadata of the RxState type and DataPduMetadata of the TxState type point to arrays
                  of length CANTP_MAX_PDU_METADATA_LENGTH. CANTP_MAX_PDU_METADATA_LENGTH is generated based on the
                  available addressing modes.
  \COUNTERMEASURE \R [CM_CANTP_MAXPDUMETADATALENGTH]

\ID SBSW_CANTP_TXSTARTCONNECTION_CALL_PDUINFO
  \DESCRIPTION    The passed CanTpTxInfoPtr is obtained from the upper layer and checked against null.
  \COUNTERMEASURE \R [CM_CANTP_TXINFOPTR]

\ID SBSW_CANTP_RXGETFREECHANNEL_CALL_PTRS
  \DESCRIPTION    The pointers pPayloadInfo and pMetadataInfo are assumed to be valid and forwarded unchanged to the 
                  CanTp_RxGetFreeChannelPtr function.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXGETFREECHANNEL_CALL_PTR
  \DESCRIPTION    The pointer CanTpTxInfoPtr is assumed to be valid (since it has to be checked in the CanTp_Transmit
                  function) and is forwarded unchanged to the CanTp_TxGetFreeChannelPtr function.
  \COUNTERMEASURE \N -

 \ID SBSW_CANTP_TXSDUMETADATAMATCH_CALL_PTRS
  \DESCRIPTION    The pointers pPayloadInfo and pMetadataInfo are assumed to be valid and forwarded unchanged to the
                  CanTp_Util_TxSduMetadataFromFcPduMatch function. The pTpTxState pointer is checked for validity
                  before the function call takes place.
  \COUNTERMEASURE \N -

 \ID SBSW_CANTP_RXSDUMETADATAMATCH_CALL_PTRS
  \DESCRIPTION    The pointers pPayloadInfo and pMetadataInfo are assumed to be valid and forwarded unchanged to the
                  CanTp_Util_RxSduMetadataFromDataPduMatch function. The pTpRxState pointer is checked for validity
                  before the function call takes place.
  \COUNTERMEASURE \N -

 \ID SBSW_CANTP_RXEXTRACTSDUMETADATA_CALL_PTRS
  \DESCRIPTION    The pointers pPayloadInfo and pMetadataInfo are assumed to be valid and forwarded unchanged to the
                  CanTp_Util_RxExtractSduMetadataInfo function. The pTpRxState pointer is checked for validity before
                  the function call takes place.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_TXEXTRACTSDUMETADATA_CALL_PTRS
  \DESCRIPTION    The pointer CanTpTxInfoPtr is assumed to be valid and forwarded unchanged to the function
                  CanTp_Util_TxExtractSduMetadataInfo. The pTpTxState pointer is checked for validity before the
                  function call takes place.
  \COUNTERMEASURE \N -

\ID SBSW_CANTP_RXASSEMBLESDUMETADATA_CALL_PTRS
  \DESCRIPTION    The pointers pPayloadInfo and pMetadataInfo are assumed to be valid and forwarded unchanged to the
                  CanTp_Util_RxAssembleSduMetadata function. The parameter argument passed as pDest points to an array
                  of length CANTP_MAX_SDU_METADATA_LENGTH and the argument assigned pLength is also a valid pointer,
                  since it points either to a local variable or a member of a valid RxState struct.
  \COUNTERMEASURE \N -

SBSW_JUSTIFICATION_END */


/* ------------------------------------------------------------------------------------------------------------------ */
/* Silent BSW Countermeasures                                                                                         */
/* ------------------------------------------------------------------------------------------------------------------ */
/*
--- Runtime Checks within the CanTp_Util_CheckConfigValidity function ---
The following countermeasures are implemented as runtime checks in CanTp_Util_CheckConfigValidity() and executed during initialization:
\CM CM_CANTP_RXMAXPAYLOADLENGTH   For all Rx N-SDUs, CanTp_RxCfg_GetMaxPayload must be less or equal CANTP_MAX_PAYLOAD_LENGTH
\CM CM_CANTP_TXMAXPAYLOADLENGTH   For all Tx N-SDUs, CanTp_TxCfg_GetMaxPayload must be less or equal CANTP_MAX_PAYLOAD_LENGTH

\CM CM_CANTP_TXMAXFRAMELENGTH     For all NormalAddressing or NormalFixed (0-byte address offset) Tx N-SDUs, (CanTp_TxCfg_GetMaxPayload + 1) must be less or equal CANTP_MAX_FRAME_LENGTH
                                  For all Extended or Mixed11 or Mixed29 Addressing Tx N-SDUs (1-byte address offset), (CanTp_TxCfg_GetMaxPayload + 2) must be less or equal CANTP_MAX_FRAME_LENGTH

\CM CM_CANTP_RXCFG_TXFCCONFPDUIDS In case of a physical Rx N-SDU, the macro CanTp_RxCfg_GetTxFcConfPduId must always return
                                  a value < CanTp_Cfg_GetNumTxConfPdus.

\CM CM_CANTP_TXCFG_TXCONFPDUIDS   The macro CanTp_TxCfg_GetTxConfPduId must always return a value < CanTp_Cfg_GetNumTxConfPdus.

\CM CM_CANTP_RXARRAYSIZES         The size of the following RAM arrays must have at least the size of CanTp_RxSduCfg, as
                                  its size defines the range of the general Rx handle:
                                  - CanTp_CalcBS           (only exists if CANTP_CONSTANT_BS == STD_ON)
                                  - CanTp_DynFCParameters  (only exists if CANTP_ENABLE_CHANGE_PARAM == STD_ON)
                                  - CanTp_RxChannelMap     (only exists if CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
                                  - CanTp_RxState          (only if CANTP_DYN_CHANNEL_ASSIGNMENT == STD_OFF)
\CM CM_CANTP_TXARRAYSIZES         The size of the following RAM arrays must have at least the size of CanTp_TxSduCfg, as
                                  its size defines the range of the general Tx handle:
                                  - CanTp_TxChannelMap     (only exists if CANTP_DYN_CHANNEL_ASSIGNMENT == STD_ON)
                                  - CanTp_TxState          (only if CANTP_DYN_CHANNEL_ASSIGNMENT == STD_OFF)
\CM CM_CANTP_TXCONFARRAYSIZES     The size of the following RAM array must have at least the size of CanTp_TxSemaphores,
                                  as its size defines the range of the general TxConf Pdu handle:
                                  - CanTp_TxQueue          (only exists if CANTP_TRANSMIT_QUEUE == STD_ON)

\CM CM_CANTP_LOLAYERTRANSMITFCT   The TransmitFct member of all the elements in the CanTp_LoLayerFcts array shall not be NULL_PTR.

\CM CM_CANTP_MAXSDUMETADATALENGTH    The macro CANTP_MAX_SDU_METADATA_LENGTH must fulfill the following conditions:
                                  - If CANTP_GENERIC_CONNECTIONS == STD_ON && CANTP_MIXED29_ADDRESSING == STD_ON, then CANTP_MAX_SDU_METADATA_LENGTH == 3
                                  - If CANTP_GENERIC_CONNECTIONS == STD_ON && CANTP_NORMALFIXED_ADDRESSING == STD_ON, then CANTP_MAX_SDU_METADATA_LENGTH >= 2
                                  - If CANTP_GENERIC_CONNECTIONS == STD_ON && (CANTP_EXTENDED_ADDRESSING == STD_ON || CANTP_MIXED11_ADDRESSING == STD_ON), then CANTP_MAX_SDU_METADATA_LENGTH >= 1

\CM CM_CANTP_MAXPDUMETADATALENGTH    The macro CANTP_MAX_PDU_METADATA_LENGTH must fulfill the following conditions:
                                  - If CANTP_GENERIC_CONNECTIONS == STD_ON && (CANTP_MIXED29_ADDRESSING == STD_ON || CANTP_NORMALFIXED_ADDRESSING == STD_ON), then CANTP_MAX_PDU_METADATA_LENGTH == 2


--- Runtime Checks outside the CanTp_Util_CheckConfigValidity function ---
\CM CM_CANTP_LOLAYERCANCELTRASNMITFCT Detect invalid pointers to CancelTransmit functions and avoid dereferencing them.

\CM CM_CANTP_TXINFOPTR    Detect any invalid CanTpTxInfoPtr passed to CanTp_Transmit and avoid dereferencing or forwarding it.

--- MSSV Plugin ---
\CM CM_CANTP_PRECOMPILEOPTIONS To ensure that all mandatory / excluded features are as expected, the following must be verified by MSSV:
                               - CANTP_DEV_ERROR_DETECT = STD_ON
                               - CANTP_SINGLE_RX_BUFFER_OPTIMIZED = STD_OFF
                               - MSR_PDUR_API_AR_VERSION is undefined
                               - CANTP_TX_QUEUE_SIZE = 4 (The generated files shall not redefine the value defined in CanTp_Types.h)
                               - CANTP_PDUR_API_AR_VERSION = 0x412
                               - CANTP_TX_FC_FROM_ISR is undefined
                               - CANTP_RX_GET_BUFFER_FROM_ISR is undefined
                               - CANTP_TX_GET_BUFFER_FROM_ISR is undefined
                               - CANTP_IGNORE_FC_WITH_RES_STMIN is undefined
                               - CANTP_IGNORE_CF_WITH_WRONG_SN is undefined
                               - CANTP_IGNORE_FC_OVFL_INVALID_FS is undefined
                               - CANTP_FAULT_TOLERANT_RXBUFFER is undefined
                               - CANTP_NUM_RX_SDUS > 0
                               - CANTP_NUM_TX_SDUS > 0
*/



/**********************************************************************************************************************
 *  END OF FILE: CanTp.c
 *********************************************************************************************************************/
