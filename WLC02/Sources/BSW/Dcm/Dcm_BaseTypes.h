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
/**        \file  Dcm_BaseTypes.h
 *        \brief  Public data type definition interface of DCM
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
#if !defined(DCM_BASETYPES_H)
# define DCM_BASETYPES_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_BASETYPES_MAJOR_VERSION                                 11u
# define DCM_BASETYPES_MINOR_VERSION                                 6u
# define DCM_BASETYPES_PATCH_VERSION                                 0u
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/* DID operation types - bitmapped which gives the application the opportunity to "OR" multiple operations per DID */
#  define DCM_DID_OP_READ                                            ((Dcm_DidOpType)0x01u)
#  define DCM_DID_OP_WRITE                                           ((Dcm_DidOpType)0x02u)
#  define DCM_DID_OP_IO                                              ((Dcm_DidOpType)0x04u)
#  define DCM_DID_OP_SCALINGINFO                                     ((Dcm_DidOpType)0x08u)
#  define DCM_DID_OP_DEFINE                                          ((Dcm_DidOpType)0x10u)
/*! Not used directly!
#  define DCM_DID_OP_IS_AVAILABLE                                    ((Dcm_DidOpType)0x20u)
*/
#  define DCM_DID_OP_ROE                                             ((Dcm_DidOpType)0x40u)
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Typedefs
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8       Dcm_DidOpMemType;
typedef uint8_least Dcm_DidOpOptType;

typedef Dcm_DidOpMemType Dcm_DidOpType;
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
#endif /* !defined(DCM_BASETYPES_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_BaseTypes.h
 * ******************************************************************************************************************** */
