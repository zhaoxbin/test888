/* Kernbauer Version: 1.16 Konfiguration: DrvTransCan Erzeugungsgangnummer: 213 */


/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 |  FILE DESCRIPTION
 |  -------------------------------------------------------------------------------------------------------------------
 |         File:  CanTrcv_30_Tja1040.h
 |      Project:  MICROSAR
 |       Module:  CAN Transceiver driver
 |    Generator:  DaVinci Configurator
 |  Description:  Header of the MICROSAR CAN Transceiver Driver.
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Senol Cendere                 Ces           Vector Informatik GmbH
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Jan Hammer                    Jan           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2009-02-09  Tvi     -             First Implementation
 *  1.01.00   2009-09-11  Tvi     -             (no changes here, just updated HL code)
 *  1.02.00   2010-03-29  Tvi     -             (no changes here, just updated HL code)
 *  1.03.00   2011-02-18  Tvi     ESCAN00047646 Rename filenames to match BSW00347
 *  1.04.00   2011-04-27  Tvi     -             (update to newest template in order to update HL code)
 *  2.00.00   2011-08-31  Seu     -             (update to newest template in order to update HL code)
 *  2.01.00   2012-01-16  Seu     ESCAN00055237 [Tja1042 only] WakeupByBus over CanTrcv does not work due to hardware limitation
 *  2.01.01   2012-07-10  Tvi     -             (no changes here, just updated HL code)
 *  3.00.00   2012-07-26  Tvi     ESCAN00060456 Add support for ASR4.0.3
 *                                ESCAN00060110 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  3.00.01   2012-10-30  Tvi     -             (no changes here, just updated HL code)
 *  3.01.00   2013-04-25  Seu     -             (no changes here, just updated HL code)
 *  3.02.00   2014-02-04  Tvi     -             (no changes here, just updated HL code)
 *  4.00.00   2014-09-25  Seu     ESCAN00078591 AR4-698: Post-Build Selectable (Identity Manager)
 *  4.00.01   2015-07-29  Seu     -             (no changes here, just updated HL code)
 *  4.01.00   2015-12-11  Seu     -             (no changes here, just updated HL code)
 *  4.02.00   2017-05-22  Seu     ESCAN00095260 Adapt to SafeBSW
 *  4.03.00   2018-08-23  Jan     STORYC-6322   MISRA-C:2012 Compliance
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Jan Hammer                    Jan           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-02-25  Fn      -             Intitial revision of the core implementation
 *  01.00.01  2008-04-17  Fn      -             Update of the include file names
 *  01.01.00  2008-06-26  Ou      ESCAN00027616 Various compile errors, problems with Organi
 *  01.02.00  2008-09-12  Ou      ESCAN00029980 Compiler failure due to wrong definition of SW version
 *  01.03.00  2008-10-07  Ou      ESCAN00028298 Several warnings due to unreferenced local variables
 *                        Ou      ESCAN00029572 DrvTrans__coreCanxAsr raise DET error if CanTrcv_SetOpMode is called with invalid TrcvWakeupMode
 *                        Ou      ESCAN00030536 Compile error at extended version check
 *  01.04.00  2008-12-11  Ou      ESCAN00031771 Adjust wakeup by bus handling for platforms which cannot be woken up with a CAN frame
 *  01.05.00  2009-02-19  Tvi     ESCAN00033258 GetBusWuReason may return an invalid value
 *  01.06.00  2009-02-26  Tvi     ESCAN00033383 Don't throw DET error in case the same mode is requested again
 *                        Tvi     ESCAN00033398 Compiler warnings when using different transceiver types within the same stack
 *                        Tvi     ESCAN00033413 Possible out of bounds access in SetOpMode if DET is enabled
 *  02.00.00  2009-06-29  Fn      ESCAN00035913 CAN Transceiver channel does not wake up
 *  02.00.01  2009-10-15  Tvi     ESCAN00038495 Compile error: unknown type definitions in dio.h
 *  02.01.00  2009-11-04  Tvi     ESCAN00036841 OP_MODE_SLEEP should be independent of GENERAL_WAKE_UP_SUPPORT
 *                        Tvi     ESCAN00038945 Use different DioPins tokens for GetOpMode and CHECK_WA
 *                        Tvi     ESCAN00038946 Rename filenames to match BSW00347
 *                        Tvi     ESCAN00038947 CanTrcv087 has to be implemented the correct way
 *                        Tvi     ESCAN00039039 Add support for timers
 *                        Tvi     ESCAN00039041 Allow transition to OP_MODE_NORMAL even if it is the current OpMode
 *                        Tvi     ESCAN00039043 Implement an initialization via OP_MODE_NORMAL
 *                        Tvi     ESCAN00039194 Disable IcuNotification when entering Normal mode in Init and SetOpMode
 *  02.02.00  2010-05-04  Tvi     ESCAN00040088 Compiler Warning: unused parameter 'TrcvWakeupMode'
 *  02.20.00  2010-07-01  Tvi     ESCAN00046512 Add support for partial network transceivers
 *            2010-11-29  Tvi     ESCAN00046781 Support Multiple Identity Configuration
 *                                ESCAN00045601 "Channel Used" parameter not well implemented
 *                                ESCAN00046813 Adapt AUTOSAR version check
 *                                ESCAN00047668 Critical areas should be Trcv specific
 *  02.20.01  2011-02-08  Tvi     ESCAN00048498 Wrong DEM Events used
 *  02.20.02  2011-03-11  Tvi     ESCAN00049830 Remove ASR Version check for SPI / DIO
 *                        Tvi     ESCAN00049831 [PN only] Store wakeup event and report them if Trcv is in Standby mode
 *  03.00.00  2011-05-05  Tvi     ESCAN00051930 Add support for ASR3.2.1
 *                                ESCAN00051564 Remove the AUTOSAR Release Version Check
 *  03.01.00  2011-11-22  Tvi     ESCAN00054349 AR3-1738: Add support for asynchronous transceiver driver
 *                                ESCAN00053272 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053265 AR3-2069: Remove non-SchM code for critical section handling
 *  03.01.01  2012-02-12  Tvi     ESCAN00057892 [PN only] CanTrcv does not wakeup when Synchronous SPI is being used
 *                        Tvi     ESCAN00056788 Compiler error/warning: DRVTRANS__CORECANXASR_RELEASE_VERSION' redefined
 *  04.00.00  2012-05-21  Tvi     ESCAN00058641 AR4-95: Provide CanTrcv according ASR 4, Asynchronous Transceiver Mode Changes
 *                                ESCAN00059656 Add support for SetPNActivationState according to ASR4
 *                                ESCAN00060455 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  04.00.01  2012-09-27  Tvi     ESCAN00061779 [CFG5/ASR4 only]: Compiler error about unkown struct member instanceID
 *  04.01.00  2012-10-08  Tvi     ESCAN00062121 Report DEM if PN is not available
 *                        Tvi     ESCAN00066283 AR4-352: Support partial networking 
 *  04.02.00  2013-11-20  Tvi     ESCAN00071370 AR4-569: [CanTrcv]  Incompatible  argument  in call to EcuM_SetWakeupEvent() 
 *  04.03.00  2014-01-10  Tvi     ESCAN00073861 AR4-345: Implement PF4_PostBuildSelectable
 *  05.00.00  2014-09-24  Seu     ESCAN00076622 AR4-698: Post-Build Selectable (Identity Manager)
 *  05.00.01  2014-11-13  Seu     -             MISRA deviation comment for rule 6080 added (APIs: *_ClearTrcvWufFlag() and *_CheckWakeFlag())
 *  05.01.00  2015-05-04  Seu     ESCAN00077814 Support for CAN Transceiver on System-Basis Chips (SBCs)
 *            2015-07-23  Seu     ESCAN00084154 Only since R13: Compiler error: C2059: syntax error : '{'
 *            2015-07-23  Seu     ESCAN00083583 Adapt in order to fix ESCAN00083361 / ESCAN00083362
 *            2015-07-23  Seu     ESCAN00083395 Compiler warning: parameter is never used
 *  05.01.01  2015-09-24  Seu     ESCAN00085451 Support usage of Partial Networking for SBCs.
 *  05.01.02  2015-10-06  Seu     ESCAN00085678 Initialize requestState in case of INTERFACE_SBC and PN is used
 *  05.02.00  2015-02-04  Seu     ESCAN00080310 FEAT-427: SafeBSW Step I
 *            2015-10-05  Seu     ESCAN00081795 FEAT-1275: SafeBSW Step 2
 *            2015-10-05  Seu     ESCAN00085154 FEAT-1527: SafeBSW Step 3
 *  05.03.00  2016-01-16  Seu     ESCAN00087580 SafeBSW - Silent Analysis
 *            2016-03-09  Seu     ESCAN00088810 Add Postbuild Loadable Support for CanTrcvDrv
 *  05.04.00  2016-04-05  Seu     ESCAN00087813 FEAT-1688: SafeBSW Step 4
 *            2016-05-19  Seu     ESCAN00090097 Compiler error: Syntax Error caused by undefined compiler class
 *  05.04.01  2016-08-02  Seu     ESCAN00091270 MISRA deviation: MISRA-C:2004 Rule 8.8
 *            2016-08-17  Seu     ESCAN00091505 Improve code coverage and doxygen comments
 *            2016-10-17  Seu     ESCAN00091616 Compiler error: identifier index not declared
 *  05.05.00  2016-11-23  Seu     ESCAN00092817 Add support for asynchronous SPI without polling support
 *            2016-11-29  Seu     ESCAN00093075 [Only: Tja1145 / E52013] In case of startup of ECU SysErr-wakeup is reported instead of PowerOn-wakeup
 *            2016-12-06  Seu     ESCAN00093177 Omit interrupted transition: STANDBY -> NORMAL (pending) -> SLEEP  [only async SPI]
 *  05.06.00  2017-04-05  Seu     ESCAN00094603 Add support for requirements: CanTrcv_00230, CanTrcv_00190, CanTrcv_00191
 *            2017-04-05  Seu     ESCAN00094658 Improve doxygen comments
 *  05.06.01  2017-05-30  Seu     ESCAN00095350 Add: SafeBSW support for DIO-CanTrcv, flexibility for SPI-CanTrcv
 *  05.07.00  2018-08-21  Jan     STORYC-4868   MISRA-C:2012 Compliance
 * *******************************************************************************************************************/
