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
/*!        \file  CanTp.h
 *        \brief  CanTp main header file
 *
 *      \details  main header file of the CanTp to be included by other components which interact with the CanTp.
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
 *                        visath  FEATC-667:     FEAT-2144: Mixed11 Addressing Priorization
 *  03.03.01  2017-04-12  visath  ESCAN00091493: Modified the DET error reporting for extended and mixed11 addressing
 *  03.03.02  2018-02-23  visath  ESCAN00097375: Compiler warning: 'lTxHdl' : local variable is initialized but not referenced
 *                        visath  ESCAN00097790: Compiler warning:  'CanTpTxSduId' : unreferenced formal parameter
 *                        visath  ESCAN00097950: Compiler error: 'CanTp_GetRxSduCfgInd' undefined
 *                        visath  ESCAN00094451: CanTp_ApplStartSeparationTime is now called with the SDU's SNV
 *                        visath  ESCAN00098595: The main functions now always check if the module has been initialized
 *  03.03.03  2018-08-10  visath  ESCAN00100333: Always initialize all the Rx and Tx channel structures
 *  03.04.00  2018-12-13  visath  STORYC-6491:   Support the PduR as lower layer
 *  03.05.00  2019-03-12  visath  STORYC-7040:   Support metadata according to AR 4.2.2
 *                        visath  STORYC-5247:   MISRA-C:2012 Compliance
*********************************************************************************************************************/
#if !defined (CANTP_H)
#define CANTP_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CanTp_Types.h"

#include "CanTp_Cfg.h"
#include "CanTp_Lcfg.h"
#include "CanTp_PBcfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* --- Vendor and Module Identification ---------------------------------------------------------------------------- */
#define CANTP_VENDOR_ID                          (30u)
#define CANTP_MODULE_ID                          (0x23u)


/* --- AUTOSAR Software Specification Version Information ---------------------------------------------------------- */
# define CANTP_AR_RELEASE_MAJOR_VERSION          (4u)
# define CANTP_AR_RELEASE_MINOR_VERSION          (0u)
# define CANTP_AR_RELEASE_REVISION_VERSION       (3u)


/* --- Component Version Information ------------------------------------------------------------------------------- */
# define CANTP_SW_MAJOR_VERSION                  (3u)
# define CANTP_SW_MINOR_VERSION                  (5u)
# define CANTP_SW_PATCH_VERSION                  (0u)

# define CANTP_INSTANCE_ID_DET                   (0x00u)


/* --- API Service IDs --------------------------------------------------------------------------------------------- */
#define CANTP_SID_INIT                           (0x01u)
#define CANTP_SID_SHUTDOWN                       (0x02u)
#define CANTP_SID_TRANSMIT                       (0x03u)
#define CANTP_SID_RXINDICATION                   (0x04u)
#define CANTP_SID_TXCONFIRMATION                 (0x05u)
#define CANTP_SID_MAINFUNCTION                   (0x06u)
#define CANTP_SID_GETVERSIONINFO                 (0x07u)
#define CANTP_SID_CANCELTRANSMIT                 (0x08u)
#define CANTP_SID_CANCELRECEIVE                  (0x09u)
#define CANTP_SID_CHANGEPARAMETER                (0x0Au)
#define CANTP_SID_READPARAMETER                  (0x0Bu)
#define CANTP_SID_MAINFUNCTIONRX                 (0x20u)
#define CANTP_SID_MAINFUNCTIONTX                 (0x21u)

/* Vector-CanTp specific service-Ids */
#define CANTP_SID_RXGETBUFFER                    (0x30u)
#define CANTP_SID_TXGETBUFFER                    (0x31u)
#define CANTP_SID_RXTRANSMITFRAME                (0x32u)
#define CANTP_SID_TXTRANSMITFRAME                (0x33u)
#define CANTP_SID_RXINIT                         (0x34u)
#define CANTP_SID_TXINIT                         (0x35u)
#define CANTP_SID_STOPSEPARATIONTIME             (0x36u)

