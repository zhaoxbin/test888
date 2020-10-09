/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  MemIf.h
 *        \brief  Memory Interface header file
 *
 *      \details  The Memory Abstraction Interface provides uniform access to services of underlying
 *                Memory Hardware abstraction (MemHwA) modules, i.e. EEPROM Abstraction (EA) and
 *                Flash EEPROM Emulation (FEE). The appropriate MemHwA module is selected by a device index.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  Roland Suess                  Rsu           Vector Informatik GmbH
 *  Manfred Duschinger            Du            Vector Informatik GmbH
 *  Michael Goss                  Gmi           Vector Informatik Gmbh
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id      Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.02.00  -           Tsd     -              first production release
 *  02.00.00  2008-04-09  Tsd     -              update for AUTOSAR Release 3.0
 *  02.00.01  2008-05-13  Tsd     -              Introduced SIP-Check
 *  02.01.00  2008-09-15  Rsu     -              Supporting 2 Fee instances in NvM
 *  02.01.01  2009-10-20  Tsd     ESCAN00037330  Corrected Fee/Ea calls in macro API in MemIf_Cfg.h
 *  02.01.02  2011-03-16  Du      ESCAN00042276  Only changes in MemIf_Types.h, but SW Patch Version is incremented
 *  02.01.03  2011-10-12  Du      ESCAN00053322  Added MISRA justifications to source code
 *  02.01.04  2011-12-08  Du      ESCAN00055428  Added include of Std_Types.h in MemIf_Types.h
 *  03.00.00  2012-07-17  Du      ESCAN00058817  AR 4.0.3 compliant component
 *  03.00.01  2013-02-19  Du      -              MISRA justifications added
 *  03.00.02  2013-10-30  Du      -              Copyright year and file names were corrected
 *  03.00.03  2014-11-21  Gmi     -              MISRA justifications added
 *  03.01.00  2015-04-21  Gmi     ESCAN00080287  FEAT-427: SafeBSW step 1
 *                                ESCAN00081775  FEAT-1275: SafeBSW step 2
 *                                ESCAN00081722  Extended version check was removed
 *  03.02.00  2015-09-18  Gmi     ESCAN00085095  FEAT-1372: Updated Cfg Version Check 
 *  03.03.00  2016-02-08  Gmi     -              Update of generator version
 *  03.03.01  2016-12-19  Gmi     FEAT-1824      Update of generator version
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#if !defined MEMIF_H
# define MEMIF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "MemIf_Types.h"
# include "MemIf_Cfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define MEMIF_MODULE_ID                    (22u)
# define MEMIF_VENDOR_ID                    (30u)
# define MEMIF_INSTANCE_ID                  (0u)

# define MEMIF_AR_RELEASE_MAJOR_VERSION     (4u)
# define MEMIF_AR_RELEASE_MINOR_VERSION     (0u)
# define MEMIF_AR_RELEASE_REVISION_VERSION  (3u)

# define MEMIF_SW_MAJOR_VERSION             (3u)
# define MEMIF_SW_MINOR_VERSION             (3u)
# define MEMIF_SW_PATCH_VERSION             (1u)

/**** API Defines ************************************************************************************/

# define MEMIF_BROADCAST_ID                 (0xFFu)

/**** MemIf Service Identification ************************************************************************************/
# define MEMIF_SID_SETMODE                  (0x01U)
# define MEMIF_SID_READ                     (0x02U)
# define MEMIF_SID_WRITE                    (0x03U)
# define MEMIF_SID_CANCEL                   (0x04U)
# define MEMIF_SID_GET_STATUS               (0x05U)
# define MEMIF_SID_GET_JOB_RESULT           (0x06U)
# define MEMIF_SID_INVALIDATE               (0x07U)
# define MEMIF_SID_VERSION_INFO             (0x08u)
# define MEMIF_SID_ERASE                    (0x09u)


/**********************************************************************************************************************
 *  CHECK NUMBER OF DEVICES
 *********************************************************************************************************************/

# if ( MEMIF_NUMBER_OF_DEVICES == 0 )
#  error "No Memory Hardware Abstraction Devices (EA/FEE) defined!"
# endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define MEMIF_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 *  MemIf_Read()
 *********************************************************************************************************************/
