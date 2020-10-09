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
/*! \ingroup    Dem_ClientAccess
 *  \defgroup   Dem_DTCReadoutBuffer DTCReadoutBuffer
 *  \{
 *  \file       Dem_DTCReadoutBuffer_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
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

#if !defined (DEM_DTCREADOUTBUFFER_INTERFACE_H)
#define DEM_DTCREADOUTBUFFER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCReadoutBuffer_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTCReadoutBuffer_Properties Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestDataRequested
 *****************************************************************************/
/*!
 * \brief         Returns whether data was requested for the given buffer
 *
 * \details       Returns whether data was requested for the given buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                The given buffer contains or will contain data
 * \return        FALSE
 *                There is no data requested for the given buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestDataRequested(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestResultReady
 *****************************************************************************/
/*!
 * \brief         Returns whether the result of the data selection is available
 *
 * \details       Returns whether the result of the data selection is available
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                The given buffer is ready.
 * \return        FALSE
 *                The given buffer is still updating.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestResultReady(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestStoredDataAvailable
 *****************************************************************************/
/*!
 * \brief         Returns whether data is stored or not
 *
 * \details       Returns whether data is stored or not
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                The buffer holds the data stored for the requested event
 * \return        FALSE
 *                There is no stored data for the requested event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestStoredDataAvailable(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestExtendedRecordSelected
 *****************************************************************************/
/*!
 * \brief         Returns whether an extended data record is selected
 *
 * \details       Returns whether an extended data record is selected
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                An extended data record has been selected
 * \return        FALSE
 *                No extended data record has been selected
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestExtendedRecordSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedDataEventId
 *****************************************************************************/
/*!
 * \brief         Returns the Event Id
 *
 * \details       Returns the Event Id that was assigned to the readout buffer
 *                when initializing the extended entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        Event Id
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedDataEventId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedDataMemoryEntryId
 *****************************************************************************/
/*!
 * \brief         Returns the memory entry handle
 *
 * \details       Returns the memory entry handle that was assigned to the
 *                readout buffer when initializing the extended entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The memory entry handle
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedDataMemoryEntryId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedEntryIndex
 *****************************************************************************/
/*!
 * \brief         Returns the extended entry index
 *
 * \details       Returns the current extended entry index of the readout
 *                buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The extended entry index
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedEntryIndex(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedEntryIterator
 *****************************************************************************/
/*!
 * \brief         Returns the extended entry iterator
 *
 * \details       Returns the extended entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The extended entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ExtendedEntry_IterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetExtendedEntryIterator
 *****************************************************************************/
/*!
 * \brief         Sets the extended entry iterator
 *
 * \details       Sets the extended entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ExtendedEntryIter
 *                The new extended entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_ExtendedEntry_IterType, AUTOMATIC)  ExtendedEntryIter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_IncExtendedEntryIndex
 *****************************************************************************/
/*!
 * \brief         Increments the extended entry index
 *
 * \details       Increments the extended entry index of the readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ERecType
 *                Type of ExtendedData Record
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_IncExtendedEntryIndex(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  ERecType
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedDataNumber
 *****************************************************************************/
/*!
 * \brief         Returns the extended data record number
 *
 * \details       Returns the extended data record number
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The extended data record number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedDataNumber(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestSnapshotRecordSelected
 *****************************************************************************/
/*!
 * \brief         Returns whether a snapshot record is selected
 *
 * \details       Returns whether a snapshot record is selected
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        TRUE
 *                A snapshot record has been selected
 * \return        FALSE
 *                No snapshot record has been selected
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestSnapshotRecordSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotEntryIterator
 *****************************************************************************/
/*!
 * \brief         Return the snapshot record entry iterator
 *
 * \details       Return the snapshot record entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The snapshot record entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON && DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SnapshotEntry_IterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetSnapshotEntryIterator
 *****************************************************************************/
/*!
 * \brief         Sets the snapshot record entry iterator
 *
 * \details       Sets the snapshot record entry iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     SnapshotEntryIter
 *                The new value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_SnapshotEntry_IterType, AUTOMATIC)  SnapshotEntryIter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotRecordNumber
 *****************************************************************************/
