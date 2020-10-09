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
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  vstdlib.c
 *        \brief  Implementation of the generic Vector Standard Library (VStdLib_GenericAsr)
 *
 *      \details  The generic Vector Standard Library provides a hardware independent implementation
 *                of memory manipulation services used by several MICROSAR BSW components.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define VSTDLIB_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "vstdlib.h"

#if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Checks the version of the interface header file */
#if (  (VSTDLIB_SW_MAJOR_VERSION != (3u)) \
    || (VSTDLIB_SW_MINOR_VERSION != (0u)) \
    || (VSTDLIB_SW_PATCH_VERSION != (0u)) )
# error "Version numbers of vstdlib.c and vstdlib.h are inconsistent!"
#endif

/* Checks the version of the configuration header file */
#if (  (VSTDLIB_CFG_MAJOR_VERSION != (2u)) \
    || (VSTDLIB_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of vstdlib.c and VStdLib_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/

# if !defined (VSTDLIB_USE_LIBRARY_FUNCTIONS)
#  error "VSTDLIB_USE_LIBRARY_FUNCTIONS has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_RUNTIME_OPTIMIZATION)
#  error "VSTDLIB_RUNTIME_OPTIMIZATION has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_USE_JUMPTABLES)
#  error "VSTDLIB_USE_JUMPTABLES has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_DEV_ERROR_DETECT)
#  error "VSTDLIB_DEV_ERROR_DETECT has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_DEV_ERROR_REPORT)
#  error "VSTDLIB_DEV_ERROR_REPORT has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_VERSION_INFO_API)
#  error "VSTDLIB_VERSION_INFO_API has to be defined.. check VStdLib_Cfg.h!"
# endif

# if !defined (VSTDLIB_DUMMY_STATEMENT)
#  error "VSTDLIB_DUMMY_STATEMENT has to be defined.. check VStdLib_Cfg.h!"
# endif

# if ((VSTDLIB_DEV_ERROR_REPORT == STD_ON) && (VSTDLIB_DEV_ERROR_DETECT != STD_ON))
#  error "VSTDLIB_DEV_ERROR_REPORT defined to STD_ON requires VSTDLIB_DEV_ERROR_DETECT also to be defined to STD_ON!"
# endif

# if (VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_ON)
#  if (!defined (VStdLib_MemClr) || !defined (VStdLib_MemSet) || !defined (VStdLib_MemCpy) || \
       !defined (VStdLib_MemCpy16) || !defined (VStdLib_MemCpy32))
#   error "VStdLib_MemClr, VStdLib_MemSet, VStdLib_MemCpy, VStdLib_MemCpy16 and VStdLib_MemCpy32 have to be defined!"
#  endif
# else
#  if ((VSTDLIB_SUPPORT_LARGE_DATA != STD_ON) && (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON))
#   error "VSTDLIB_RUNTIME_OPTIMIZATION must not be enabled if large data support is not given!"
#  endif
# endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Masks internal parameters to ensure an upper limit of 3, respectively 31 */
#define VSTDLIB_MASK_3                       (0x03u)
#define VSTDLIB_MASK_31                      (0x1Fu)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/* Returns the number of bytes that are missing to the next 32-bit boundary */
#define VSTDLIB_ALIGN_OFFSET(ptr) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
  (uint8_least)((4u - (uint32_least)(ptr)) & VSTDLIB_MASK_3)

/**********************************************************************************************************************
 *  LOCAL TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Module specific definition of LOCAL_INLINE */
#if !defined (VSTDLIB_LOCAL_INLINE)
# define VSTDLIB_LOCAL_INLINE                LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define VSTDLIB_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON)
# if (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON)

/**********************************************************************************************************************
 *  VStdLib_Loc_MemSet_8_3()
 *********************************************************************************************************************/
/*! \brief         Initializes up to 3 bytes at pDst to the character nPattern (any alignment).
 *  \details       Depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst8         8-bit pointer to the memory location to be initialized.
 *  \param[in]     nPattern      The character to be used to initialize the memory.
 *  \param[in]     nCnt          Number of bytes to initialize, pDst must be valid for this amount.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst8' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemSet_8_31()
 *********************************************************************************************************************/
/*! \brief         Initializes up to 31 bytes at pDst to the character nPattern (any alignment).
 *  \details       Depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst8         8-bit pointer to the memory location to be initialized.
 *  \param[in]     nPattern      The character to be used to initialize the memory.
 *  \param[in]     nCnt          Number of bytes to initialize, pDst must be valid for this amount.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst8' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemSet_32_Aligned()
 *********************************************************************************************************************/
/*! \brief         Initializes memory at pDst to the character nPattern (32-bit aligned).
 *  \details       With a for loop, the tail depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst32        32-bit pointer to the memory location to be initialized.
 *  \param[in]     nPattern      The character to be used to initialize the memory.
 *  \param[in]     nCnt          Number of bytes to initialize, pDst must be valid for this amount.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst32' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  uint8 nPattern,
  uint32_least nCnt);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemCpy_8_3()
 *********************************************************************************************************************/
/*! \brief         Copies up to 3 bytes from pSrc to pDst (any alignment).
 *  \details       Depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst8         8-bit pointer to the memory location to copy to.
 *  \param[in]     pSrc8         8-bit pointer to the memory location to copy from.
 *  \param[in]     nCnt          Number of bytes to copy, pDst must be valid for this amount.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst8' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemCpy_8_31()
 *********************************************************************************************************************/