#if !defined (CANTRCV_30_TJA1040_API_H)
# define CANTRCV_30_TJA1040_API_H

/* PRQA S 0850 EOF */ /* MD_MSR_MacroArgumentEmpty */
/* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */

# define V_CANTRCV_30_TJA1040_HEADER

/* ********************************************************************************************************************
 * INCLUDES
 * *******************************************************************************************************************/
# include "CanTrcv_30_Tja1040_Cfg.h" /* SREQ00010148,SREQ00007523 */

# include "SchM_CanTrcv_30_Tja1040.h"

/* ********************************************************************************************************************
 * Module version
 * *******************************************************************************************************************/

# define CANTRCV_30_TJA1040_AR_RELEASE_MAJOR_VERSION      4u
# define CANTRCV_30_TJA1040_AR_RELEASE_MINOR_VERSION      0u
# define CANTRCV_30_TJA1040_AR_RELEASE_REVISION_VERSION   3u
# define CANTRCV_30_TJA1040_AUTOSARVERSION_4X             0x403u


/* ##V_CFG_MANAGEMENT ##CQProject : DrvTrans_Tja1040CandioAsr CQComponent : Implementation */
# define DRVTRANS_TJA1040CANDIOASR_VERSION                 0x0403u
# define DRVTRANS_TJA1040CANDIOASR_RELEASE_VERSION         0x00u