/*!
 * \brief         Returns the 
 *
 * \details       Returns the 
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The record number of the selected snapshot record
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotRecordSource
 *****************************************************************************/
/*!
 * \brief         Returns the source
 *
 * \details       Returns the snapshot record source
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The source
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_SnapshotSourceType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotRecordSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetSnapshotRecordSource
 *****************************************************************************/
/*!
 * \brief         Sets the snapshot source type
 *
 * \details       Sets the snapshot source type
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     Source
 *                The new value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotRecordSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_SnapshotSourceType, AUTOMATIC)  Source
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotSourceIterator
 *****************************************************************************/
/*!
 * \brief         Returns the source iterator
 *
 * \details       Returns the source iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The source iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ComplexIterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetSnapshotSourceIterator
 *****************************************************************************/
/*!
 * \brief         Sets the source iterator
 *
 * \details       Sets the source iterator
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     SourceIterator
 *                The new value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_Cfg_ComplexIterType, AUTOMATIC)  SourceIterator
);                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetMemoryEntryId
 *****************************************************************************/
/*!
 * \brief         Returns the memory entry Id for the given readout buffer
 *
 * \details       Returns the memory entry Id for the given readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        The memory entry Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemoryEntryId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetEventId
 *****************************************************************************/
/*!
 * \brief         Get EventId of readout buffer.
 *
 * \details       Get EventId of readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        The EventId of the readout buffer
 *
 * \pre           Dem_DTCReadoutBuffer_GetState() != DEM_DTCREADOUTBUFFER_UNUSED
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCReadoutBuffer_GetEventId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetMemoryId
 *****************************************************************************/
/*!
 * \brief         Get the memory location
 *
 * \details       Get the memory locations of the given record
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Size of a memory entry Data record in bytes.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemoryId(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
* Dem_DTCReadoutBuffer_SetOBDData_IsStored
*****************************************************************************/
/*!
* \brief         Sets the stored status of OBD FreezeFrame
*
* \details       Sets the stored status of OBD FreezeFrame for requested ReadOutBuffer
*                ReadoutBufferId
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer, derived from the ClientId.
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON 
*                && DEM_CFG_SUPPORT_OBDII == STD_ON
*                && DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetOBDData_IsStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(boolean, AUTOMATIC) IsStored
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
* Dem_DTCReadoutBuffer_GetOBDData_IsStored
*****************************************************************************/
/*!
* \brief         Returns the stored status of OBD FreezeFrame
*
* \details       Returns the stored status of OBD FreezeFrame for requested ReadOutBuffer 
*                ReadoutBufferId
*
* \param[in]     ReadoutBufferId
*                Index of the ReadoutBuffer, derived from the ClientId.
*
* \return        Stored status of OBD FreezeFrame
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*                && DEM_CFG_SUPPORT_OBDII == STD_ON
*                && DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_GetOBDData_IsStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer
 *****************************************************************************/
/*!
 * \brief         Returns pointer to OBD FreezeFrame buffer
 *
 * \details       Returns pointer to OBD FreezeFrame buffer in ReadoutBuffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Pointer to OBD FreezeFrame buffer in ReadoutBuffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                && DEM_CFG_SUPPORT_OBDII == STD_ON
 *                && DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
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
 * \defgroup Dem_DTCReadoutBuffer_Public Public Methods
 * \{
 */
#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr
 *****************************************************************************/
/*!
 * \brief         Returns the pointer to the global snapshot data in the 
 *                memory entry of the readout buffer.
 *
 * \details       Returns the pointer to the global snapshot data in the 
 *                memory entry of the readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        Pointer to the beginning of the global snapshot data set.
 *
 * \pre           Readout buffer is initiliazed.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
  Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_TestGlobalSnapshotStored
 *****************************************************************************/
