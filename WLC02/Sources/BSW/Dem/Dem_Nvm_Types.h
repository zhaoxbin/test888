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
/*! \addtogroup Dem_Nvm
 *  \{
 *  \file       Dem_Nvm_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Control modification state of NV blocks and background synchronization with NvM
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

#if !defined (DEM_NVM_TYPES_H)
#define DEM_NVM_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*!
* \defgroup  Dem_Nvm_BlockTypes  Macros encoding the types of NvRAM blocks.
* \{
*/
#define DEM_NVM_BLOCKTYPE_ADMIN                      0U /*!< Value for the admin block */
#define DEM_NVM_BLOCKTYPE_STATUS                     1U /*!< Value for the status block */
#define DEM_NVM_BLOCKTYPE_PERMANENT                  2U /*!< Value for the permanent block */
#define DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME             3U /*!< Value for the OBDFreezeFrame block */
#define DEM_NVM_BLOCKTYPE_IUMPR                      4U /*!< Value for the IUMPR block */
#define DEM_NVM_BLOCKTYPE_DEBOUNCE                   5U /*!< Value for the debounce block */
#define DEM_NVM_BLOCKTYPE_AVAILABILITY               6U /*!< Value for the availability block */
#define DEM_NVM_BLOCKTYPE_DTR                        7U /*!< Value for the DTR block */
#define DEM_NVM_BLOCKTYPE_PRIMARY                    8U /*!< Value for a primary block */
#define DEM_NVM_BLOCKTYPE_SECONDARY                  9U /*!< Value for a secondary block */
#define DEM_NVM_BLOCKTYPE_TIMESERIES                10U /*!< Value for a time series block */
#define DEM_NVM_BLOCKTYPE_AGINGDATA                 11U /*!< Value for the aging data block */

/*!
* \}
*/

/*!
 * \defgroup  Dem_NvM_CommitState Macros encoding NV immediate data commit state
 * Macros encoding NV immediate data commit state
 * \{
 */
#define DEM_NVM_COMMIT_IDLE                      (0x00U)  /*!< No data commit in progress */
#define DEM_NVM_COMMIT_WRITING                   (0x01U)  /*!< Data commit in progress */
#define DEM_NVM_COMMIT_FINISHED                  (0x02U)  /*!< Data commit completed */
#define DEM_NVM_COMMIT_FAILED                    (0x03U)  /*!< Data commit finished, but failed */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_NvM_BlockState Macros encoding NV block state
 * Macros encoding NV block state
 * \{
 */
/* Take care with modifications: The implementation of Dem_Nvm_SetBlockStateImmediate() requires DIRTYFLAG < IMMEDIATEFLAG < CLEARFLAG */
#define DEM_NVM_BLOCKSTATE_DIRTYFLAG             (0x01U)  /*!< Block status bit 'data modified' */
#define DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG         (0x02U)  /*!< Block status bit 'commit immediately' */
#define DEM_NVM_BLOCKSTATE_CLEARFLAG             (0x04U)  /*!< Block status bit 'date cleared' */

#define DEM_NVM_BLOCKSTATE_UNMODIFIED            (0x00U)  /*!< Data is unmodified */
#define DEM_NVM_BLOCKSTATE_DIRTY                 (DEM_NVM_BLOCKSTATE_DIRTYFLAG)  /*!< Data modified, commit at shutdown */
#define DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE        (DEM_NVM_BLOCKSTATE_DIRTYFLAG|DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG)  /*!< Data modified, commit immediately */
#define DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE (DEM_NVM_BLOCKSTATE_DIRTYFLAG|DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG|DEM_NVM_BLOCKSTATE_CLEARFLAG)  /*!< Data cleared, commit immediately */

/*!
 * \}
 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type is used for NvRAM block types */
typedef uint8 Dem_Nvm_BlockType;

/*! NV commit management data */
#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
struct Dem_Nvm_CommitDataType_s
{
  Dem_Cfg_MemoryIndexType BlockIndex;  /*!< Currently processed memory block */
  Dem_Cfg_MemoryIndexType PendingCount;  /*!< Number of pending commits */
  uint8 CommitState;  /*!<State of current commit */
# if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
  Dem_Cfg_MemoryIndexType PendingClearCount;  /*!< Number of pending cleared block commits */
  boolean BlockIsCleared;  /*!< Indication if the currently processed block was cleared */
# endif
};
/*! NV commit management data type*/
typedef struct Dem_Nvm_CommitDataType_s Dem_Nvm_CommitDataType;
#endif

#endif /* DEM_NVM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Nvm_Types.h
 *********************************************************************************************************************/