/*! \brief         Copies up to 31 bytes from pSrc to pDst (any alignment).
 *  \details       Depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst8         8-bit pointer to the memory location to copy to.
 *  \param[in]     pSrc8         8-bit pointer to the memory location to copy from.
 *  \param[in]     nCnt          Number of bytes to copy, pDst must be valid for this amount.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst8' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemCpy_32_Aligned()
 *********************************************************************************************************************/
/*! \brief         Copies 32-bit aligned data from pSrc to pDst.
 *  \details       With a for loop, the tail depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst32        32-bit pointer to the memory location to copy to.
 *  \param[in]     pSrc32        32-bit pointer to the memory location to copy from.
 *  \param[in]     nCnt          Number of bytes to copy, pDst must be valid for this amount.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst32' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemCpy_8_PartialWord()
 *********************************************************************************************************************/
/*! \brief         Copies a partial word of 1 to 3 bytes from pSrc to pDst to reach a 32-bit boundary (any alignment).
 *  \details       Depending on VSTDLIB_USE_JUMPTABLES either with a jumptable or a for loop.
 *  \param[out]    pDst8         8-bit pointer to the memory location to copy to.
 *  \param[in]     nCnt          Number of bytes to copy, pDst must be valid for this amount.
 *  \param[in,out] pPrev         Word to copy from (is modified and used by caller afterwards).
 *  \param[in,out] pDPos         Index for pDst8 to copy to (is modified and used by caller afterwards).
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst8' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_PartialWord(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8_least nCnt,
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pPrev,
  P2VAR(uint32_least, AUTOMATIC, VSTDLIB_VAR_FAR) pDPos);

/**********************************************************************************************************************
 *  VStdLib_Loc_MemCpy_32_Unaligned()
 *********************************************************************************************************************/
