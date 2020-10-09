/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Types.h                                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2018 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision of Flash Wrapper Component specific types used within the module.*/
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X1x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * V1.0.0:  08-Oct-2015  : Initial Version
 *
 * V1.1.0:  04-Dec-2015  : As a part of F1K 4.00.01 release following changes
 *                          are made:
 *                         1. Added Enumerations - ETag_Fls_FlashReadType,
 *                            ETag_Fls_FcuStatusType.
 *                         2. Added structure - Stag_Fls_FcuDataType,
 *                            STag_Fls_RegistersType, STag_Fls_ECCRegType.
 *                         3. Changed name of STag_Fls_GstVarProperties to
 *                            STag_Fls_GstVarProperties and removed some
 *                            structure elements.
 *                         4. Removed structure element
 *                            ulFlsSlowModeMaxWriteBytes from structure
 *                            STag_Fls_ConfigType.
 *                         5. Fcu_Types.h file inclusion is removed.
 *
 * V1.2.0:  28-Sep-2016  : #ARDAABD-843
 *                         1. Removed support for
 *                            FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V1.2.1:  26-Oct-2016  : #ARDAABD-929
 *                         1. pFlEndImrAddress structure field is changed
 *                            to constant pointer to variable.
 * V2.0.0:  11-Nov-2016  : #ARDAABD-732
 *                         1. added FLS_COMMAND_DMA_WRITE command into
 *                            ETag_Fls_CommandType enum.
 *                         2. added pointer to DmaUnitConfig into Fls_ConfigType
 *                         3. defined structure for Fls_DmaUnitConfig.
 *
 * V2.0.1:  06-Jan-2017  : #ARDAABD-929
 *                         1. storage class of structure fields:
 *                            pTempBufferAddress, pBufferAddress, pDmaUnitConfig
 *                            changed to typedef
 *
 * V2.0.2:  09-Jan-2017  : #ARDAABD-786
 *                         1. Structure's Stag_Fls_FcuDataType member
 *                            Fls_FcuFlashMode changed to volatile
 *
 * V2.0.3:  10-Jan-2017  : #ARDAABD-786
 *                         1. Structure's Stag_Fls_FcuDataType member
 *                            Fls_FcuFlashMode no more volatile
 * V2.0.4:  16-Jan-2017  : #ARDAABD-459 pDmaImrIntCntlReg, pDmaIntCntlReg and
 *                            usDmaImrMask structure elements has been placed
 *                            under FLS_INTERRUPT_MODE == STD_ON compiler switch
 *
 * V2.0.5:  14-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 * V2.0.6:  20-Jul-2017  :  ARDAABD-1139 - STag_Fls_ECCRegType has been removed.
 * V2.0.7:  31-Aug-2017  :  ARDAABD-2151 - Corrected QAC/MISRA Warning.
 * V2.0.8:  25-Sep-2017  :  ARDAABD-2370: corrected variables naming convention.
 * V2.0.9:  20-Jun-2018  :  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-2158):
 *                           a. Removed IMR register and mask value fields
 *                              in the struct declaration.
 *                          2. As per ARDAABD-3853, traceability has been
 *                            improved.
 */
/******************************************************************************/
#ifndef FLS_TYPES_H
#define FLS_TYPES_H

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
/* Included for pre-compile options */
#include "Fls_PBTypes.h"
/* Included for pre-compile options
#include "Fls_Cfg.h"*/
/*******************************************************************************
**                        Version Information                                 **
*******************************************************************************/
/* AUTOSAR release version information */
#define FLS_TYPES_AR_RELEASE_MAJOR_VERSION      FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_TYPES_AR_RELEASE_MINOR_VERSION      FLS_AR_RELEASE_MINOR_VERSION
#define FLS_TYPES_AR_RELEASE_REVISION_VERSION   FLS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLS_TYPES_SW_MAJOR_VERSION              FLS_SW_MAJOR_VERSION
#define FLS_TYPES_SW_MINOR_VERSION              FLS_SW_MINOR_VERSION

/*******************************************************************************
**                      GLOBAL DATA TYPES                                     **
*******************************************************************************/
/* FLS_TYPES_H_001:  FLS_ESDD_UD_226                                          */
/* FLS_TYPES_H_002:  EAAR_PN0034_FR_0052                                      */

/* Enumeration for flash read type */
typedef enum ETag_Fls_FlashReadType
{
  FLS_MISALIGNED_READ = 0,
  FLS_ALIGNED_READ
} Fls_FlashReadType;