#if defined(CANTRCV_30_TJA1040_INCLUDE_INTERNAL) /* COV_CANTRCV_HL_TJA1040_VARCOV_AVOID_COREVER_REDEF */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvTrans__coreCanxAsr CQComponent : Implementation */
# define DRVTRANS__CORECANXASR_VERSION                         0x0507u
# define DRVTRANS__CORECANXASR_RELEASE_VERSION                 0x00u
#endif

#  define CANTRCV_30_TJA1040_SW_MAJOR_VERSION      ((uint8)((DRVTRANS_TJA1040CANDIOASR_VERSION & 0xFF00u) >> 8))
#  define CANTRCV_30_TJA1040_SW_MINOR_VERSION               (DRVTRANS_TJA1040CANDIOASR_VERSION & 0x00FFu)
#  define CANTRCV_30_TJA1040_SW_PATCH_VERSION                DRVTRANS_TJA1040CANDIOASR_RELEASE_VERSION




#define CANTRCV_30_TJA1040_SUPPORTS_MODE_STANDBY




/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 * *******************************************************************************************************************/ 
# define CANTRCV_30_TJA1040_VENDOR_ID                      30u
# define CANTRCV_30_TJA1040_MODULE_ID                      70u

/* ! API IDs for Error Reporting */
# define CANTRCV_30_TJA1040_INIT_ID                        0x00u
# define CANTRCV_30_TJA1040_SETOPMODE_ID                   0x01u
# define CANTRCV_30_TJA1040_GETOPMODE_ID                   0x02u
# define CANTRCV_30_TJA1040_GETBUSWUREASON_ID              0x03u
# define CANTRCV_30_TJA1040_GETVERSIONINFO_ID              0x04u
# define CANTRCV_30_TJA1040_SETWAKEUPMODE_ID               0x05u
# define CANTRCV_30_TJA1040_MAINFUNCTION_ID                0x06u
# define CANTRCV_30_TJA1040_CHECKWAKEUP_ID                 0x07u 
# define CANTRCV_30_TJA1040_MAINFUNCTIONDIAGNOSTICS        0x08u
# define CANTRCV_30_TJA1040_GETTRCVSYSTEMDATA_ID           0x09u
# define CANTRCV_30_TJA1040_CLEARTRCVWUFFLAG_ID            0x0Au
# define CANTRCV_30_TJA1040_READTRCVTIMEOUTFLAG_ID         0x0Bu
# define CANTRCV_30_TJA1040_CLEARTRCVTIMEOUTFLAG_ID        0x0Cu
# define CANTRCV_30_TJA1040_READTRCVSILENCEFLAG_ID         0x0Du
# define CANTRCV_30_TJA1040_CHECKWAKEFLAG_ID               0x0Eu
# define CANTRCV_30_TJA1040_SETPNACTIVATIONSTATE_ID        0x0Fu
# define CANTRCV_30_TJA1040_SPIINDICATION_ID               0x10u


