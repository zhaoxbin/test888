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
/*! \addtogroup Dem_Error
 *  \{
 *  \file       Dem_Error_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of Error subcomponent
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

#if !defined (DEM_ERROR_IMPLEMENTATION_H)
#define DEM_ERROR_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_InitState_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/*! Stores the code line where a run-time error has occurred */
VAR(uint16, DEM_VAR_NOINIT) Dem_LineOfRuntimeError;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/*! Stores the filename where a run-time error has occurred */
P2CONST(Dem_CharacterType, DEM_VAR_NOINIT, DEM_CONST) Dem_FileOfRuntimeError;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* *********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 **********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Error_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Error_ReportError
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Error_ReportError(
  CONST(uint8, AUTOMATIC) ApiId,
  CONST(uint8, AUTOMATIC) ErrorCode
  )
{
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  (void)Det_ReportError(DEM_MODULE_ID, 0, ApiId, ErrorCode);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ApiId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ErrorCode)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/* ****************************************************************************
 % Dem_Error_RunTimeCheckFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Error_RunTimeCheckFailed(
  CONSTP2CONST(Dem_CharacterType, AUTOMATIC, DEM_CONST) FileName,
  CONST(uint16, AUTOMATIC) Line
  )
{
  Dem_FileOfRuntimeError = FileName;
  Dem_LineOfRuntimeError = Line;
# if (DEM_DEV_DISABLE_ON_RUNTIME_ERRORS == STD_ON)                                                                               /* COV_DEM_FAILED_RUNTIME_CHECKS TX */
  Dem_InitState_SetInitState(DEM_INITSTATE_HALTED_AFTER_ERROR);
# endif
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_ERROR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Error_Implementation.h
 *********************************************************************************************************************/
