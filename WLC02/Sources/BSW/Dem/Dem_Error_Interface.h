/* ********************************************************************************************************************
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
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \ingroup    Dem_Shared
 *  \defgroup   Dem_Error Assertion and Error handling
 *  \{
 *  \file       Dem_Error_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of Error subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Savas Ates                    vissat        Vector Informatik GmbH
 *  Anna Bosch                    visanh        Vector Informatik GmbH
 *  Stefan Huebner                vishrs        Vector Informatik GmbH
 *  Thomas Dedler                 visdth        Vector Informatik GmbH
 *  Alexander Ditte               visade        Vector Informatik GmbH
 *  Matthias Heil                 vismhe        Vector Informatik GmbH
 *  Erik Jeglorz                  visejz        Vector Informatik GmbH
 *  Friederike Hitzler            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ERROR_INTERFACE_H)
#define DEM_ERROR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
#include "Dem_Error_Types.h"
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Cfg_Declarations.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (__LINE__)                                                                                                          /* COV_DEM_PREPROCESSOR_DEFINE XF */
/*! substitute a number if the preprocessor does not support __LINE__ */
# define __LINE__                                0xffffu
#endif
#if !defined (__FILE__)                                                                                                          /* COV_DEM_PREPROCESSOR_DEFINE XF */
/*! substitute a char array if the preprocessor does not support __FILE__ */
# define __FILE__                                "Not supported"
#endif


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

                                                               /* Assertions */
/* ------------------------------------------------------------------------- */

#if (DEM_DEV_ERROR_REPORT == STD_ON)
/*! Define local variable for DET error code */
# define Dem_Det_ErrorRegisterDefine()           uint8 lErrorId;                                                                 /* PRQA S 3412, 3453 */ /* MD_MSR_19.4, MD_MSR_19.7 */
/*! Set error register with DET error code */
# define Dem_Det_ErrorRegisterSet(value)         lErrorId = (value);                                                             /* PRQA S 3412, 3453 */ /* MD_MSR_19.4, MD_MSR_19.7 */
/*! Get error register with DET error code */
# define Dem_Det_ErrorRegisterGet()              lErrorId                                                                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
#else
/*! Define local variable for DET error code  */
# define Dem_Det_ErrorRegisterDefine()                                                                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set error register with DET error code */
# define Dem_Det_ErrorRegisterSet(value)                                                                                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Get error register with DET error code */
# define Dem_Det_ErrorRegisterGet()                                                                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif

/* Internal Development Assertion Macros */
/*! Unconditional assertion, also calls DET if enabled */
#define Dem_Internal_AssertAlways(ErrorCode)
/*! Conditional assertion, also calls DET if enabled. Returns in case the assertion fails */
#define Dem_Internal_AssertReturnVoid(Condition, ErrorCode)
/*! Conditional assertion, also calls DET if enabled. Returns 'ReturnValue' in case the assertion fails */
#define Dem_Internal_AssertReturnValue(Condition, ErrorCode, ReturnValue)
/*! Conditional assertion, also calls DET if enabled. Continues with execution in case the assertion fails */
#define Dem_Internal_AssertContinue(Condition, ErrorCode)

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/*! Stores the code line where a run-time error has occurred */
extern VAR(uint16, DEM_VAR_NOINIT) Dem_LineOfRuntimeError;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/*! Stores the filename where a run-time error has occurred */
extern P2CONST(Dem_CharacterType, DEM_VAR_NOINIT, DEM_CONST) Dem_FileOfRuntimeError;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Error_Public Public Methods
 * \{
 */

/* ****************************************************************************
 % Dem_Error_ReportError
 *****************************************************************************/
/*!
 * \brief         Call DET error report.
 *
 * \details       Calls DET error report with the module Id of the Dem.
 *
 * \param[in]     ApiId
 *                API Id of the function calling this function
 * \param[in]     ErrorCode
 *                Error Code describing the error
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Error_ReportError(
  CONST(uint8, AUTOMATIC) ApiId,
  CONST(uint8, AUTOMATIC) ErrorCode
  );

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/* ****************************************************************************
 * Dem_Error_RunTimeCheckFailed
 *****************************************************************************/
/*!
 * \brief         Call DET error report.
 *
 * \details       Calls DET error report with the module Id of the Dem.
 *
 * \param[in]     FileName
 *                FileName in which the runtime error has occurred
 * \param[in]     Line
 *                Line on which the runtime error has occurred
 *
 * \pre           -
 * \config        DEM_DEV_RUNTIME_CHECKS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Error_RunTimeCheckFailed(
  CONSTP2CONST(Dem_CharacterType, AUTOMATIC, DEM_CONST) FileName,
  CONST(uint16, AUTOMATIC) Line
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_ERROR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Error_Interface.h
 *********************************************************************************************************************/