# define CANTRCV_30_TJA1040_OP_MODE_NORMAL                 CANTRCV_TRCVMODE_NORMAL
# define CANTRCV_30_TJA1040_OP_MODE_STANDBY                CANTRCV_TRCVMODE_STANDBY 
# define CANTRCV_30_TJA1040_OP_MODE_SLEEP                  CANTRCV_TRCVMODE_SLEEP

# define CANTRCV_30_TJA1040_WU_ENABLE                      CANTRCV_WUMODE_ENABLE
# define CANTRCV_30_TJA1040_WU_DISABLE                     CANTRCV_WUMODE_DISABLE
# define CANTRCV_30_TJA1040_WU_CLEAR                       CANTRCV_WUMODE_CLEAR

# define CANTRCV_30_TJA1040_WU_ERROR                       CANTRCV_WU_ERROR
# define CANTRCV_30_TJA1040_WU_NOT_SUPPORTED               CANTRCV_WU_NOT_SUPPORTED
# define CANTRCV_30_TJA1040_WU_BY_BUS                      CANTRCV_WU_BY_BUS
# define CANTRCV_30_TJA1040_WU_INTERNALLY                  CANTRCV_WU_INTERNALLY
# define CANTRCV_30_TJA1040_WU_RESET                       CANTRCV_WU_RESET
# define CANTRCV_30_TJA1040_WU_POWER_ON                    CANTRCV_WU_POWER_ON
# define CANTRCV_30_TJA1040_WU_BY_PIN                      CANTRCV_WU_BY_PIN
# define CANTRCV_30_TJA1040_WU_BY_SYSERR                   CANTRCV_WU_BY_SYSERR

