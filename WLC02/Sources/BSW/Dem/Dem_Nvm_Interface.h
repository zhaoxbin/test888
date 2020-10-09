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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Nvm Nvm
 *  \{
 *  \file       Dem_Nvm_Interface.h
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

#if !defined (DEM_NVM_INTERFACE_H)
#define DEM_NVM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Nvm_Types.h"

#if (DEM_CFG_USE_NVM == STD_ON)
#include "NvM.h"
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Nvm_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Nvm_GetSingleBlockId
 *****************************************************************************/
/*!
 * \brief         Get the index of a memory block.
 *
 * \details       Get the index of a memory block (from which type only one 
 *                block exists).
 *
 * \param[in]     BlockType
 *                Type of the memory block.
 *
 * \return        Block index of the given NvRAM block type.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Nvm_GetSingleBlockId(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Nvm_BlockType, AUTOMATIC)  BlockType
  );

/* ****************************************************************************
 * Dem_Nvm_SetSingleBlockState
 *****************************************************************************/
/*!
 * \brief         Set the status of a memory block.
 *
 * \details       Set the status of a memory block (from which type only one 
 *                block exists).
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     Status
 *                New status of the memory block.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetSingleBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_Nvm_SetEventMemoryBlockState
 *****************************************************************************/
/*!
 * \brief         Set the status of an event memory block.
 *
 * \details       Set the status of an event memory block.
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     Status
 *                New status of the memory block.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetEventMemoryBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_Nvm_SetTimeSeriesMemoryBlockState
 *****************************************************************************/
/*!
 * \brief         Set the status of a time series memory block.
 *
 * \details       Set the status of a time series memory block.
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     Status
 *                New status of the memory block.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetTimeSeriesMemoryBlockState(                                                                                           
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  Status
  );

/* ****************************************************************************
 % Dem_Nvm_SetAllBlocksDirty
 *****************************************************************************/
/*!
 * \brief         Sets the block state of all NV blocks 'Dirty'
 *
 * \details       Sets the block state of all NV blocks 'Dirty'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetAllBlocksDirty(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Nvm_Private Private Methods
 * \{
 */

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetPrivateBlockState
 *****************************************************************************/
/*!
 * \brief         Gets the status of the memory block
 *
 * \details       Gets the status of the memory block
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 *
 * \return        The status of the memory block
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Nvm_GetPrivateBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetPrivateBlockState
 *****************************************************************************/
/*!
 * \brief         Sets the status of the memory block
 *
 * \details       Sets the status of the memory block
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 * \param[in]     Status
 *                New status of the memory block
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetPrivateBlockState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  Status
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_TestBlockStateDirtyWithoutImmediate
 *****************************************************************************/
/*!
 * \brief         Tests if the 'Dirty' flag of the block state is set
 *
 * \details       Tests if the 'Dirty' flag of the block state is set
 *
 * \param[in]     BlockState
 *                The block state of a memory block
 *
 * \return        TRUE 
 *                The 'Dirty' flag of the block state is set
 *                FALSE
 *                The 'Dirty' flag of the block state is set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateDirtyWithoutImmediate(
  CONST(uint8, AUTOMATIC)  BlockState
  );

/* ****************************************************************************
 * Dem_Nvm_TestBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Tests if the 'Commit immediately' flag of the block state is 
 *                set
 *
 * \details       Tests if the 'Commit immediately' flag of the block state is 
 *                set
 *
 * \param[in]     BlockState
 *                The block state of a memory block
 *
 * \return        TRUE 
 *                The 'Commit immediately' flag of the block state is set
 *                FALSE
 *                The 'Commit immediately' flag of the block state is set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateImmediate(
  CONST(uint8, AUTOMATIC)  BlockState
  );

/* ****************************************************************************
 * Dem_Nvm_TestBlockStateClear
 *****************************************************************************/
/*!
 * \brief         Tests if the 'Clear' flag of the block state is set
 *
 * \details       Tests if the 'Clear' flag of the block state is set
 *
 * \param[in]     BlockState
 *                The block state of a memory block
 *
 * \return        TRUE 
 *                The 'Clear' flag of the block state is set
 *                FALSE
 *                The 'Clear' flag of the block state is set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestBlockStateClear(
  CONST(uint8, AUTOMATIC)  BlockState
  );

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetCurrentBlockIndex
 *****************************************************************************/
/*!
 * \brief         Gets the currently processed memory block
 *
 * \details       Gets the currently processed memory block
 *
 * \return        The handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Nvm_GetCurrentBlockIndex(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetCurrentBlockIndex
 *****************************************************************************/
/*!
 * \brief         Sets the currently processed memory block
 *
 * \details       Sets the currently processed memory block
 *
 * \param[in]     BlockIndex
 *                The handle of the memory block to be processed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentBlockIndex(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_GetCurrentCommitState
 *****************************************************************************/
/*!
 * \brief         Gets the state of the current commit
 *
 * \details       Gets the state of the current commit
 *
 * \return        DEM_NVM_COMMIT_IDLE
 *                No commit in progress
 *                DEM_NVM_COMMIT_WRITING
 *                Data commit is in progress
 *                DEM_NVM_COMMIT_FINISHED
 *                Data commit is completed
 *                DEM_NVM_COMMIT_FAILED
 *                Data commit is completed, but failed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Nvm_GetCurrentCommitState(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetCurrentCommitState
 *****************************************************************************/
/*!
 * \brief         Sets the state of the current commit
 *
 * \details       Sets the state of the current commit
 *
 * \param[in]     CommitState
 *                The state of the current commit
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentCommitState(
  CONST(uint8, AUTOMATIC)  CommitState
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestCurrentBlockIsCleared
 *****************************************************************************/
/*!
 * \brief         Tests if the currently processed block was cleared
 *
 * \details       Tests if the currently processed block was cleared
 *
 * \return        TRUE
 *                The currently processed block was cleared
 *                FALSE
 *                The currently processed block was not cleared
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestCurrentBlockIsCleared(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetCurrentBlockIsCleared
 *****************************************************************************/
/*!
 * \brief         Sets the value of the 'BlockIsCleared' flag for the currently 
 *                processed block
 *
 * \details       Sets the value of the 'BlockIsCleared' flag for the currently 
 *                processed block
 *
 * \param[in]     BlockIsCleared
 *                Flag to tell whether or not the current block is cleared or
 *                modified.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetCurrentBlockIsCleared(
  CONST(boolean, AUTOMATIC)  BlockIsCleared
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestPendingCommits
 *****************************************************************************/
/*!
 * \brief         Tests if NvRAM blocks have to be processed
 *
 * \details       Tests if NvRAM blocks have to be processed
 *
 * \return        TRUE
 *                NvRAM blocks have to be processed
 *                FALSE
 *                No NvRAM blocks have to be processed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestPendingCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_IncrementPendingCommits
 *****************************************************************************/
/*!
 * \brief         Increments the number of to be processed NvRAM blocks
 *
 * \details       Increments the number of to be processed NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_IncrementPendingCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_DecrementPendingCommits
 *****************************************************************************/
/*!
 * \brief         Decrements the number of to be processed NvRAM blocks
 *
 * \details       Decrements the number of to be processed NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_DecrementPendingCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_ResetPendingCommits
 *****************************************************************************/
/*!
 * \brief         Resets the number of to be processed NvRAM blocks
 *
 * \details       Resets the number of to be processed NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ResetPendingCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Tests if cleared NvRAM blocks have to be processed
 *
 * \details       Tests if cleared NvRAM blocks have to be processed
 *
 * \return        TRUE
 *                Cleared NvRAM blocks have to be processed
 *                FALSE
 *                No cleared NvRAM blocks have to be processed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_TestPendingClearCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_IncrementPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Increments the number of to be cleared NvRAM blocks
 *
 * \details       Increments the number of to be cleared NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_IncrementPendingClearCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_DecrementPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Decrements the number of to be cleared NvRAM blocks
 *
 * \details       Decrements the number of to be cleared NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_DecrementPendingClearCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_ResetPendingClearCommits
 *****************************************************************************/
/*!
 * \brief         Resets the number of to be cleared NvRAM blocks
 *
 * \details       Resets the number of to be cleared NvRAM blocks
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ResetPendingClearCommits(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_MemorySetBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Marks an event memory entry block as 'dirty' and commits it to
 *                NvM
 *
 * \details       This function checks the occurrence limit (if configured) and
 *                removes an immediate update request if necessary. Otherwise
 *                it behaves like Dem_Nvm_SetBlockStateImmediate.
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 * \param[in]     BlockState
 *                State modification of the block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different blocks
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_MemorySetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  BlockState
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Marks a block as 'dirty' and commits it to NvM
 *
 * \details       This function processes the NV block according to BlockState:
 *                DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG - The block is queued for
 *                immediate NV update.
 *                DEM_NVM_BLOCKSTATE_CLEARFLAG - The block was cleared.
 *                DEM_NVM_BLOCKSTATE_DIRTY - The block should be synchronized
 *                to NV-Ram during WriteAll.
 *                The NV block state will not downgrade, e.g. setting a block
 *                to DIRTY will not remove a CLEARFLAG or IMMEDIATEFLAG.
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 * \param[in]     BlockState
 *                State modification of the block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different blocks
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint8, AUTOMATIC)  BlockState
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_RestoreBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Restore internal state for block marked as 'dirty'
 *
 * \details       This function processes the NV block according to BlockState:
 *                DEM_NVM_BLOCKSTATE_IMMEDIATEFLAG - The block is queued for
 *                immediate NV update.
 *                DEM_NVM_BLOCKSTATE_CLEARFLAG - The block was cleared.
 *                DEM_NVM_BLOCKSTATE_DIRTY - The block should be synchronized
 *                to NV-Ram during WriteAll.
 *
 * \param[in]     BlockIndex
 *                Handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different blocks
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_RestoreBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_FindNextBlockToCommit
 *****************************************************************************/
/*!
 * \brief         Find the next modified block to commit
 *
 * \details       Find the next modified block to commit
 *
 * \return        TRUE
 *                A block was found
 *                FALSE
 *                No block was found
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_FindNextBlockToCommit(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_CommitBlock
 *****************************************************************************/
/*!
 * \brief         Processes NvM synchronization
 *
 * \details       This function writes the memory block marked for immediate
 *                synchronization into the NV storage.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_CommitBlock(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_ProcessQueue
 *****************************************************************************/
/*!
 * \brief         Process updates of deferred dirty markers
 *
 * \details       To avoid critical sections some NV block status updates are
 *                deferred. This function processes those updates.
 *                This function also processes the application request for
 *                complete NV-Ram synchronization.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ProcessQueue(
  void
  );
#endif

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_ON)
/* ****************************************************************************
 % Dem_Nvm_GetNvMResult
 *****************************************************************************/
/*!
 * \brief         Poll the result of an ongoing write job
 *
 * \details       Poll the result of an ongoing write job
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON &&
 *                DEM_CFG_SUPPORT_NVM_POLLING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_GetNvMResult(
  void
  );
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_InitStartup
 *****************************************************************************/
/*!
 * \brief         Initializes the NvM management
 *
 * \details       Initializes the NvM management on startup
 *
 * \pre           May be called only during module initialization
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_InitStartup(
  void
  );
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_InitWakeup
 *****************************************************************************/
/*!
 * \brief         Initializes the NvM management
 *
 * \details       Initializes the NvM management on wake up
 *
 * \pre           May be called only during module initialization
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_InitWakeup(
  void
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Nvm_Public Public Methods
 * \{
 */

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestAndSetBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Evaluates, if immediate Nv-Updates are possible and sets the
 *                block state accordingly. 
 *
 * \details       Evaluates, if immediate Nv-Updates are possible and sets the
 *                block state accordingly. 
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     OldOccCounter
 *                Old occurrence counter.
 * \param[in]     NewOccCounter
 *                New occurrence counter.
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON &&
 *                DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_TestAndSetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint16, AUTOMATIC)  OldOccCounter,
  CONST(uint16, AUTOMATIC)  NewOccCounter
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_SetStatusBlockChanged
 *****************************************************************************/