/* FLS_TYPES_H_003:  FLS_ESDD_UD_056, FLS_ESDD_UD_093                         */
/* FLS_TYPES_H_004:  EAAR_PN0034_FR_0052                                      */
/* Enumeration for driver commands */
typedef enum ETag_Fls_CommandType
{
  FLS_COMMAND_NONE = 0,
  FLS_COMMAND_ERASE,
  FLS_COMMAND_WRITE,
  FLS_COMMAND_DMA_WRITE,
  FLS_COMMAND_READ,
  FLS_COMMAND_COMPARE,
  FLS_COMMAND_BLANKCHECK,
  FLS_COMMAND_READ_IMM
} Fls_CommandType;

/* FLS_TYPES_H_005:  FLS_ESDD_UD_228                                          */
/* FLS_TYPES_H_006:  EAAR_PN0034_FR_0052                                      */
/* Enumeration for returning FCU status values */
typedef enum ETag_Fls_FcuStatusType
{
  FLS_FCU_OK = 0,
  FLS_FCU_BUSY ,
  FLS_FCU_SUSPENDED ,
  FLS_FCU_ERR_CONFIGURATION ,
  FLS_FCU_ERR_REJECTED  ,
  FLS_FCU_ERR_WRITE ,
  FLS_FCU_ERR_ERASE  ,
  FLS_FCU_ERR_BLANKCHECK ,
  FLS_FCU_ERR_ECC_SED ,
  FLS_FCU_ERR_ECC_DED  ,
  FLS_FCU_ERR_INTERNAL ,
  FLS_FCU_CANCELED
} Fls_FcuStatusType;

/* FLS_TYPES_H_007:  FLS_ESDD_UD_238                                          */
/* FLS_TYPES_H_008:  EAAR_PN0034_FR_0052                                      */
/* Structure contains all Fcu internal data */
typedef struct Stag_Fls_FcuDataType
{
  /* Flash hardware frequency in MHz */
  uint16 usCpuFrequencyMHz;
  /* Data Flash pool size in no. of blocks */
  uint16 usDFPoolSize;
  /* Data Flash size, required for boundary checks */
  uint32 ulFcuDfSize;
  /* ECC base address determined on firmware parameter version */
  uint32 ulFcuBaseAddrECC;
  /* Checksum end address */
  uint32 ulFcuChksumEndAddr;
  /* Checksum value */
  uint32 ulFcuChksumVal;
  /* Current Flash operating mode: P/E or Read */
  uint16 usFcuFlashMode;
} Fls_FcuDataType;

/* FLS_TYPES_H_009:  FLS_ESDD_UD_239                                          */
/* FLS_TYPES_H_010:  EAAR_PN0034_FR_0081, EAAR_PN0034_FR_0052                 */
/* Global Structure to handle the FACI Registers */
typedef struct STag_Fls_RegistersType
{
  uint8  volatile ucReserved1[16];
  /* Flash Access Status Register */
  uint8  volatile ucFASTAT;
  uint8  volatile ucReserved2[31];
  /* Flash Command Start Address Register */
  uint32 volatile ulFSADDR;
  /* Flash Command End Address Register */
  uint32 volatile ulFEADDR;
  uint8  volatile ucReserved3[28];
  /* FCURAM Enable Register */
  uint16 volatile usFCURAME;
  uint8  volatile ucReserved4[42];
  /* Flash Status Register */
  uint32 volatile ulFSTATR;
  /* Flash P/E Entry Register */
  uint16 volatile usFENTRYR;
  uint8  volatile ucReserved5[78];
  /* DF Blank Check Status Register */
  uint8  volatile ucFBCSTAT;
  uint8  volatile ucReserved6[3];
  /* DF Programming Start Address Register */
  uint32 volatile ulFPSADDR;
  uint8  volatile ucReserved7[8];
  /* Flash Sequencer Processing Clock Notify Register */
  uint16 volatile usFPCKAR;
}Fls_FACIRegType;