# define CANTRCV_30_TJA1040_E_NO_ERROR                     0x00u
# define CANTRCV_30_TJA1040_E_INVALID_CAN_NETWORK          0x01u
/* ! SREQ00010156: Keep the invalid CAN Network switch for compatibility reason. */
# define CANTRCV_30_TJA1040_E_INVALID_TRANSCEIVER          CANTRCV_30_TJA1040_E_INVALID_CAN_NETWORK
# define CANTRCV_30_TJA1040_E_PARAM_POINTER                0x02u
# define CANTRCV_30_TJA1040_E_UNINIT                       0x11u
# define CANTRCV_30_TJA1040_E_TRCV_NOT_STANDBY             0x21u
# define CANTRCV_30_TJA1040_E_TRCV_NOT_NORMAL              0x22u
# define CANTRCV_30_TJA1040_E_PARAM_TRCV_WAKEUP_MODE       0x23u
# define CANTRCV_30_TJA1040_E_PARAM_TRCV_OP_MODE           0x24u
# define CANTRCV_30_TJA1040_E_BAUDRATE_NOT_SUPPORTED       0x25u
# define CANTRCV_30_TJA1040_E_CLR_TRCV_WUF_NOT_CALLED      0x30u
# define CANTRCV_30_TJA1040_E_NO_TRCV_CONTROL              0x40u /* SREQ00010156: Actual ID is unspecified in SWS! */


# define CANTRCV_30_TJA1040_WAKEUP_NOT_SUPPORTED          0u
# define CANTRCV_30_TJA1040_WAKEUP_BY_POLLING             1u
# define CANTRCV_30_TJA1040_WAKEUP_BY_ISR                 2u
/* ! Compatibility defines... */
# define CANTRCV_30_TJA1040_WAKEUP_NONE                   CANTRCV_30_TJA1040_WAKEUP_NOT_SUPPORTED
# define CANTRCV_30_TJA1040_WAKEUP_POLLING                CANTRCV_30_TJA1040_WAKEUP_BY_POLLING
# define CANTRCV_30_TJA1040_WAKEUP_ISR                    CANTRCV_30_TJA1040_WAKEUP_BY_ISR

# define CanTrcv_30_Tja1040_TrcvModeType                  CanTrcv_TrcvModeType
# define CanTrcv_30_Tja1040_TrcvWakeupModeType            CanTrcv_TrcvWakeupModeType
# define CanTrcv_30_Tja1040_TrcvWakeupReasonType          CanTrcv_TrcvWakeupReasonType


/* ! Timer configuration */


# define CANTRCV_30_TJA1040_USE_TIMERS                    STD_OFF

/* ! Predefined timer indexes (0x01 - 0x0f)                                   */
# define kCanTrcv_30_Tja1040_LoopInit                          0x01






/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 * *******************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 * *******************************************************************************************************************/
/* SREQ00007522 */
/* ! Defines the state of any requested FLAG-action: *SET or *CLEARED. */
typedef enum
{
  CANTRCV_30_TJA1040_FLAG_SET,
  CANTRCV_30_TJA1040_FLAG_CLEARED
}
CanTrcv_30_Tja1040_TrcvFlagStateType;

