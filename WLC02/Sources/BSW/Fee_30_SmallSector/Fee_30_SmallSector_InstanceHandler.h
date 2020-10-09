/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *        \file  Fee_30_SmallSector_InstanceHandler.h
 *         \brief  Fee Sub-component InstanceHandler source file
 *
 *       \details  InstanceHandler sub-component is responsible for management and initialization of instance relevant
 *                 data. InstanceHandler provides public services to other FEE sub-components to create instance objects
 *                 and access their data.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#ifndef FEE_30_SMALLSECTOR_INSTANCE_HANDLER_H
# define FEE_30_SMALLSECTOR_INSTANCE_HANDLER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
  INSTANCE_STATUS_ERASED = 0,
  INSTANCE_STATUS_OK,
  INSTANCE_STATUS_INVALID,
  INSTANCE_STATUS_INCONSISTENT
}Fee_30_SmallSector_Ih_InstanceStatusType;

typedef P2VAR(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_BufferPointerType;

typedef struct
{
  Fee_30_SmallSector_AddressType Fee_30_SmallSector_Ih_CompareAddress;
  uint16 Fee_30_SmallSector_Ih_CompareLength;
  Fee_30_SmallSector_Ih_BufferPointerType Fee_30_SmallSector_Ih_CompareBufferPtr;
}Fee_30_SmallSector_Ih_CompareParameterType;

typedef struct
{
  Fee_30_SmallSector_AddressType StartAddress;
  Fee_30_SmallSector_AddressType WP2Address;
  Fee_30_SmallSector_AddressType MgmtAddress;
  uint16 DataLength; /*!< The amount of payload bytes */
  Fee_30_SmallSector_StaticPatternState WP1State;
  Fee_30_SmallSector_StaticPatternState WP2State;
  uint8 MgmtValue;
  Fee_30_SmallSector_Ih_InstanceStatusType InstanceStatus;
}Fee_30_SmallSector_Ih_InstanceType;


typedef P2VAR(Fee_30_SmallSector_Ih_CompareParameterType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_CompareParameterPointerType;
typedef P2VAR(Fee_30_SmallSector_Ih_InstanceType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_InstanceVarPointerType;
typedef P2CONST(Fee_30_SmallSector_Ih_InstanceType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_InstanceConstPointerType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_IsLastPageNecessary()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if an additional last page needs to be written
 * \details    Calculates if all data bytes fit to pages or if a separate last page needs to be written
 * \param[in]  Instance
 * \return     TRUE: Additional last page needs to be written
 *             FALSE: Entire payload is aligned to page size
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_IsLastPageNecessary(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_CreateInstance()
 *********************************************************************************************************************/
/*!
 * \brief      Creates initialized instance object
 * \details    Creates and stores initialized instance values to instance object referenced by parameter Instance
 * \param[in]  Instance
 * \param[in]  InstanceStartAddress
 * \param[in]  DataLength
 * \param[in]  CycleCounter
 * \return     Instance object
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_CreateInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance,
        Fee_30_SmallSector_AddressType InstanceStartAddress, uint16 DataLength);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_InitInstance()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes instance which is passed via input parameter
 * \details    Initializes instance which is passed via input parameter
 * \param[in]  Instance
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_InitInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetInstanceStartAddress()
 *********************************************************************************************************************/
/*!
 * \brief      Returns start address of instance
 * \details    Returns start address of instance
 * \param[in]  Instance
 * \return     InstanceStartAddress
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceStartAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetStartPatternAddress()
 *********************************************************************************************************************/
/*!
 * \brief      Returns address of second write pattern of instance
 * \details    Returns address of second write pattern of instance
 * \param[in]  Instance
 * \return     Instance Start Pattern Address
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndPatternAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetManagementAddress()
 *********************************************************************************************************************/
/*!
 * \brief      Returns address of management information of instance
 * \details    Returns address of management information of instance
 * \param[in]  Instance
 * \return     Instance Management Info Address
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetManagementAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetInstanceDataLength()
 *********************************************************************************************************************/
/*!
 * \brief      Returns length of instance's data
 * \details    Returns length of instance's data. Length of FEE Management part is NOT included
 * \param[in]  Instance
 * \return     Data length of instance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceDataLength(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetInstanceStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns status of instance
 * \details    Evaluates and returns status of instance based on header and trailer values
 * \param[in]  Instance
 * \return     InstanceStatus
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_Ih_InstanceStatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceStatus(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetMgmtValue()
 *********************************************************************************************************************/
/*!
 * \brief      Returns value of instance's management information
 * \details    Returns value of instance's management information
 * \param[in]  Instance
 * \return     Value of management information
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetMgmtValue(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetWP1State()
 *********************************************************************************************************************/
/*!
 * \brief      Returns state of instance's first write pattern
 * \details    Returns state of instance's first write pattern
 * \param[in]  Instance
 * \return     State of first write pattern
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetWP1State(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetWP2State()
 *********************************************************************************************************************/
/*!
 * \brief      Returns state of instance's second write pattern
 * \details    Returns state of instance's second write pattern
 * \param[in]  Instance
 * \return     State of second write pattern
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetWP2State(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_StoreMgmtValueFromBuffer()
 *********************************************************************************************************************/
/*!
 * \brief      Stores recently read value of management byte from read buffer to passed instance
 * \details    Stores recently read value of management byte from read buffer to passed instance.
 *             This service is called after ReadManagementBytes sub-component stored management value in buffer.
 * \param[in]  Instance
 * \return     Value of trailer
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_StoreMgmtValueFromBuffer(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetInstanceStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Sets status of passed instance
 * \details    Sets status of passed instance
 * \param[in]  Instance
 * \param[in]  status
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetInstanceStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_Ih_InstanceStatusType status);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetWP1State()
 *********************************************************************************************************************/
/*!
 * \brief      Sets state of first write pattern of passed instance
 * \details    Sets state of first write pattern of passed instance
 * \param[in]  Instance
 * \param[in]  status
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetWP2State()
 *********************************************************************************************************************/
/*!
 * \brief      Sets state of second write pattern of passed instance
 * \details    Sets state of second write pattern of passed instance
 * \param[in]  Instance
 * \param[in]  status
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_PrepareNextInstanceProperties()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates addresses of instance based on start address and resets all other values
 * \details    Calculates addresses of instance based on start address and resets all other values
 * \param[in]  Instance
 * \param[in]  StartAddress
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_PrepareNextInstanceProperties(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance,
        Fee_30_SmallSector_AddressType StartAddress);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetManagementValuesAccordingToStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Sets management bytes with either valid or invalid values
 * \details    Sets both header and trailer values of passed instance with either valid (write job) or
 *             invalid values (invalidate job). Values are calculated from CycleCounter,
 *             which is stored in instance object.
 * \param[in]  Instance
 * \param[in]  IsValid
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetManagementValuesAccordingToStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetNegativeJobResultAccordingToStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns job result according to instance's status
 * \details    Returns job result according to instance's status
 * \param[in]  Instance
 * \return     MemIf_JobResult
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetNegativeJobResultAccordingToStatus(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_DetermineInstanceStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Sets status of passed instance
 * \details    Sets status of passed instance based on management values
 * \param[in]  Instance
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_DetermineInstanceStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_CorrectSingleBitFlips()
 *********************************************************************************************************************/
/*!
 * \brief      Performs single bit flip correction on passed ManagementByte
 * \details    Performs single bit flip correction on passed ManagementByte
 * \param[in]  ManagementByte
 * \pre        Pre-compile switch "CorrectSingleBitFlips" is enabled
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace DSGN-Fee22978
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_CorrectSingleBitFlips(Fee_30_SmallSector_Ih_BufferPointerType ManagementByte);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetStartPatternFromBuffer()
 *********************************************************************************************************************/
/*!
 * \brief      Determine state of start pattern by checking recently read content of buffer
 * \details    Determine state of start pattern by checking recently read content of buffer
 * \param[in]  Instance
 * \return     State of StartPattern
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetStartPatternFromBuffer(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetEndPatternFromBuffer()
 *********************************************************************************************************************/
/*!
 * \brief      Determine state of end pattern by checking recently read content of buffer
 * \details    Determine state of end pattern by checking recently read content of buffer
 * \param[in]  Instance
 * \return     State of EndPattern
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndPatternFromBuffer(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_BlankCheckStartPattern()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if first write pattern is blank
 * \details    Checks if first write pattern is blank
 * \param[in]  Instance
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckStartPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_BlankCheckEndPattern()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if second write pattern is blank
 * \details    Checks if second write pattern is blank
 * \param[in]  Instance
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckEndPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_ReadAllMgmt()
 *********************************************************************************************************************/
/*!
 * \brief      Requests reading all management information of Instance
 * \details    Requests reading both write patterns and management information of Instance
 * \param[in]  Instance
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadAllMgmt(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_ReadData()
 *********************************************************************************************************************/
/*!
 * \brief      Requests reading data bytes of instance
 * \details    Requests reading data bytes of instance by calling read service of FLS driver
 * \param[in]  InstanceHeaderAddress
 * \param[in]  DataBufferPtr
 * \param[in]  BlockOffset
 * \param[in]  ReadLength
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadData(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
                                                    Fee_30_SmallSector_Ih_BufferPointerType DataBufferPtr,
                                                    uint16 BlockOffset,
                                                    uint16 ReadLength,uint16 blockid);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteStartPattern()
 *********************************************************************************************************************/
/*!
 * \brief      Writes static pattern into first page of instance.
 * \details    Writes static start pattern to first page of instance. This is the first step of each write job.
 * \param[in]  Instance
 * \param[in]  CompareParameter
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteStartPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteManagementPage()
 *********************************************************************************************************************/
/*!
 * \brief      Write one page containing the management byte and optional payload bytes
 * \details    Write one page containing the management byte and optional payload bytes
 * \param[in]  Instance
 * \param[in]  UserJobParameter
 * \param[in]  CompareParameter
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteManagementPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WritePayload()
 *********************************************************************************************************************/
/*!
 * \brief      Write payload pages
 * \details    Write payload pages. Only data is contained which is aligned to the PageSize. Residual bytes are written in a separate step.
 * \param[in]  Instance
 * \param[in]  UserJobParameter
 * \param[in]  CompareParameter
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WritePayload(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteLastPage()
 *********************************************************************************************************************/
/*!
 * \brief      Writes last page
 * \details    Writes last page with some data bytes and some padding bytes
 * \param[in]  Instance
 * \param[in]  UserJobParameter
 * \param[in]  CompareParameter
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteLastPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteEndPattern()
 *********************************************************************************************************************/
/*!
 * \brief      Writes static pattern into second page of instance.
 * \details    Writes static start pattern to second page of instance. This is the last step of each write job.
 * \param[in]  Instance
 * \param[in]  CompareParameter
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        Pointer to parameter Instance of type Fee_30_SmallSector_Ih_InstanceType is valid
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteEndPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_VerifyData()
 *********************************************************************************************************************/
/*!
 * \brief      Verifies recently written data
 * \details    Verifies recently written data. Information about recently written data was stored in passed structure.
 * \param[in]  CompareParameter
 * \return     E_OK: Request to FLS driver was successful
 * \return     E_NOT_OK: Request to FLS driver failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 * \trace DSGN-Fee22975
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_VerifyData(Fee_30_SmallSector_Ih_CompareParameterType CompareParameter);


# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_INSTANCE_HANDLER_H */

/* PRQA L:LongInfixName */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_InstanceHandler.h
 *********************************************************************************************************************/