/* FLS_TYPES_H_020:  FLS_ESDD_UD_049                                          */
#if (FLS_SET_MODE_API == STD_ON)
/*******************************************************************************
** Structure for DMA channel configuration                                   **
*******************************************************************************/
typedef struct STag_Fls_DmaUnitConfig
{
  #if (FLS_INTERRUPT_MODE == STD_ON)
  P2VAR(volatile uint16, AUTOMATIC, FLS_CONFIG_DATA)pDmaIntCntlReg;
  #endif /* (FLS_INTERRUPT_MODE == STD_ON) */
  /* DTFR register value */
  uint16 usDmaDtfrRegValue;
  /* Address for DMA control registers index */
  uint8 ucDmaRegIndex;
} Fls_DmaUnitConfig;
#endif /* FLS_SET_MODE_API == STD_ON */

/* FLS_TYPES_H_013:  FLS_ESDD_UD_044                                          */
/* FLS_TYPES_H_014:  FLS109, FLS110, FLS262, FLS263, FLS352, FLS353,FLS355    */
/* FLS_TYPES_H_015:  SWS_Fls_00368, SWS_Fls_00109, SWS_Fls_00110              */
/* FLS_TYPES_H_016:  SWS_Fls_00262, SWS_Fls_00263, SWS_Fls_00353              */
/* FLS_TYPES_H_017:  SWS_Fls_00352, SWS_Fls_00355                             */
/* FLS_TYPES_H_018:  AR_PN0072_NR_0003                                        */
/* Structure for Fls Init Configuration */
/* Overall Module Configuration Data Structure */
typedef struct STag_Fls_ConfigType
{
  /* Database start value - 0x0EDF0400 */
  uint32 ulStartOfDbToc;
  /* Pointer to job end callback notification */
  P2FUNC (void, FLS_APPL_CODE, pJobEndNotificationPointer)(void);
  /* Pointer to job error callback notification */
  P2FUNC (void, FLS_APPL_CODE, pJobErrorNotificationPointer)(void);
  /* Pointer to ECC SED callback notification */
  P2FUNC (void, FLS_APPL_CODE, pEccSEDNotificationPointer)(uint32);
  /* Pointer to ECC DED callback notification */
  P2FUNC (void, FLS_APPL_CODE, pEccDEDNotificationPointer)(uint32);
  /* Maximum number of Read bytes in Normal Mode */
  uint32 ulFlsSlowModeMaxReadBytes;
  /* Maximum number of Read bytes in Fast Mode */
  uint32 ulFlsFastModeMaxReadBytes;
  /* Default Mode value */
  MemIf_ModeType ddDefaultMode;
  #if (FLS_SET_MODE_API == STD_ON)
  /* Pointer to DMA  data */
  P2CONST(Fls_DmaUnitConfig, TYPEDEF, FLS_CONFIG_DATA) pDmaUnitConfig;
  #endif /* FLS_SET_MODE_API == STD_ON */
} Fls_ConfigType;

/* FLS_TYPES_H_019:  FLS_ESDD_UD_048                                          */
typedef struct STag_Fls_GstVarProperties
{
  /* Variable to store the source address */
  P2CONST(uint8, TYPEDEF, FLS_INIT_DATA) pBufferAddress;
  /* Variable to store the source address */
  P2CONST(uint8, TYPEDEF, FLS_INIT_DATA) pTempBufferAddress;
  /* Variable to store the target address */
  uint32 ulSrcDestAddress;
  /* Variable to store the read address */
  uint32 ulReadAddress;
  /* Variable to hold the erase/write start address */
  uint32 ulJobStartAddress;
  /* Variable to hold the erase/write end address */
  uint32 ulJobEndAddress;
  /* Variable to hold the length */
  uint32 ulCurrentLength;
  /* Variable to store the requested number of bytes to be processed */
  uint32 ulRequestedLength;
  /* Variable to hold offset by masking the source address with page size */
  uint8 ucOffset;
  /* Variable to store the Flash read type */
  Fls_FlashReadType enReadType;
  /* Variable to store the requested commands */
  Fls_CommandType enCommand;
  /* Variable to hold the state of FLS software component */
  VAR(Fls_FcuStatusType, FLS_INIT_DATA) enDFStatus;

} Fls_GstVarProperties;

#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)
/* FLS_TYPES_H_021:  FLS_ESDD_UD_241                                          */
/*
 type for CheckHWConsistency API parameter
*/
typedef enum ETag_Fls_HWConsistencyModeType
{
  FLS_STATIC = 0,
  FLS_DYNAMIC
}Fls_HWConsistencyModeType;
#endif /* (FLSTST_RAM_MIRROR == FLS_MIRROR_ENABLE) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* FLS_TYPES_H */

/*******************************************************************************
**                          End Of File                                       **
*******************************************************************************/