/*!
 * \brief         Set event-status memory block to changed
 *
 * \details       Set event-status memory block to changed
 *
 * \pre           DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetStatusBlockChanged(
  void
  );

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_IsCurrentlyWrittenBlockModified
 *****************************************************************************/
/*!
 * \brief         Tests if if the Dem is waiting for an NV write request
 *                and the NV same data block is also marked 'MODIFIED'
 *
 * \details       Tests if if the Dem is waiting for an NV write request
 *                and the NV same data block is also marked 'MODIFIED'
 *
 * \return        TRUE
 *                Dem is waiting for an NV write request and the same data
 *                block is marked 'MODIFIED'
 *                FALSE
 *                Dem is not waiting for an NV write request or written block
 *                is not marked 'MODIFIED'
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_IsCurrentlyWrittenBlockModified(
  void
  );
#endif

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 * Dem_Nvm_ChangeNVWriteState
 *****************************************************************************/
/*!
 * \brief         Change the NV write state according to the NV job result
 *
 * \details       Change the NV write state according to the NV job result
 *
 * \param[in]     JobResult
 *                Result of the NV job
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON && 
 *                DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ChangeNVWriteState(
  CONST(NvM_RequestResultType, AUTOMATIC)  JobResult
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the NvM management
 *
 * \details       Initializes the NvM management
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_Init(
  void
  );

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_Shutdown
 *****************************************************************************/
