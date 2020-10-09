
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Dem_MemMap.h
      Project:  Vector Basic Runtime System
       Module:  BRS@Impl_Stubs

  \brief Description:  Stub of Dem_MemMap.h for a simple default UseCase with up to 6 Cores.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Daniel Kuhnle                 viskdl        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2019-02-14  visbwa  Initial creation, based on Diag_Asr4Dem@Implementation[16.01.00]
                        viskdl  Adaptions for actual MSR4-R21 default Startapplication applications
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

 /* PRQA S 0883 */  /* MD_DEM_1915 */
#if defined (DEM_START_SEC_0_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_0_VAR_ZERO_INIT_UNSPECIFIED                                                                                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_0_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_0_VAR_ZERO_INIT_UNSPECIFIED                                                                                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* Sample Preprocessor directive for a newly configured OS-Application instance <OS_APPLICATION_NAME>

  #if defined (DEM_START_SEC_<OS_APPLICATION_NAME>_VAR_ZERO_INIT_UNSPECIFIED)
  # undef DEM_START_SEC_<OS_APPLICATION_NAME>_VAR_ZERO_INIT_UNSPECIFIED
  # define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
  #endif

  #if defined (DEM_STOP_SEC_<OS_APPLICATION_NAME>_VAR_ZERO_INIT_UNSPECIFIED)
  # undef DEM_STOP_SEC_<OS_APPLICATION_NAME>_VAR_ZERO_INIT_UNSPECIFIED
  # define STOP_SEC_VAR
  #endif
 */

/**********************************************************************************************************************
  OsApplication_Trusted_Core0
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_Trusted_Core0_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_Trusted_Core0_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_NonTrusted_Core0
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_NonTrusted_Core0_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE0_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_NonTrusted_Core0_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_Trusted_Core1
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_Trusted_Core1_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_Trusted_Core1_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_NonTrusted_Core1
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_NonTrusted_Core1_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE1_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_NonTrusted_Core1_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_Trusted_Core2
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_Trusted_Core2_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_Trusted_Core2_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_NonTrusted_Core2
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_NonTrusted_Core2_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE2_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_NonTrusted_Core2_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_Trusted_Core3
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_Trusted_Core3_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_Trusted_Core3_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_NonTrusted_Core3
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_NonTrusted_Core3_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE3_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_NonTrusted_Core3_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_Trusted_Core4
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_Trusted_Core4_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_Trusted_Core4_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_NonTrusted_Core4
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_NonTrusted_Core4_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE4_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_NonTrusted_Core4_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_Trusted_Core5
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_TRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_Trusted_Core5_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_TRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_Trusted_Core5_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
  OsApplication_NonTrusted_Core5
**********************************************************************************************************************/
#if defined (DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_START_SEC_OSAPPLICATION_NONTRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED
/*# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED*/
# define OS_START_SEC_OsApplication_NonTrusted_Core5_VAR_ZERO_INIT_UNSPECIFIED
#endif

#if defined (DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED)
# undef DEM_STOP_SEC_OSAPPLICATION_NONTRUSTED_CORE5_VAR_ZERO_INIT_UNSPECIFIED
/*# define STOP_SEC_VAR*/
# define OS_STOP_SEC_OsApplication_NonTrusted_Core5_VAR_ZERO_INIT_UNSPECIFIED
#endif

