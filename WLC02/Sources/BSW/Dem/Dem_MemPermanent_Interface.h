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
/*! \ingroup    Dem_Memory
 *  \defgroup   Dem_MemPermanent MemPermanent
 *  \{
 *  \file       Dem_MemPermanent_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file.
 *  \details    Implementation of the Permanent Memory subcomponent which manages storage of permanent DTCs.
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
 *  Friederike Schulze            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMPERMANENT_INTERFACE_H)
#define DEM_MEMPERMANENT_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemPermanent_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MemPermanent_Properties Properties
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyGetEventId
 *****************************************************************************/
/*!
 * \brief         Get the event Id in confirmed chronology
 *
 * \details       Get the event Id in confirmed chronology
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 *
 * \return        EventId
 *                Unique handle of the event.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologySetEventId
 *****************************************************************************/
/*!
 * \brief         Set the event Id in confirmed chronology
 *
 * \details       Set the event Id in confirmed chronology
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 * \param[in]     EventId
 *                Unique handle of the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * \brief         Mark the confirmed chronology as NOT overflown.
 *
 * \details       Mark the confirmed chronology as NOT overflown.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyResetOverflown( 
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologySetOverflown
 *****************************************************************************/
/*!
 * \brief         Mark the confirmed chronology as overflown.
 *
 * \details       Mark the confirmed chronology as overflown.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetOverflown( 
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyGetCurrentSize
 *****************************************************************************/
/*!
 * \brief         Get the number of occupied entries in the confirmed chronology.
 *
 * \details       Get the number of occupied entries in the confirmed chronology.
 *
 *
 * \return        Size
 *                Number of occupied entries in the confirmed chronology.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetCurrentSize(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologySetCurrentSize
 *****************************************************************************/
/*!
 * \brief         Set the number of occupied entries in the confirmed chronology.
 *
 * \details       Set the number of occupied entries in the confirmed chronology.
 *
 * \param[in]     Size
 *                New number of occupied entries in the confirmed chronology.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetCurrentSize(
  CONST(uint16, AUTOMATIC)  Size
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
 * \defgroup Dem_MemPermanent_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_PermanentFillUpAddEvent
 *****************************************************************************/
/*!
 * \brief         Add an event to the permanent memory.
 *
 * \details       Add an event to the permanent memory. Set the event to 'active '
 *                and 'visible' if it's WIR-bit is qualified.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_PermanentFillUpFromPrimary
 *****************************************************************************/
/*!
 * \brief         Fills up the permanent memory after healing some entries
 *
 * \details       This function checks for OBD relevant DTCs that currently
 *                trigger the MIL but are not stored in permanent memory. Up to
 *                all empty permanent slots are filled with such events.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromPrimary(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_PermanentFillUpFromConfirmedChronology
 *****************************************************************************/
/*!
 * \brief         Fill up the permanent memory from entries of the 
 *                confirmed chronology.
 *
 * \details       Fill up the permanent memory from entries of the 
 *                confirmed chronology.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \return        E_OK
 *                The permanent memory is completly filled.
 *
 * \return        E_NOT_OK
 *                The permanent memory is not completly filled.
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromConfirmedChronology(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyEventStored
 *****************************************************************************/
/*!
 * \brief         Test if event is already stored in confirmed chronology.
 *
 * \details       Test if event is already stored in confirmed chronology.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyEventStored(
  CONST(Dem_EventIdType, AUTOMATIC)  Event
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronoFreeEntry
 *****************************************************************************/
/*!
 * \brief         Frees the entry in confirmed chronology at forwarded index position
 *
 * \details       Move all entries that are newer than the entry to delete 
 *                one step forward in the chronology array until the entry
 *                at the forwarded index position is overwritten.
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEntry(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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
 * \defgroup Dem_MemPermanent_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyInit
 *****************************************************************************/
/*!
 * \brief         Initialize complete confirmed chronology with 'invalid event id'
 *
 * \details       Initialize complete confimred chronology with 'invalid event id'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyInit(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyRestore
 *****************************************************************************/
/*!
 * \brief         Initialize and validates confirmed chronology of permanent memory
 *
 * \details       Initialize current size of chronology and removes entries in 
 *                chronology belonging to events that do not belong to primary 
 *                memory anymore or do not have the 'Confirmed Bit' set.
 *
 * \param[in]     -
 *
 * \pre           Initialization and restoration of event status at 
 *                Dem initialization is done.
 *
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyRestore(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronoFreeEvent
 *****************************************************************************/
/*!
 * \brief         Frees the entry in confirmed chronology for the event
 *
 * \details       Move all entries that are newer than the entry to delete 
 *                one step forward in the chronology array until the entry
 *                with the forwarded event is overwritten.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronoAddEvent
 *****************************************************************************/
/*!
 * \brief         Add an event to confirmed chronology
 *
 * \details       Add an event to confirmed chronology.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 * \param[in]     SearchExistingEvent
 *                TRUE  Add the event only if there is no existing entry
 *                FALSE Add the event unconditionally
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  ConfirmedEvent,
  CONST(boolean, AUTOMATIC) SearchExistingEvent
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_FillUp
 *****************************************************************************/
/*!
 * \brief         Fills up the permanent memory after healing some entries
 *
 * \details       This function checks for OBD relevant DTCs that currently
 *                trigger the MIL but are not stored in permanent memory. Up to
 *                all empty permanent slots are filled with such events.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_FillUp(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMPERMANENT_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemPermanent_Interface.h
 *********************************************************************************************************************/