/* ! Defines the state of PN (= Partial Networking): *ENABLED or *DISABLED. */
typedef enum
{
  CANTRCV_30_TJA1040_PN_ENABLED,
  CANTRCV_30_TJA1040_PN_DISABLED
} CanTrcv_30_Tja1040_PNActivationType;




/* ! The following type includes CAN transceiver channel specific settings. */
typedef struct
{
  /* ---- Common attributes ---- */

  /* ! Last detected wakeup reason */
  CanTrcv_30_Tja1040_TrcvWakeupReasonType wakeUpReason;

  /* ! Specifies whether or not to report wakeups */
  CanTrcv_30_Tja1040_TrcvWakeupModeType wakeUpReport;






  /* ! HW specific attributes */

} CanTrcv_30_Tja1040_Prob_Type;

/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 * *******************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 * *******************************************************************************************************************/
/* for callback function prototypes see CanTrcv_Cbk.h */
# define CANTRCV_30_TJA1040_START_SEC_CODE
# include "MemMap.h"


/************************************************************************************************************
 | NAME:  CanTrcv_30_Tja1040_Init()
 ***********************************************************************************************************/
/*! \brief         Initializes the CAN transceiver module.
 *  \details       Initializes all active channels of the CAN transceiver driver which are configured in the configuration tool.
 *                 This function has the service id 0x00.
 *  \param[in]     ConfigPtr - Pointer to the CanTrcv_30_Tja1040_Config structure.
 *                 If multiple configurations are available, the active configuration can be selected by using the related CanTrcv_30_Tja1040_Config_<IdentityName> structure.
 *  \pre           The function CanTrcv_30_Tja1040_InitMemory must be called before the function CanTrcv_30_Tja1040_Init can be called.
 *                 This function must be called before any other service functionality of the transceiver driver
 *                 The SPI/DIO driver must be initialized
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
***********************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_Init( P2CONST(CanTrcv_30_Tja1040_ConfigType, AUTOMATIC, CANTRCV_30_TJA1040_CONST) ConfigPtr );


/***********************************************************************************************************************
 | NAME:  CanTrcv_30_Tja1040_InitMemory
 **********************************************************************************************************************/
/*! \brief         Initializes the memory of the CAN transceiver module.
 *  \details       -
 *  \param[in]     -
 *  \pre           -
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \config        -
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_InitMemory(void);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_SetOpMode
 **********************************************************************************************************************/
/*! \brief       Changes the transceiver operating mode to the requested mode.
 *  \details     This function has the service id 0x01.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   OpMode: Operating mode which shall be set.
 *  \return      E_OK: Change of transceiver operating mode was successful.
 *  \return      E_NOT_OK: Change of transceiver operating mode failed or passed parameter(s) is/are invalid.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE (if CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_SetOpMode(uint8 CanTrcvIndex, CanTrcv_TrcvModeType OpMode);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_GetOpMode
 **********************************************************************************************************************/
/*! \brief       Returns the current transceiver operating mode.
 *  \details     DIO transceiver: The mode is determined from status of PINs of the transceiver hardware.
 *               SPI transceiver: The mode is read from state variable. No access to transceiver hardware is performed.
 *               This function has the service id 0x02.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  OpMode: Pointer to buffer where the current operating mode is stored.
 *  \return      E_OK: Determination of current transceiver operating mode was successful.
 *  \return      E_NOT_OK: Determination of transceiver operating mode failed or passed parameter(s) is/are invalid.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_GetOpMode(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_30_TJA1040_APPL_VAR) OpMode);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_GetBusWuReason
 **********************************************************************************************************************/