/*! \brief         Copies data from 32-bit aligned pSrc to unaligned pDst.
 *  \details       With a for loop using 32-bit accesses, the head and tail depending on VSTDLIB_USE_JUMPTABLES either
                   with a jumptable or a for loop.
 *  \param[out]    pDst8         8-bit pointer to the memory location to copy to.
 *  \param[in]     pSrc32        32-bit pointer to the memory location to copy from.
 *  \param[in]     nCnt          Number of bytes to copy, pDst must be valid for this amount.
 *  \param[in]     nDstOffset    pDst offset to the next 32-bit boundary.
 *  \context       ANY
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \config        VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON && VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON
 *  \pre           The parameters 'pDst8' and 'nCnt' have to define a valid memory area.
 *********************************************************************************************************************/
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Unaligned(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt,
  uint8_least nDstOffset);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * VStdLib_Loc_MemSet_8_3()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt)
{
  /* ----- Implementation ----------------------------------------------- */
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #10 Initialize up to 3 bytes using a jump table */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (nCnt)
  {
    case 3:
      pDst8[2] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 2:
      pDst8[1] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 1:
      pDst8[0] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    default:
      /* nothing to do */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#  else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  uint8_least idx;

  /* #20 Linearly initialize the bytes using a loop */
  for (idx = 0u; idx < nCnt; idx++)
  {
    pDst8[idx] = nPattern; /* SBSW_VSTDLIB_ACCESS_LOOP */
  }

#  endif /* VSTDLIB_USE_JUMPTABLES */
} /* VStdLib_Loc_MemSet_8_3() */

/**********************************************************************************************************************
 * VStdLib_Loc_MemSet_8_31()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8 nPattern,
  uint8_least nCnt)
{
  /* ----- Implementation ----------------------------------------------- */
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #10 Initialize up to 31 bytes using a jump table */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (nCnt)
  {
    case 31:
      pDst8[30] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 30:
      pDst8[29] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 29:
      pDst8[28] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 28:
      pDst8[27] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 27:
      pDst8[26] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 26:
      pDst8[25] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 25:
      pDst8[24] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 24:
      pDst8[23] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 23:
      pDst8[22] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 22:
      pDst8[21] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 21:
      pDst8[20] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 20:
      pDst8[19] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 19:
      pDst8[18] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 18:
      pDst8[17] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 17:
      pDst8[16] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 16:
      pDst8[15] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 15:
      pDst8[14] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 14:
      pDst8[13] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 13:
      pDst8[12] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 12:
      pDst8[11] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 11:
      pDst8[10] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 10:
      pDst8[9] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 9:
      pDst8[8] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 8:
      pDst8[7] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 7:
      pDst8[6] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 6:
      pDst8[5] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 5:
      pDst8[4] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 4:
      pDst8[3] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 3:
      pDst8[2] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 2:
      pDst8[1] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 1:
      pDst8[0] = nPattern; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    default:
      /* nothing to do */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#  else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  uint8_least idx;

  /* #20 Linearly initialize the bytes using a loop */
  for (idx = 0u; idx < nCnt; idx++)
  {
    pDst8[idx] = nPattern;  /* SBSW_VSTDLIB_ACCESS_LOOP */
  }

#  endif /* VSTDLIB_USE_JUMPTABLES */
} /* VStdLib_Loc_MemSet_8_31() */ /* PRQA S 6030 */ /* MD_VStdLib_Metrics */

/**********************************************************************************************************************
 * VStdLib_Loc_MemSet_32_Aligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemSet_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  uint8 nPattern,
  uint32_least nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32_least dPos = 0u;
  uint32_least remaining;
  uint32 nPattern32 =
    (uint32)(((uint32)nPattern << 24u) | ((uint32)nPattern << 16u) | ((uint32)nPattern << 8u) | nPattern);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Linearly initialize 16-byte blocks using 32-bit accesses in a loop */
  for (remaining = nCnt; remaining >= 16u; remaining -= 16u)
  {
    pDst32[dPos]      = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    pDst32[dPos + 1u] = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    pDst32[dPos + 2u] = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    pDst32[dPos + 3u] = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    dPos += 4u;
  }

#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #20 Initialize the remaining block using a jump table */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (remaining)
  {
    case 15:
    case 14:
    case 13:
    case 12:
      pDst32[dPos] = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_JUMPTABLE */
      dPos++;
      /* intentionally no break */
    case 11:
    case 10:
    case 9:
    case 8:
      pDst32[dPos] = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_JUMPTABLE */
      dPos++;
      /* intentionally no break */
    case 7:
    case 6:
    case 5:
    case 4:
      pDst32[dPos] = nPattern32; /* SBSW_VSTDLIB_ACCESS_32_JUMPTABLE */
      dPos++;
      /* intentionally no break */
    case 3:
    case 2:
    case 1:
      VStdLib_Loc_MemSet_8_3( /* SBSW_VSTDLIB_CALL_REMAINING_JUMPTABLE */
        (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
        nPattern,
        (uint8_least) (remaining & VSTDLIB_MASK_3));
      /* intentionally no break */
    default:
      /* nothing to do */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#  else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  /* #30 Initialize the remaining block using a byte-wise algorithm */
  VStdLib_Loc_MemSet_8_31( /* SBSW_VSTDLIB_CALL_REMAINING */
    (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
    nPattern,
    (uint8_least) remaining);

#  endif /* VSTDLIB_USE_JUMPTABLES */
} /* VStdLib_Loc_MemSet_32_Aligned() */

/**********************************************************************************************************************
 * VStdLib_Loc_MemCpy_8_3()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_3(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt)
{
  /* ----- Implementation ----------------------------------------------- */
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #10 Copy up to 3 bytes using a jump table */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (nCnt)
  {
    case 3:
      pDst8[2] = pSrc8[2]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 2:
      pDst8[1] = pSrc8[1]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 1:
      pDst8[0] = pSrc8[0]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    default:
      /* nothing to do */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#  else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  uint8_least idx;

  /* #20 Linearly copy the bytes using a loop */
  for (idx = 0u; idx < nCnt; idx++)
  {
    pDst8[idx] = pSrc8[idx]; /* SBSW_VSTDLIB_ACCESS_LOOP */
  }

#  endif /* VSTDLIB_USE_JUMPTABLES */
} /* VStdLib_Loc_MemCpy_8_3() */

/**********************************************************************************************************************
 * VStdLib_Loc_MemCpy_8_31()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_31(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8,
  uint8_least nCnt)
{
  /* ----- Implementation ----------------------------------------------- */
#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #10 Copy up to 31 bytes using a jump table */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (nCnt)
  {
    case 31:
      pDst8[30] = pSrc8[30]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 30:
      pDst8[29] = pSrc8[29]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 29:
      pDst8[28] = pSrc8[28]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 28:
      pDst8[27] = pSrc8[27]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 27:
      pDst8[26] = pSrc8[26]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 26:
      pDst8[25] = pSrc8[25]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 25:
      pDst8[24] = pSrc8[24]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 24:
      pDst8[23] = pSrc8[23]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 23:
      pDst8[22] = pSrc8[22]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 22:
      pDst8[21] = pSrc8[21]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 21:
      pDst8[20] = pSrc8[20]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 20:
      pDst8[19] = pSrc8[19]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 19:
      pDst8[18] = pSrc8[18]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 18:
      pDst8[17] = pSrc8[17]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 17:
      pDst8[16] = pSrc8[16]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 16:
      pDst8[15] = pSrc8[15]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 15:
      pDst8[14] = pSrc8[14]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 14:
      pDst8[13] = pSrc8[13]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 13:
      pDst8[12] = pSrc8[12]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 12:
      pDst8[11] = pSrc8[11]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 11:
      pDst8[10] = pSrc8[10]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 10:
      pDst8[9] = pSrc8[9]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 9:
      pDst8[8] = pSrc8[8]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 8:
      pDst8[7] = pSrc8[7]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 7:
      pDst8[6] = pSrc8[6]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 6:
      pDst8[5] = pSrc8[5]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 5:
      pDst8[4] = pSrc8[4]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 4:
      pDst8[3] = pSrc8[3]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 3:
      pDst8[2] = pSrc8[2]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 2:
      pDst8[1] = pSrc8[1]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    case 1:
      pDst8[0] = pSrc8[0]; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      /* intentionally no break */
    default:
      /* nothing to do */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#  else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  uint8_least idx;

  /* #20 Linearly copy the bytes using a loop */
  for (idx = 0u; idx < nCnt; idx++)
  {
    pDst8[idx] = pSrc8[idx]; /* SBSW_VSTDLIB_ACCESS_LOOP */
  }

#  endif /* VSTDLIB_USE_JUMPTABLES */
} /* VStdLib_Loc_MemCpy_8_31() */ /* PRQA S 6030 */ /* MD_VStdLib_Metrics */

/**********************************************************************************************************************
 * VStdLib_Loc_MemCpy_32_Aligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Aligned(
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32_least dPos = 0u; /* == sPos */
  uint32_least remaining;
  uint32 x0, x1, x2, x3;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Linearly copy 16-byte blocks using 32-bit accesses in a loop */
  for (remaining = nCnt; remaining >= 16u; remaining -= 16u)
  {
    x0 = pSrc32[dPos];
    x1 = pSrc32[dPos + 1u];
    x2 = pSrc32[dPos + 2u];
    x3 = pSrc32[dPos + 3u];
    pDst32[dPos]      = x0; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    pDst32[dPos + 1u] = x1; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    pDst32[dPos + 2u] = x2; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    pDst32[dPos + 3u] = x3; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
    dPos += 4u;
  }

#  if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #20 Copy the remaining block using a jump table */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (remaining)
  {
    case 15:
    case 14:
    case 13:
    case 12:
      pDst32[dPos] = pSrc32[dPos]; /* SBSW_VSTDLIB_ACCESS_32_JUMPTABLE */
      dPos++;
      /* intentionally no break */
    case 11:
    case 10:
    case 9:
    case 8:
      pDst32[dPos] = pSrc32[dPos]; /* SBSW_VSTDLIB_ACCESS_32_JUMPTABLE */
      dPos++;
      /* intentionally no break */
    case 7:
    case 6:
    case 5:
    case 4:
      pDst32[dPos] = pSrc32[dPos]; /* SBSW_VSTDLIB_ACCESS_32_JUMPTABLE */
      dPos++;
      /* intentionally no break */
    case 3:
    case 2:
    case 1:
      VStdLib_Loc_MemCpy_8_3( /* SBSW_VSTDLIB_CALL_REMAINING_JUMPTABLE */
        (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
        (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pSrc32[dPos],
        (uint8_least) (remaining & VSTDLIB_MASK_3));
      /* intentionally no break */
    default:
      /* nothing to do */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#  else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  /* #30 Copy the remaining block using a byte-wise algorithm */
  VStdLib_Loc_MemCpy_8_31( /* SBSW_VSTDLIB_CALL_REMAINING */
    (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos],
    (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pSrc32[dPos],
    (uint8_least) remaining);

#  endif /* VSTDLIB_USE_JUMPTABLES */
} /* VStdLib_Loc_MemCpy_32_Aligned() */

/**********************************************************************************************************************
 * VStdLib_Loc_MemCpy_8_PartialWord()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_8_PartialWord(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  uint8_least nCnt,
  P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pPrev,
  P2VAR(uint32_least, AUTOMATIC, VSTDLIB_VAR_FAR) pDPos)
{
  /* ----- Implementation ----------------------------------------------- */
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#   if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #10 Copy 1 to 3 bytes using a jump table and adapt '*pDPos' and '*pPrev' for little endian byte order */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (nCnt)
  {
    case 3:
      pDst8[*pDPos] = (uint8) *pPrev; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      (*pPrev) >>= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      /* intentionally no break */
    case 2:
      pDst8[*pDPos] = (uint8) *pPrev; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      (*pPrev) >>= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      /* intentionally no break */
    default: /* case 1 - nCnt is always in range [1..3] */
      pDst8[*pDPos] = (uint8) *pPrev; /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      (*pPrev) >>= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#   else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  uint8_least idx;

  /* #20 Linearly copy the bytes using a loop and adapt '*pDPos' and '*pPrev' for little endian byte order */
  for (idx = 0u; idx < nCnt; idx++)
  {
    pDst8[*pDPos] = (uint8) (uint8) *pPrev; /* SBSW_VSTDLIB_ACCESS_LOOP */
    (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
    (*pPrev) >>= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
  }

#   endif /* VSTDLIB_USE_JUMPTABLES */
#  else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
#   if (VSTDLIB_USE_JUMPTABLES == STD_ON)

  /* #30 Copy 1 to 3 bytes using a jump table and adapt '*pDPos' and '*pPrev' for big endian byte order */
  /* PRQA S 2003 VSTDLIB_NO_CASE_BREAK */ /* MD_VStdLib_NoCaseBreak */
  switch (nCnt)
  {
    case 3:
      pDst8[*pDPos] = (uint8) ((*pPrev) >> 24u); /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      (*pPrev) <<= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      /* intentionally no break */
    case 2:
      pDst8[*pDPos] = (uint8) ((*pPrev) >> 24u); /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      (*pPrev) <<= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      /* intentionally no break */
    default: /* case 1 -  nCnt is always in range [1..3] */
      pDst8[*pDPos] = (uint8) ((*pPrev) >> 24u); /* SBSW_VSTDLIB_ACCESS_8_JUMPTABLE */
      (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      (*pPrev) <<= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
      break;
  }
  /* PRQA L:VSTDLIB_NO_CASE_BREAK */

#   else /* VSTDLIB_USE_JUMPTABLES == STD_OFF */

  uint8_least idx;

  /* #40 Linearly copy the bytes using a loop and adapt '*pDPos' and '*pPrev' for big endian byte order */
  for (idx = 0u; idx < nCnt; idx++)
  {
    pDst8[*pDPos] = (uint8) ((*pPrev) >> 24u); /* SBSW_VSTDLIB_ACCESS_LOOP */
    (*pDPos)++; /* SBSW_VSTDLIB_ACCESS_LOCAL */
    (*pPrev) <<= 8u; /* SBSW_VSTDLIB_ACCESS_LOCAL */
  }

#   endif /* VSTDLIB_USE_JUMPTABLES */
#  endif /* CPU_BYTE_ORDER */
} /* VStdLib_Loc_MemCpy_8_PartialWord() */

/**********************************************************************************************************************
 * VStdLib_Loc_MemCpy_32_Unaligned()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
VSTDLIB_LOCAL_INLINE FUNC(void, VSTDLIB_CODE) VStdLib_Loc_MemCpy_32_Unaligned(
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8,
  P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc32,
  uint32_least nCnt,
  uint8_least nDstOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32_least dPos = 0u;
  uint32_least sPos = 0u;
  uint32_least remaining = nCnt;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If more than 32 bytes have to be copied */
  if (remaining >= 32u)
  {
    P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst32;
    uint32 prev;

    /* #20 Copy the first partial word to reach the 32-bit boundary and adjust the destination pointer */
    prev = pSrc32[sPos];
    remaining -= 4u;
    VStdLib_Loc_MemCpy_8_PartialWord( /* SBSW_VSTDLIB_CALL_MODIFIED_CNT */
      pDst8,
      nDstOffset,
      &prev,
      &dPos);

    /* At this point 'pDst8[dPos]' is aligned to a 32-bit boundary */
    pDst32 = (P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst8[dPos]; /* PRQA S 0310, 3305 */ /* MD_VStdLib_PtrCast */
    dPos = 0u;
    sPos++;

    /* #30 Linearly copy 16-byte blocks using 32-bit accesses by correcting the byte displacement of dst and src */
    if (nDstOffset == 3u) /* 24-bit displacement */
    {
      for (; remaining >= 16u; remaining -= 16u)
      {
        uint32 x0, x1, x2, x3, x4;
        x1 = pSrc32[sPos];
        x2 = pSrc32[sPos + 1u];
        x3 = pSrc32[sPos + 2u];
        x4 = pSrc32[sPos + 3u];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << 8u);
        x1 = (x1 >> 24u) | (x2 << 8u);
        x2 = (x2 >> 24u) | (x3 << 8u);
        x3 = (x3 >> 24u) | (x4 << 8u);
        prev = x4 >> 24u;
#  else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
        x0 = prev | (x1 >> 8u);
        x1 = (x1 << 24u) | (x2 >> 8u);
        x2 = (x2 << 24u) | (x3 >> 8u);
        x3 = (x3 << 24u) | (x4 >> 8u);
        prev = x4 << 24;
#  endif /* CPU_BYTE_ORDER */
        pDst32[dPos]      = x0; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 1u] = x1; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 2u] = x2; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 3u] = x3; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        dPos += 4u;
        sPos += 4u;
      }
    }
    else if (nDstOffset == 2u) /* 16-bit displacement */
    {
      for (; remaining >= 16u; remaining -= 16u)
      {
        uint32 x0, x1, x2, x3, x4;
        x1 = pSrc32[sPos];
        x2 = pSrc32[sPos + 1u];
        x3 = pSrc32[sPos + 2u];
        x4 = pSrc32[sPos + 3u];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << 16u);
        x1 = (x1 >> 16u) | (x2 << 16u);
        x2 = (x2 >> 16u) | (x3 << 16u);
        x3 = (x3 >> 16u) | (x4 << 16u);
        prev = x4 >> 16u;
#  else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
        x0 = prev | (x1 >> 16);
        x1 = (x1 << 16u) | (x2 >> 16u);
        x2 = (x2 << 16u) | (x3 >> 16u);
        x3 = (x3 << 16u) | (x4 >> 16u);
        prev = x4 << 16;
#  endif /* CPU_BYTE_ORDER */
        pDst32[dPos]      = x0; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 1u] = x1; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 2u] = x2; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 3u] = x3; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        dPos += 4u;
        sPos += 4u;
      }

    }
    else /* nDstOffset == 1 - 8-bit displacement */
    {
      for (; remaining >= 16u; remaining -= 16u)
      {
        uint32 x0, x1, x2, x3, x4;
        x1 = pSrc32[sPos];
        x2 = pSrc32[sPos + 1u];
        x3 = pSrc32[sPos + 2u];
        x4 = pSrc32[sPos + 3u];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << 24u);
        x1 = (x1 >> 8u) | (x2 << 24u);
        x2 = (x2 >> 8u) | (x3 << 24u);
        x3 = (x3 >> 8u) | (x4 << 24u);
        prev = x4 >> 8u;
#  else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
        x0 = prev | (x1 >> 24u);
        x1 = (x1 << 8u) | (x2 >> 24u);
        x2 = (x2 << 8u) | (x3 >> 24u);
        x3 = (x3 << 8u) | (x4 >> 24u);
        prev = x4 << 8u;
#  endif /* CPU_BYTE_ORDER */
        pDst32[dPos]      = x0; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 1u] = x1; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 2u] = x2; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        pDst32[dPos + 3u] = x3; /* SBSW_VSTDLIB_ACCESS_32_LOOP */
        dPos += 4u;
        sPos += 4u;
      }
    }

    /* #40 Linearly copy the remaining words using a loop */
    {
      uint8_least prevShift = (nDstOffset << 3u) & VSTDLIB_MASK_31;
      uint8_least xShift = 32u - prevShift;
      /* At this point remaining is < 16 byte */
      for (; remaining >= 4u; remaining -= 4u)
      {
        uint32 x0, x1;
        x1 = pSrc32[sPos];
#  if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        x0 = prev | (x1 << xShift);
        prev = x1 >> prevShift;
#  else /* CPU_BYTE_ORDER == HIGH_BYTE_FIRST */
        x0 = prev | (x1 >> xShift);
        prev = x1 << prevShift;
#  endif /* CPU_BYTE_ORDER */
        pDst32[dPos] = x0; /* SBSW_VSTDLIB_ACCESS_32_LOOP_REMAINING */
        dPos++;
        sPos++;
      }
    }

    /* #50 Copy the remaining partial word using a byte-wise algorithm */
    pDst8 = (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pDst32[dPos]; /* PRQA S 1338 */ /* MD_VStdLib_ParamMod */
    dPos = 0u;
    VStdLib_Loc_MemCpy_8_PartialWord( /* SBSW_VSTDLIB_CALL_REMAINING_PARTIAL */
      pDst8,
      (4u - nDstOffset),
      &prev,
      &dPos);
  }

  /* #60 Copy the remaining bytes using a byte-wise algorithm */
  VStdLib_Loc_MemCpy_8_31( /* SBSW_VSTDLIB_CALL_REMAINING */
    &pDst8[dPos],
    (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) &pSrc32[sPos],
    (uint8_least) remaining);
} /* VStdLib_Loc_MemCpy_32_Unaligned() */