/*!
 * \brief         Returns whether global snapshot is stored.
 *
 * \details       Returns whether global snapshot is stored.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        TRUE, global snapshot is stored
 *
 * \return        FALSE, global snapshot is not stored
 *
 * \pre           Readout buffer is initiliazed.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTCReadoutBuffer_TestGlobalSnapshotStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_Init
 *****************************************************************************/
/*!
 * \brief         Initialize memory entry.
 *
 * \details       Initialize memory entry.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_Init(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_CheckAndSetState
 *****************************************************************************/
/*!
 * \brief         Check state of a ReadoutBuffer entry, save current request if
 *                it is new.
 *
 * \details       Check state of a ReadoutBuffer entry, save current request if
 *                it is new.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     EventId
 *                New EventId for comparison, stored in ReadoutBuffer with a
 *                new request.
 * \param[in]     MemoryId
 *                New MemoryId for comparison, stored in ReadoutBuffer with a
 *                new request.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector
 *
 * \return        E_OK
 *                ReadoutBuffer contains given EventId, MemoryId
 *                configuration and the copying of event data (MainFunction)
 *                has finished - current request is identical repetition of
 *                previous, no data change.
 * \return        DEM_PENDING
 *                Either ReadoutBuffer is unused, so it contains no valid
 *                data - store current request as new request and QUEUE it for
 *                MainFunction to copy the event data.
 *                Or ReadoutBuffer contains given EventId, MemoryId
 *                configuration but the copying of event data (MainFunction)
 *                has NOT finished yet - no data change.
 * \return        E_NOT_OK
 *                ReadoutBuffer contains different EventId, MemoryId
 *                configuration, current request is different to previous -
 *                no data change.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTCReadoutBuffer_CheckAndSetState(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_EventIdType, AUTOMATIC)                 EventId,
  CONST(uint8, AUTOMATIC)                           MemoryId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_FillData
 *****************************************************************************/
/*!
 * \brief         Populate readout buffer with data.
 *
 * \details       Populate readout buffer with data by copying the record from
 *                the primary/secondary memory.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTCReadoutBuffer_FillData(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_FreeBuffer
 *****************************************************************************/
/*!
 * \brief         Release the memory entry.
 *
 * \details       Release the memory entry calling Dem_EnableDTCRecordUpdate.
 * 
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 * \param[in]     DTCSelector
 *                Handle for DTC Selector 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_FreeBuffer(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SelectExtendedDataRecord
 *****************************************************************************/
/*!
 * \brief         Selects a data record
 *
 * \details       Initializes the iterator for the selected event.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ExtendedDataNumber
 *                The extended data number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SelectExtendedDataRecord(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) ExtendedDataNumber
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SelectSnapshotRecord
 *****************************************************************************/
/*!
 * \brief         Selects a data record
 *
 * \details       Initializes the iterator for the selected event.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     RecordNumber
 *                The selected record number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SelectSnapshotRecord(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(uint8, AUTOMATIC) RecordNumber
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

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
 * \defgroup Dem_DTCReadoutBuffer_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetReadoutBufferEntry()
 *****************************************************************************/
/*!
 * \brief         Sets the readout buffer entry
 *
 * \details       Set the EventId, MemoryId, State, ExtendedIterator and 
 *                SnapshotIterator of the readout buffer entry for the given 
 *                handle
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     EventId
 *                EventId to be set
 * \param[in]     MemoryId
 *                MemoryId to be set
 * \param[in]     State
 *                State to be set
 * \param[in]     ExtendedIterator
 *                Pointer to ExtendedIterator to be set
 * \param[in]     SnapshotIterator
 *                Pointer to SnapshotIterator to be set
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ReadoutBuffer Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_DTCReadoutBuffer_SetReadoutBufferEntry(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint16, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  State,
  Dem_DTCReadoutBuffer_ExtendedDataIteratorConstPtrType  ExtendedIterator,
  Dem_DTCReadoutBuffer_SnapshotDataIteratorConstPtrType  SnapshotIterator
  );

/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetEntrySafe()
 *****************************************************************************/
