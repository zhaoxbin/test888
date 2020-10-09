/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_ExtCbk.h
 *        \brief  Callback interface of DCM for other BSWs
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
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
#if !defined(DCM_EXTCBK_H)
# define DCM_EXTCBK_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_EXTCBK_MAJOR_VERSION                                    11u
# define DCM_EXTCBK_MINOR_VERSION                                    6u
# define DCM_EXTCBK_PATCH_VERSION                                    0u
# if (DCM_EXTENSION_ID != 0x96ACD543UL)
#  error "Mismatching OEMs between static and generated code"
# endif
#endif /* !defined(DCM_EXTCBK_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_ExtCbk.h
 * ******************************************************************************************************************** */