/*! \brief       Returns the bus wake-up reason.
 *  \details     The wake-up reason is read from state variable. No access to transceiver hardware is performed.
 *               This function has the service id 0x03.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[out]  Reason: Pointer to buffer where the bus wake-up reason is stored.
 *  \return      E_OK: Determination of wake-up reason was successfull.
 *  \return      E_NOT_OK: Determination of wake-up reason failed or passed parameter(s) is/are invalid.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_TJA1040_APPL_VAR) Reason);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_SetWakeupMode
 **********************************************************************************************************************/
/*! \brief       Changes the wake-up mode to the requested mode.
 *  \details     For more information about possible wake-up modes please see the description of type <CanTrcv_TrcvWakeupModeType>.
 *               This function has the service id 0x05.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \param[in]   TrcvWakeupMode: Requested wake-up mode for the transceiver channel (CanTrcvIndex).
 *  \return      E_OK: Change of wake-up mode was successful.
 *  \return      E_NOT_OK: Change of wake-up mode has failed or passed parameter(s) is/are invalid.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_SetWakeupMode(uint8 CanTrcvIndex, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);


/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_CheckWakeup
 **********************************************************************************************************************/
/*! \brief       Checks if a wake-up event was detected.
 *  \details     This function has the service id 0x07.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \return      E_OK: Wake-up was detected / the request to check for wake-up was accepted (only asynchronous SPI-interface).
 *  \return      E_NOT_OK: No wake-up was detected / the request to check for wake-up was rejected (only asynchronous SPI-interface).
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE (if CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      -
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_CheckWakeup(uint8 CanTrcvIndex);


#if (CANTRCV_30_TJA1040_GET_VERSION_INFO == STD_ON)
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief       Returns the version info of the CAN transceiver module.
 *  \details     The versions are stored into the structure referenced by parameter: VersionInfo.
 *               This function has the service id 0x04.
 *  \param[out]  VersionInfo: Pointer to structure for storing of version info.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1040_GET_VERSION_INFO == STD_ON
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_30_TJA1040_APPL_VAR) VersionInfo);
#endif /* (CANTRCV_30_TJA1040_GET_VERSION_INFO == STD_ON) */

/* SREQ00007670 */



/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1040_MainFunction
 **********************************************************************************************************************/
/*! \brief       Service to scan all buses for wake up events and perform these event.
 *  \details     This function has the service id 0x06.
 *  \param[in]   -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE (if CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS == STD_ON), FALSE (if CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS == STD_OFF)
 *  \config      -
 **********************************************************************************************************************/
/* FUNC(void, CANTRCV_30_TJA1040_CODE) CanTrcv_30_Tja1040_MainFunction(void); */ /* ESCAN00091270 */



# define CANTRCV_30_TJA1040_STOP_SEC_CODE
# include "MemMap.h"

/*! 
* \exclusivearea CANTRCV_TJA1040_EXCLUSIVE_AREA_0
* Ensures consistent handling of CanTrcv-hardware via the DIO-interface.
* \protects Atomic / consistent reading of DIO-pins and setting of them.
* \usedin CanTrcv_30_Tja1040_Init(), CanTrcv_30_Tja1040_SetOpMode(), CanTrcv_30_Tja1040_GetOpMode(), CanTrcv_30_Tja1040_CheckWakeup() and CanTrcv_30_Tja1040_MainFunction().
* \exclude call of: CanTrcv-driver APIs: CanTrcv_30_Tja1040_Init(), CanTrcv_30_Tja1040_SetOpMode(), CanTrcv_30_Tja1040_GetOpMode(), CanTrcv_30_Tja1040_CheckWakeup() and CanTrcv_30_Tja1040_MainFunction() 
*                   AND in fact the instructions within the exclusive area must be executed atomic without any interruption / delay in between.
* \length SHORT Call to DIO module.
* \endexclusivearea
*/



#endif /* CANTRCV_30_TJA1040_API_H */

/* ********************************************************************************************************************
 *  END OF FILE
 * *******************************************************************************************************************/