/*!
 * \brief         Returns pointer to the readout buffer entry
 *
 * \details       Checks if passed handle is valid and returns pointer to the 
 *                readout buffer entry
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        Valid pointer to the readout buffer entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ReadoutBufferEntryPtrType, DEM_CODE) 
Dem_DTCReadoutBuffer_GetEntrySafe(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_ExtendedDataRecord_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the extended data iterator
 *
 * \details       Clear all members.
 *
 * \param[in]     ExtendedDataIterator
 *                Pointer to the extended data iterator to be initialized
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_ExtendedDataRecord_Init(
  Dem_DTCReadoutBuffer_ExtendedDataIteratorPtrType ExtendedDataIterator
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SnapshotRecord_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the snapshot record iterator
 *
 * \details       Clear all members.
 *
 * \param[in]     SnapshotDataIterator
 *                Pointer to the snapshot data iterator to be initialized
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SnapshotRecord_Init(
  Dem_DTCReadoutBuffer_SnapshotDataIteratorPtrType SnapshotDataIterator
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetExtendedIteratorPtr
 *****************************************************************************/
/*!
 * \brief         Returns pointer to the extended iterator
 *
 * \details       Returns pointer to the extended iterator of the given readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        Pointer to the extended iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_ExtendedDataIteratorPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 *  Dem_DTCReadoutBuffer_SetExtendedIterator
 *****************************************************************************/
/*!
 * \brief         Sets the extended iterator
 *
 * \details       Sets the extended iterator of the given readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ExtendedDataIterator
 *                Pointer to the new value of the extended data iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  Dem_DTCReadoutBuffer_ExtendedDataIteratorConstPtrType  ExtendedDataIterator
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr
 *****************************************************************************/
/*!
 * \brief         Returns pointer to the snapshot iterator
 *
 * \details       Returns pointer to the snapshot iterator of the given readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \return        Pointer to the snapshot iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_SnapshotDataIteratorPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 *  Dem_DTCReadoutBuffer_SetSnapshotIterator
 *****************************************************************************/
/*!
 * \brief         Sets the snapshot iterator
 *
 * \details       Sets the snapshot iterator of the given readout buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \param[in]     SnapshotIterator
 *                Pointer to the new value of the snapshot data iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  Dem_DTCReadoutBuffer_SnapshotDataIteratorConstPtrType SnapshotIterator
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_GetState
 *****************************************************************************/
/*!
 * \brief         Get internal state of readout buffer.
 *
 * \details       Get internal state of readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \return        DEM_DTCREADOUTBUFFER_UNUSED
 *                The readout buffer is unused and contains no (i.e. invalid)
 *                data.
 * \return        DEM_DTCREADOUTBUFFER_QUEUED
 *                The readout buffer contains EventId, MemoryId values, and is
 *                waiting for the MainFunction to copy the Data.
 * \return        DEM_DTCREADOUTBUFFER_IN_USE
 *                The readout buffer contains configuration and event's data.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_StatusType, DEM_CODE)
Dem_DTCReadoutBuffer_GetState(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetState
 *****************************************************************************/
/*!
 * \brief         Set internal state of readout buffer.
 *
 * \details       Set internal state of readout buffer.
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer, derived from the ClientId.
 *
 * \param[in]     State
 *                New internal state to be set
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetState(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  State
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_SetExtendedEntryIndex
 *****************************************************************************/
/*!
 * \brief         Sets the extended entry index
 *
 * \details       Sets the new extended entry index of the readout
 *                buffer
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 * \param[in]     ExtendedEntryIndex
 *                New extended entry index
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedEntryIndex(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 * Dem_DTCReadoutBuffer_CopyOBDFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Copies OBD FreezeFrame
 *
 * \details       Copies OBD FreezeFrame from memory buffer to
 *                OBD FreezeFrame Buffer in ReadOutBuffer
 *
 *
 * \param[in]     ReadoutBufferId
 *                Index of the ReadoutBuffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *                && DEM_CFG_SUPPORT_OBDII == STD_ON
 *                && DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_CopyOBDFreezeFrame(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCREADOUTBUFFER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReadoutBuffer_Interface.h
 *********************************************************************************************************************/