/* --- Error Codes ------------------------------------------------------------------------------------------------- */
#define CANTP_E_PARAM_CONFIG                     (0x01u)   /* !< Error code: invalid or inconsistent configuration                         */
#define CANTP_E_PARAM_ID                         (0x02u)   /* !< Error code: API call with invalid identifier                              */
#define CANTP_E_PARAM_POINTER                    (0x03u)   /* !< Error code: API call with an invalid pointer parameter                    */
#define CANTP_E_UNINIT                           (0x20u)   /* !< Error code: API call when CanTp is not initialized                        */
#define CANTP_E_INVALID_TX_ID                    (0x30u)   /* !< Error code: API call with invalid TxSduId / TxConfPduId                   */
#define CANTP_E_INVALID_RX_ID                    (0x40u)   /* !< Error code: API call with invalid RxPduId                                 */
#define CANTP_E_INVALID_TX_BUFFER                (0x50u)   /* !< Error code: size or pointer of Tx buffer invalid                          */
#define CANTP_E_INVALID_RX_BUFFER                (0x60u)   /* !< Error code: size or pointer of Rx buffer invalid                          */
#define CANTP_E_INVALID_TX_LENGTH                (0x70u)   /* !< Error code: transmission request with invalid data length                 */
#define CANTP_E_INVALID_RX_LENGTH                (0x80u)   /* !< Error code: invalid data length in a received SF or FF                    */
#define CANTP_E_INVALID_TATYPE                   (0x90u)   /* !< Error code: segmented Rx / Tx for functional Sdu                          */
#define CANTP_E_OPER_NOT_SUPPORTED               (0xA0u)   /* !< Error code: requested operation is not supported                          */
#define CANTP_E_COM                              (0xB0u)   /* !< Error code: protocol timeout or implementation specific error             */
#define CANTP_E_INVALID_RX_STATE                 (0xB1u)   /* !< Error code: Rx state machine is in an invalid state (Vector specific)     */
#define CANTP_E_INVALID_TX_STATE                 (0xB2u)   /* !< Error code: Tx state machine is in an invalid state (Vector specific)     */
#define CANTP_E_INVALID_FRAME_TYPE               (0xB3u)   /* !< Error code: an invalid frame type occurred (Vector specific)              */
#define CANTP_E_RX_COM                           (0xC0u)   /* !< Error code: reception error                                               */
#define CANTP_E_RX_TIMEOUT_AR                    (0xC1u)   /* !< Error code: N_Ar timeout (Vector specific)                                */
#define CANTP_E_RX_TIMEOUT_BR                    (0xC2u)   /* !< Error code: N_Br timeout (Vector specific)                                */
#define CANTP_E_RX_TIMEOUT_CR                    (0xC3u)   /* !< Error code: N_Cr timeout (Vector specific)                                */
#define CANTP_E_RX_INVALID_SN                    (0xC4u)   /* !< Error code: CF with invalid SN received (Vector specific)                 */
#define CANTP_E_RX_WFTMAX                        (0xC5u)   /* !< Error code: max number of wait frames reached (Vector specific)           */
#define CANTP_E_RX_RESTART                       (0xC6u)   /* !< Error code: connection terminated due to new SF/FF (Vector specific)      */
#define CANTP_E_RX_TRANSMIT_ERROR                (0xC7u)   /* !< Error code: transmission of a flow control frame failed (Vector specific) */
#define CANTP_E_TX_COM                           (0xD0u)   /* !< Error code: transmission error                                            */
#define CANTP_E_TX_TIMEOUT_AS                    (0xD1u)   /* !< Error code: N_As timeout (Vector specific)                                */
#define CANTP_E_TX_TIMEOUT_BS                    (0xD2u)   /* !< Error code: N_Bs timeout (Vector specific)                                */
#define CANTP_E_TX_TIMEOUT_CS                    (0xD3u)   /* !< Error code: N_Cs timeout (Vector specific)                                */
#define CANTP_E_TX_FC_OVFL                       (0xD4u)   /* !< Error code: FC.OVFL received (Vector specific)                            */
#define CANTP_E_TX_INVALID_FS                    (0xD5u)   /* !< Error code: FC with invalid flow status received (Vector specific)        */
#define CANTP_E_TX_RES_STMIN                     (0xD6u)   /* !< Error code: FC with res. STmin received but not allowed (Vector specific) */
#define CANTP_E_TX_TRANSMIT_ERROR                (0xD7u)   /* !< Error code: transmission of any frame failed (Vector specific)            */
#define CANTP_E_NO_ERROR                         (0xFFu)   /* !< non AR-error code, used for channel reset                                 */


/* --- Modes ------------------------------------------------------------------------------------------------------- */
#define CANTP_OFF                                (0x00u)
#define CANTP_ON                                 (0x01u)


/* --- Switch Default Settings ------------------------------------------------------------------------------------- */
/* UserConfig switches */
#if (!defined (CANTP_APPL_RX_SF_INDICATION))
# define CANTP_APPL_RX_SF_INDICATION             STD_OFF
#endif

#if (!defined (CANTP_APPL_RX_FF_INDICATION))
# define CANTP_APPL_RX_FF_INDICATION             STD_OFF
#endif

#if (!defined (CANTP_APPL_RX_CF_INDICATION))
# define CANTP_APPL_RX_CF_INDICATION             STD_OFF
#endif