/*!
 * \brief         Finalize NvM block status
 *
 * \details       All pending Nv updates are reported as modified block for the
 *                NvM. (NvM_SetRamBlockStatus). The Dem assumes that all such
 *                marked blocks are persisted in NV-Ram using NvM_WriteAll
 *                following the Dem shutdown. This is not in scope of the Dem
 *                module however.
 *                If Dem_Shutdown is ever called without a following
 *                NvM_WriteAll, data will be lost.
 *
 * \pre           May be called only during module shutdown
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_Shutdown(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_MainFunction
 *****************************************************************************/
/*!
 * \brief         Processes NvM synchronization
 *
 * \details       The function controls NvM commits. Modified blocks are passed
 *                to the NvM to write back, and once the write operation has
 *                finished the next modified block is processed.
 *                In case of polling, NvM job results are updated here as well.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_MainFunction(
  void
  );

# if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON) && (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetSynchronizationFlag
 *****************************************************************************/
/*!
 * \brief         Sets a flag for NvM synchronization
 *
 * \details       Sets a flag for NvM synchronization.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON &&
 *                DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetSynchronizationFlag(
  void
  );
#endif /* (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON) && (DEM_CFG_USE_NVM == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_NVM_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Nvm_Interface.h
 *********************************************************************************************************************/