# endif /* VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * VStdLib_MemSet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSTDLIB_CODE) VStdLib_MemSet(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                        uint8 nPattern,
                                        VStdLib_CntType nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8 = \
    (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst; /* PRQA S 0316 */ /* MD_VStdLib_PtrCast */
  uint8 errorId = VSTDLIB_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter 'pDst' */
  if (pDst == NULL_PTR)
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON)

    /* #20 If less than 32 bytes have to be initialized */
    if (nCnt < 32u)
    {
      /* #30 Use a byte-wise algorithm */
      VStdLib_Loc_MemSet_8_31( /* SBSW_VSTDLIB_CALL_UNMODIFIED */
        pDst8,
        nPattern,
        (uint8_least) nCnt);
    }
    /* #40 Else */
    else
    {
      /* #50 Get the destination pointer offset to the next 32-bit boundary */
      uint8_least nDstOffset = VSTDLIB_ALIGN_OFFSET(pDst8); /* PRQA S 0306 */ /* MD_VStdLib_PtrCastToInt */

      /* #60 If the destination is not aligned */
      if (nDstOffset != 0u)
      {
        /* #70 Initialize the amount of bytes to reach the alignment boundary and adjust the pointer */
        VStdLib_Loc_MemSet_8_3( /* SBSW_VSTDLIB_CALL_MODIFIED_CNT */
          pDst8,
          nPattern,
          nDstOffset);

        pDst8 = &pDst8[nDstOffset];
        nCnt -= nDstOffset; /* PRQA S 1338 */ /* MD_VStdLib_ParamMod */
      }

      /* #80 The pointer is aligned, use the 32-bit aligned memset */
      VStdLib_Loc_MemSet_32_Aligned( /* SBSW_VSTDLIB_CALL_MODIFIED_PTR_CNT */
        (P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst8, /* PRQA S 0310, 3305 */ /* MD_VStdLib_PtrCast */
        nPattern,
        nCnt);
    }

# else /* VSTDLIB_RUNTIME_OPTIMIZATION == STD_OFF */

    VStdLib_CntType idx;

    /* #90 Linearly initialize nCnt bytes using a loop */
    for (idx = 0u; idx < nCnt; idx++)
    {
      pDst8[idx] = nPattern; /* SBSW_VSTDLIB_ACCESS_LOOP */
    }

# endif /* VSTDLIB_RUNTIME_OPTIMIZATION */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_SET, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId); /* PRQA S 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* VStdLib_MemSet() */

/**********************************************************************************************************************
 * VStdLib_MemCpy()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                        P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                        VStdLib_CntType nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pDst8 = \
    (P2VAR(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst; /* PRQA S 0316 */ /* MD_VStdLib_PtrCast */
  P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc8 = \
    (P2CONST(uint8, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc; /* PRQA S 0316 */ /* MD_VStdLib_PtrCast */
  uint8 errorId = VSTDLIB_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameters 'pDst' and 'pSrc' */
  if ((pDst == NULL_PTR) || (pSrc == NULL_PTR))
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
# if (VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON)

    /* #20 If less than 32 bytes have to be copied */
    if (nCnt < 32u)
    {
      /* #30 Use a byte-wise algorithm */
      VStdLib_Loc_MemCpy_8_31( /* SBSW_VSTDLIB_CALL_UNMODIFIED */
        pDst8,
        pSrc8,
        (uint8_least) nCnt);
    }
    /* #40 Else */
    else
    {
      /* #50 Get the source pointer offset to the next 32-bit boundary */
      uint8_least nSrcOffset = VSTDLIB_ALIGN_OFFSET(pSrc8); /* PRQA S 0306 */ /* MD_VStdLib_PtrCastToInt */
      uint8_least nDstOffset;

      /* #60 If the source is not aligned */
      if (nSrcOffset != 0u)
      {
        /* #70 Copy the amount of bytes to reach the alignment boundary and adjust the pointers */
        VStdLib_Loc_MemCpy_8_3( /* SBSW_VSTDLIB_CALL_MODIFIED_CNT */
          pDst8,
          pSrc8,
          nSrcOffset);

        pSrc8 = &pSrc8[nSrcOffset];
        pDst8 = &pDst8[nSrcOffset];
        nCnt -= nSrcOffset; /* PRQA S 1338 */ /* MD_VStdLib_ParamMod */
      }

      /* #80 Get the destination pointer offset to the next 32-bit boundary */
      nDstOffset = VSTDLIB_ALIGN_OFFSET(pDst8); /* PRQA S 0306 */ /* MD_VStdLib_PtrCastToInt */

      /* #90 If destination is aligned */
      if (nDstOffset == 0u)
      {
        /* #100 Both pointers are aligned, use the 32-bit aligned memcpy */
        VStdLib_Loc_MemCpy_32_Aligned( /* SBSW_VSTDLIB_CALL_MODIFIED_PTR_CNT */
          (P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pDst8, /* PRQA S 0310, 3305 */ /* MD_VStdLib_PtrCast */
          (P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc8, /* PRQA S 0310, 3305 */ /* MD_VStdLib_PtrCast */
          nCnt);
      }
      /* #110 Else */
      else
      {
        /* #120 Use the 32-bit unaligned memcpy */
        VStdLib_Loc_MemCpy_32_Unaligned( /* SBSW_VSTDLIB_CALL_MODIFIED_PTR_CNT */
          pDst8,
          (P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR)) pSrc8, /* PRQA S 0310, 3305 */ /* MD_VStdLib_PtrCast */
          nCnt,
          nDstOffset);
      }
    }

# else /* VSTDLIB_RUNTIME_OPTIMIZATION == STD_OFF */

    VStdLib_CntType idx;

    /* #130 Linearly copy nCnt bytes using a loop */
    for (idx = 0u; idx < nCnt; idx++)
    {
      pDst8[idx] = pSrc8[idx]; /* SBSW_VSTDLIB_ACCESS_LOOP */
    }

# endif /* VSTDLIB_RUNTIME_OPTIMIZATION */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId); /* PRQA S 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* VStdLib_MemCpy() */

/**********************************************************************************************************************
 * VStdLib_MemCpy16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy16(P2VAR(uint16, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                          P2CONST(uint16, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                          VStdLib_CntType nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  VStdLib_CntType idx;
  uint8 errorId = VSTDLIB_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameters 'pDst' and 'pSrc' */
  if ((pDst == NULL_PTR) || (pSrc == NULL_PTR))
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Linearly copy nCnt 16-bit blocks using a loop */
    for (idx = 0u; idx < nCnt; idx++)
    {
      pDst[idx] = pSrc[idx]; /* SBSW_VSTDLIB_ACCESS_LOOP */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY_16, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId); /* PRQA S 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* VStdLib_MemCpy16() */

/**********************************************************************************************************************
 * VStdLib_MemCpy32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy32(P2VAR(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                          P2CONST(uint32, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                          VStdLib_CntType nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  VStdLib_CntType idx;
  uint8 errorId = VSTDLIB_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameters 'pDst' and 'pSrc' */
  if ((pDst == NULL_PTR) || (pSrc == NULL_PTR))
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Linearly copy nCnt 32-bit blocks using a loop */
    for (idx = 0u; idx < nCnt; idx++)
    {
      pDst[idx] = pSrc[idx]; /* SBSW_VSTDLIB_ACCESS_LOOP */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY_32, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId); /* PRQA S 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* VStdLib_MemCpy32() */

#endif /* VSTDLIB_USE_LIBRARY_FUNCTIONS != STD_ON */

/**********************************************************************************************************************
 * VStdLib_MemCpy_s()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSTDLIB_CODE) VStdLib_MemCpy_s(P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR) pDst,
                                          VStdLib_CntType nDstSize,
                                          P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR) pSrc,
                                          VStdLib_CntType nCnt)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VSTDLIB_E_NO_ERROR;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check parameter 'nDstSize' (independently of development error detection) */
  if (nCnt > nDstSize)
  {
    errorId = VSTDLIB_E_PARAM_SIZE;
  }
  else
  {
    /* #20 Call VStdLib_MemCpy() */
    VStdLib_MemCpy(pDst, pSrc, nCnt); /* SBSW_VSTDLIB_CALL_UNMODIFIED */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_MEM_COPY_S, errorId);
  }
#else
  VSTDLIB_DUMMY_STATEMENT(errorId); /* PRQA S 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* VStdLib_MemCpy_s() */

#if (VSTDLIB_VERSION_INFO_API == STD_ON)

/**********************************************************************************************************************
 *  VStdLib_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, VSTDLIB_CODE) VStdLib_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, VSTDLIB_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = VSTDLIB_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter 'versioninfo' */
  if (versioninfo == NULL_PTR)
  {
    errorId = VSTDLIB_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Write component data to 'versioninfo' */
    versioninfo->vendorID = VSTDLIB_VENDOR_ID;                /* SBSW_VSTDLIB_ACCESS_VERSIONINFO */
    versioninfo->moduleID = VSTDLIB_MODULE_ID;                /* SBSW_VSTDLIB_ACCESS_VERSIONINFO */
    versioninfo->sw_major_version = VSTDLIB_SW_MAJOR_VERSION; /* SBSW_VSTDLIB_ACCESS_VERSIONINFO */
    versioninfo->sw_minor_version = VSTDLIB_SW_MINOR_VERSION; /* SBSW_VSTDLIB_ACCESS_VERSIONINFO */
    versioninfo->sw_patch_version = VSTDLIB_SW_PATCH_VERSION; /* SBSW_VSTDLIB_ACCESS_VERSIONINFO */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (VSTDLIB_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VSTDLIB_E_NO_ERROR)
  {
    (void) Det_ReportError(VSTDLIB_MODULE_ID, VSTDLIB_INSTANCE_ID_DET, VSTDLIB_SID_GET_VERSION_INFO, errorId);
  }
# else
  VSTDLIB_DUMMY_STATEMENT(errorId); /* PRQA S 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* VStdLib_GetVersionInfo() */

#endif /* VSTDLIB_VERSION_INFO_API == STD_ON */

#define VSTDLIB_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

 MD_VStdLib_NoCaseBreak:
   Reason:     Break statements are omitted due to performance reasons when using jump tables.
   Risk:       Resulting code is misleading.
   Prevention: Code comments, code inspection and test of the different variants in the component test.

 MD_VStdLib_ParamMod:
   Reason:     Pointers and counts given as function parameters are modified during different algorithm stages.
   Risk:       Wrong pointer access is performed.
   Prevention: Silent analysis, code inspection and test of the different variants in the component test.

 MD_VStdLib_PtrCast:
   Reason:     Pointer is casted as different memory access sizes are utilized due to performance reasons.
   Risk:       Wrong pointer access is performed.
   Prevention: Code inspection and test of the different variants in the component test.

 MD_VStdLib_PtrCastToInt:
   Reason:     Pointer is casted to an integral type in order to get the target alignment.
   Risk:       None, as only LSBs are evaluated.
   Prevention: None.

 MD_VStdLib_Metrics:
   Reason:     No separation of functionality due to performance reasons when using jump tables.
   Risk:       None, as the complexity arises from one single switch statement.
   Prevention: None.

*/

/* SBSW_JUSTIFICATION_BEGIN

 \ID SBSW_VSTDLIB_CALL_UNMODIFIED
   \DESCRIPTION A function is called with unmodified 'pDst' and 'nCnt' parameters.
   \COUNTERMEASURE \N The caller of the function ensures that 'pDst' and 'nCnt' are valid. These parameters are passed
                      to the callee without modifications. If the parameters are casted there are no side effects.

 \ID SBSW_VSTDLIB_CALL_MODIFIED_CNT
   \DESCRIPTION A static function is called with unmodified 'pDst' parameter and a modified 'nCnt' parameter.
   \COUNTERMEASURE \N The caller of the function ensures that 'pDst' and 'nCnt' are valid. The offset value is
                      always smaller than 4 due to VSTDLIB_ALIGN_OFFSET() and 'nCnt' is 32 or higher at this point.
                      Therefore 'pDst' and 'nCnt' for the callee are valid.

 \ID SBSW_VSTDLIB_CALL_MODIFIED_PTR_CNT
   \DESCRIPTION A static function can be called with unmodified or modified 'pDst' and 'nCnt' parameters.
   \COUNTERMEASURE \N The caller of the function ensures that 'pDst' and 'nCnt' are valid. In case the function is
                      called with modified parameters (pointer alignment was performed), 'pDst' is incremented by
                      the value of 'nDstOffset' and 'nCnt' is decremented by the same value. Therefore 'pDst'
                      and 'nCnt' for the callee are valid.

 \ID SBSW_VSTDLIB_ACCESS_LOOP
   \DESCRIPTION Linear memory access using a for loop.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. The for loop ensures that
                      the loop index is always smaller than nCnt. Therefore only valid memory is accessed.

 \ID SBSW_VSTDLIB_ACCESS_8_JUMPTABLE
   \DESCRIPTION Linear 8-bit-access using a switch statement.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. The constant indices are
                      always smaller than the value of 'nCnt'. Therefore only valid memory is accessed.

 \ID SBSW_VSTDLIB_ACCESS_32_LOOP
   \DESCRIPTION Linear 32-bit-access using a for loop.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. The access index 'dPos'
                      is initialized with 0. The loop control variable 'remaining' is decremented by 16 per iteration.
                      The exit condition ensures that at least 16 bytes are valid per iteration. The access index
                      'dPos' plus constant offset ensures that exactly 16 valid bytes are accessed. 'dPos' is
                      incremented by 4 (that equals 16 bytes) after the access.

 \ID SBSW_VSTDLIB_ACCESS_32_LOOP_REMAINING
   \DESCRIPTION Linear 32-bit-access using a for loop.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. After the for loop above
                      'remaining' bytes of valid memory start at the address that is indicated by 'dPos'. The loop
                      control variable 'remaining' is decremented by 4 per iteration. The exit condition ensures that
                      at least 4 bytes are valid per iteration. The access index 'dPos' ensures that exactly 4 valid
                      bytes are accessed. 'dPos' is incremented by 1 (that equals 4 bytes) after the access.

 \ID SBSW_VSTDLIB_ACCESS_32_JUMPTABLE
   \DESCRIPTION Linear 32-bit-access using a switch statement.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. After the for loop above
                      'remaining' bytes of valid memory start at the address that is indicated by 'dPos'. The switch
                      statement ensures that an access is only made if at least 4 byte are valid. 'dPos' is
                      incremented by 4 after the access.

 \ID SBSW_VSTDLIB_CALL_REMAINING_JUMPTABLE
   \DESCRIPTION A static function is called to access the remaining bytes at the end of processing a 32-bit jump table.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. At this point 0-3
                      bytes of valid memory (indicated by the LSBs of 'remaining') start at the address that is
                      indicated by 'dPos'. Due to the usage of VSTDLIB_MASK_3 'pDst' and 'nCnt' for the callee are
                      valid.

 \ID SBSW_VSTDLIB_CALL_REMAINING
   \DESCRIPTION A static function is called to access the remaining bytes after 32-bit operations.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. After the for loop above
                      'remaining' bytes of valid memory start at the address that is indicated by 'dPos'. Therefore
                      'pDst' and 'nCnt' for the callee are valid.

 \ID SBSW_VSTDLIB_CALL_REMAINING_PARTIAL
   \DESCRIPTION A static function is called to access the remaining partial word after 32-bit displacement operations.
   \COUNTERMEASURE \N The caller of this function ensures that 'pDst' and 'nCnt' are valid. At this point at least
                      (4 - 'nDstOffset') bytes of valid memory start at the address that is indicated by 'dPos'.
                      Therefore 'pDst' and 'nCnt' for the callee are valid.

 \ID SBSW_VSTDLIB_ACCESS_LOCAL
   \DESCRIPTION Access to a pointer referencing a local variable.
   \COUNTERMEASURE \N The static function VStdLib_Loc_MemCpy_8_PartialWord() is only called with valid pointers to
                      local parameters.

 \ID SBSW_VSTDLIB_ACCESS_VERSIONINFO
   \DESCRIPTION The function VStdLib_GetVersionInfo() writes to the object referenced by parameter 'versioninfo'.
   \COUNTERMEASURE \N The caller ensures that the pointer passed to the parameter 'versioninfo' is valid and references
                      an object of type Std_VersionInfoType.

SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: vstdlib.c
 *********************************************************************************************************************/