/*!
 * \brief      Reads a data block from the EA/FEE
 * \details    Reads Length bytes of block BlockNumber of device DeviceIndex at offset BlockOffset into buffer DataBufferPtr
 * \param[in]  DeviceIndex
 * \param[in]  BlockNumber
 * \param[in]  BlockOffset - read offset within block
 * \param[in]  DataBufferPtr
 * \param[in]  Length - states the length of a read job
 * \return     Returns if requested job has been accepted by the underlying MemHwA device.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-796
 * \trace SPEC-23075
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(uint8 DeviceIndex , uint16 Blockid,uint16 BlockNumber, uint16 BlockOffset, MemIf_DataPtr_pu8 DataBufferPtr, uint16 Length);


/**********************************************************************************************************************
*  MemIf_Write()
*********************************************************************************************************************/
/*!
 * \brief      Writes a data block to the EA/FEE
 * \details    Writes the contents of DataBufferPtr to the block BlockNumber of device DeviceIndex
 * \param[in]  DeviceIndex
 * \param[in]  BlockNumber
 * \param[in]  DataBufferPtr
 * \return     Returns if requested job has been accepted by the underlying MemHwA device.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-797
 * \trace SPEC-23064
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(uint8 DeviceIndex, uint16 Blockid,uint16 BlockNumber, MemIf_DataPtr_pu8 DataBufferPtr);


/**********************************************************************************************************************
 *  MemIf_InvalidateBlock()
 *********************************************************************************************************************/
/*!
 * \brief      Invalidates the data block BlockNumber of device DeviceIndex
 * \details    Invalidates the data block BlockNumber of device DeviceIndex
 * \param[in]  DeviceIndex
 * \param[in]  BlockNumber
 * \return     Returns if requested job has been accepted by the underlying MemHwA device.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-801
 * \trace SPEC-23071
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(uint8  DeviceIndex,uint16 Blockid, uint16 BlockNumber);


/**********************************************************************************************************************
 *  MemIf_EraseImmediateBlock()
 *********************************************************************************************************************/
/*!
 * \brief      Erases the data block BlockNumber of device DeviceIndex
 * \details    Erases the data block BlockNumber of device DeviceIndex
 * \param[in]  DeviceIndex
 * \param[in]  BlockNumber
 * \return     Returns if requested job has been accepted by the underlying MemHwA device.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-803
 * \trace SPEC-23067
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(uint8 DeviceIndex,uint16 Blockid, uint16 BlockNumber);


/**********************************************************************************************************************
 *  MemIf_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels the ongoing asynchronous operation of device DeviceIndex
 * \details    Cancels the ongoing asynchronous operation of device DeviceIndex
 * \param[in]  DeviceIndex
 * \pre        Underlying MemHwA device's status is MEMIF_BUSY
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-798
 * \trace SPEC-23042
 */
FUNC(void, MEMIF_CODE) MemIf_Cancel(uint8 DeviceIndex);


/**********************************************************************************************************************
 *  MemIf_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns the status of device DeviceIndex
 * \details    Returns current status of either one underlying MemHwA device or of all of them (Broadcast)
 * \param[in]  DeviceIndex
 * \return     Status of underlying MemHwA device
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-799
 * \trace SPEC-23051, SPEC-23060
 */
FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(uint8 DeviceIndex);


/**********************************************************************************************************************
 *  MemIf_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns the job result of device DeviceIndex
 * \details    Returns the job result of device DeviceIndex
 * \param[in]  DeviceIndex
 * \return     Job result of underlying MemHwA device
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-800
 * \trace SPEC-23074
 */
FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(uint8 DeviceIndex);


# if (MEMIF_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  MemIf_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * \brief      Retrieves the version information of MemIf module
 * \details    Stores version information, i.e. Module Id, Vendor Id, Vendor specific version numbers to structure pointed by VersionInfoPtr
 * \param[in]  VersionInfoPtr
 * \pre        GetVersionInfo API is enabled via pre-compile switch
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-802
 * \trace SPEC-23043, SPEC-23059, SPEC-38547
 */
void MemIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr);
# endif


/**********************************************************************************************************************
 *  MemIf_SetMode()
 *********************************************************************************************************************/
/*!
 * \brief      Sets the mode of all underlying MemHwA devices
 * \details    Sets the mode of all underlying MemHwA devices
 * \param[in]  Mode
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-795
 * \trace SPEC-23066
 */
FUNC(void, MEMIF_CODE) MemIf_SetMode(MemIf_ModeType Mode);


# define MEMIF_STOP_SEC_CODE
# include "MemMap.h"


#endif /* MEMIF_H */

/**********************************************************************************************************************
 *  END OF FILE: MemIf.h
 *********************************************************************************************************************/