#if (!defined (CANTP_APPL_FRAME_TRANSMISSION))
# define CANTP_APPL_FRAME_TRANSMISSION           STD_OFF
#endif

#if (!defined (CANTP_APPL_FRAME_CONFIRMATION))
# define CANTP_APPL_FRAME_CONFIRMATION           STD_OFF
#endif

#if !defined (CANTP_TX_FC_FROM_ISR)                                                                                    /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_TX_FC_FROM_ISR                    STD_ON
#endif

#if !defined (CANTP_RX_GET_BUFFER_FROM_ISR)                                                                            /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_RX_GET_BUFFER_FROM_ISR            STD_ON
#endif

#if !defined (CANTP_TX_GET_BUFFER_FROM_ISR)                                                                            /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_TX_GET_BUFFER_FROM_ISR            STD_ON
#endif

#if !defined (CANTP_FAULT_TOLERANT_RXBUFFER)                                                                           /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_FAULT_TOLERANT_RXBUFFER           STD_OFF
#endif

#if !defined (CANTP_IGNORE_FC_WITH_RES_STMIN)                                                                          /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_IGNORE_FC_WITH_RES_STMIN          STD_OFF
#endif

#if !defined (CANTP_IGNORE_CF_WITH_WRONG_SN)                                                                           /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_IGNORE_CF_WITH_WRONG_SN           STD_OFF
#endif

#if !defined (CANTP_IGNORE_FC_OVFL_INVALID_FS)                                                                         /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_IGNORE_FC_OVFL_INVALID_FS         STD_OFF
#endif



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* --- Mandatory CanTp APIs ----------------------------------------------------------------------------------------- */
/**********************************************************************************************************************
 * CanTp_Init()
 **********************************************************************************************************************/
/*! \brief         Initializes the CanTp
 *  \details       This function initializes all variables of the CanTp and sets the module state to initialized.
 *  \param[in]     CfgPtr                 Pointer to CanTp configuration data
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is uninitialized.
 *  \pre           CanTp_InitMemory has been called unless CanTp_InitState is initialized by start-up code.
 *  \trace         CREQ-102794
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC, CANTP_INIT_DATA) CfgPtr);

/***********************************************************************************************************************
 *  CanTp_InitMemory()
 **********************************************************************************************************************/
/*! \brief         Initializes all *_INIT_*-variables
 *  \details       Service to initialize module global variables at power up. This function initializes the
 *                 variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is uninitialized.
 *  \trace         CREQ-102794
 **********************************************************************************************************************/
 FUNC(void, CANTP_CODE) CanTp_InitMemory(void);

/***********************************************************************************************************************
 *  CanTp_Shutdown()
 **********************************************************************************************************************/
/*! \brief         Shuts down the CanTp
 *  \details       This function resets the CanTp completely. All open connections are terminated and the module state
 *                 is set to shutdown
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \trace         CREQ-102795
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_Shutdown(void);

/***********************************************************************************************************************
 *  CanTp_Transmit()
 **********************************************************************************************************************/
/*! \brief         Starts transmission of a CanTp message
 *  \details       With this function, the transmission of segmented or unsegmented message is requested.
 *  \param[in]     CanTpTxSduId           Tx N-SDU Id of the connection, which shall be used for transmission
 *  \param[in]     CanTpTxInfoPtr         Pointer to a PduInfo struct. The SduLength member contains the total length
 *                                        of the message to be transmitted and the SduDataPtr member points to metadata
 *                                        if the Tx N-SDU has been configured with it.
 *  \return        E_OK                   Transmission request accepted
 *  \return        E_NOT_OK               Function parameters were invalid or transmission is currently not possible
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   FALSE by default, but can be configured.
 *  \pre           -
 *  \note          The SduDataPtr member of CanTpTxInfoPtr shall not be used for Tx SDUs configured without metadata.
 *  \trace         CREQ-102804
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr);

/***********************************************************************************************************************
 *  CanTp_MainFunction()
 **********************************************************************************************************************/
/*! \fn            void CanTp_MainFunction(void)
 *  \brief         Handles timing tasks and asynchronous operations of all Tx and Rx connections
 *  \details       This function handles scheduling and timeout supervision of active connections.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \trace         DSGN-CanTp23053, DSGN-CanTp23083
 **********************************************************************************************************************/
#if (CANTP_RXTX_MAINFUNCTION_API == STD_ON)
FUNC(void, CANTP_CODE) CanTp_MainFunction(void); /* Only the split functions appear in the SchM header */
#endif


/* --- Optional CanTp APIs ------------------------------------------------------------------------------------------ */
#if (CANTP_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  CanTp_GetVersionInfo()
 **********************************************************************************************************************/
/*! \brief         Returns the version information
 *  \details       CanTp_GetVersionInfo() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]    versioninfo            Pointer to where to store the version information. Parameter must not be NULL.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        This API is only available if CANTP_VERSION_INFO_API = STD_ON
 *  \pre           -
 *  \trace         CREQ-102799
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTP_APPL_DATA) versioninfo);
#endif

#if (CANTP_ENABLE_CHANGE_PARAM == STD_ON)
/***********************************************************************************************************************
 *  CanTp_ChangeParameter()
 **********************************************************************************************************************/
/*! \brief         Requests modification of a flow control parameter
 *  \details       This function is used to request the change of the parameters BS and STmin for a specific Rx N-SDU.
 *  \param[in]     id                     Rx N-SDU Id of the connection, for which the parameter shall be changed.
 *  \param[in]     parameter              Flow Control parameter to be changed (TP_STMIN or TP_BS).
 *  \param[in]     value                  New parameter value.
 *  \return        E_OK                   Change request was accepted, parameter value remains unchanged
 *  \return        E_NOT_OK               Requested parameter was changed to the new value
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This API is only available if CANTP_ENABLE_CHANGE_PARAM = STD_ON
 *  \pre           No reception is active for specified Rx N-SDU.
 *  \trace         DSGN-CanTp23299
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16  value);
#endif

#if (CANTP_ENABLE_READ_PARAM == STD_ON)
/***********************************************************************************************************************
 *  CanTp_ReadParameter()
 **********************************************************************************************************************/
/*! \brief         Reads the value of a flow control parameter
 *  \details       This function is used to read the current value of the parameters BS and STmin for a specific Rx N-SDU.
 *  \param[in]     id                     Rx N-SDU Id of the connection, for which the parameter shall be read.
 *  \param[in]     parameter              Flow Control parameter to be read (TP_STMIN or TP_BS).
 *  \param[out]    value                  Current parameter value.
 *  \return        E_OK                   Read request was successful.
 *  \return        E_NOT_OK               Read request failed because of invalid parameters.
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This API is only available if CANTP_ENABLE_READ_PARAM = STD_ON
 *  \pre           -
 *  \trace         DSGN-CanTp23299
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16* value);
#endif

#if (CANTP_TC == STD_ON)
/***********************************************************************************************************************
 *  CanTp_CancelTransmit()
 **********************************************************************************************************************/
/*! \brief         Requests cancellation of a Tx connection
 *  \details       With this function an active Tx connection can be canceled.
 *  \param[in]     CanTpTxSduId           Tx N-SDU Id of the connection, which shall be canceled
 *  \return        E_OK                   Connection was terminated successfully
 *  \return        E_NOT_OK               Cancellation failed, e.g. because transmission is not in progress or is not segmented
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This API is only available if CANTP_TC = STD_ON
 *  \pre           Transmission is in progress and in a state where it can be canceled
 *  \trace         DSGN-CanTp24679
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmit(PduIdType CanTpTxSduId);
#endif

#if (CANTP_RC == STD_ON)
/***********************************************************************************************************************
 *  CanTp_CancelReceive()
 **********************************************************************************************************************/
/*! \brief         Requests cancellation of an Rx connection
 *  \details       With this function an active Rx connection can be canceled.
 *  \param[in]     CanTpRxSduId           Rx N-SDU Id of the connection, which shall be canceled
 *  \return        E_OK                   Connection was terminated successfully
 *  \return        E_NOT_OK               Cancellation failed, e.g. because reception is not in progress or is not segmented
 *  \context       TASK|ISR2
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        This API is only available if CANTP_RC = STD_ON
 *  \pre           Reception is in progress and in a state where it can be canceled
 *  \trace         DSGN-CanTp24679
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceive(PduIdType CanTpRxSduId);
#endif


/*!
 * \exclusivearea CANTP_EXCLUSIVE_AREA_0
 *                Ensures consistency of the CanTp state variables.
 * \protects      CanTp_RxState, CanTp_TxState, CanTp_RxChannelMap, CanTp_TxChannelMap, CanTp_TxQueue, CanTp_TxSemaphores, CanTp_CalcBS, CanTp_DynFCParameters
 * \usedin        CanTp_RxIndication, CanTp_TxConfirmation, CanTp_Transmit, CanTp_ChangeParameter, CanTp_CancelReceive, CanTp_CancelTransmit, CanTp_StopSeparationTime, CanTp_MainFunctionRx, CanTp_MainFunctionTx
 * \exclude       Modifications of CanTp state from another context.
 * \length        LONG Processing of any event which modifies the CanTp state machine.
 * \endexclusivearea
 */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* CANTP_H */

/**********************************************************************************************************************
 *  END OF FILE: CanTp.h
 *********************************************************************************************************************/
