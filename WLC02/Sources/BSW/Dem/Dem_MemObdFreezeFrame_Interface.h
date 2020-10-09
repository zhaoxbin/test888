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
 *  \defgroup   Dem_MemObdFreezeFrame Dem_MemObdFreezeFrame
 *  \{
 *  \file       Dem_MemObdFreezeFrame_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the Obd Freeze Frame Memory subcomponent which manages storage and erasing of the 
 *              legislative Obd Freeze Frame
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

#if !defined (DEM_MEMOBDFREEZEFRAME_INTERFACE_H)
#define DEM_MEMOBDFREEZEFRAME_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemObdFreezeFrame_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MemObdFreezeFrame_Properties Properties
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_FreezeFrameGetVisibility
*****************************************************************************/
/*!
* \brief         Get the state of the visibility flag of the freeze frame at
*                position 'Index'.
*
* \details       Get the state of the visibility flag of the freeze frame at
*                position 'Index'.
*
* \param[in]     Index
*                Index of the freeze frame
*
* \return        The visibility flag of the freeze frame
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*                && DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameGetVisibility(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_FreezeFrameSetVisibility
*****************************************************************************/
/*!
* \brief         Set the state of the visibility flag of the freeze frame at
*                position 'Index'.
*
* \details       Set the state of the visibility flag of the freeze frame at
*                position 'Index'.
*
* \param[in]     Index
*                Index of the freeze frame
* \param[in]     Visible
*                TRUE: Set the visibility flag of the freeze frame entry
*                FALSE: Reset the visibility flag of the freeze frame entry
*
* \return        The stored EventId of the freeze frame
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(boolean, AUTOMATIC)  Visible
  );                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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
 * \defgroup Dem_MemObdFreezeFrame_Private Private Methods
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_SelectNewestLowPrioFF
*****************************************************************************/
/*!
* \brief         Selects the index of the newest Obd freeze frame with low prio 
*                readiness group
*
* \details       If there are multiple low prio Obd freeze frames stored 
*                select the one with most recent timestamp
*
* \param[in]     SelectVisible
*                TRUE:  Select newest low prio visible freeze frame
*                FALSE: Select newest low prio invisible freeze frame
*
* \return        Freeze Frame Index of the event if found, otherwise
*                Dem_Cfg_GlobalObdIIFFCount()
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(
  CONST(boolean, AUTOMATIC)  SelectVisible
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_GetEventOfObdFF
*****************************************************************************/
/*!
* \brief         Get the stored EventId of the freeze frame at position
*                'Index'.
*
* \details       If the given slot is occupied, returns the event Id
*                otherwise returns the invalid event Id
*
* \param[in]     Index
*                Index of the freeze frame
*
* \return        The stored EventId of the freeze frame
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemObdFreezeFrame_GetEventOfObdFF(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_FreezeFrameTestVisible
*****************************************************************************/
/*!
* \brief         Tests whether a given freeze frame slot contains a visible
*                freeze frame
*
* \details       Tests whether a given freeze frame slot contains a visible
*                freeze frame
*
* \param[in]     Index
*                Index of the freeze frame
* \return        TRUE: Freeze frame stored at index is visible
*                FALSE: Freeze frame stored at index is not visible
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameTestVisible(
  CONST(uint8, AUTOMATIC) Index
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
 * \defgroup Dem_MemObdFreezeFrame_Public Public Methods
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_SelectFFDisplaceIndex
*****************************************************************************/
/*!
* \brief         Selects Obd freeze frame index for displacement
*
* \details       Selects lowest prior Obd freeze frame index for displacement.
*                If no less prior entry than Event Id is found,
*                an invalid index is returned
*
* \param[in]     EventId
*                EventId of the freeze frame that needs to be stored
* \param[in]     DisplacePendingFreezeFrame
*                TRUE: trigger and configuration for displacing a pending 
*                      freeze frame is given
*                FALSE: displacing pending freeze frames with confirmed is
*                       either excluded by configuration or the trigger is not
*                       confirmed
*
* \return        Index of the freeze frame to displace if found, otherwise
*                Dem_Cfg_GlobalObdIIFFCount()
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectFFDisplaceIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  DisplacePendingFreezeFrame
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame
*****************************************************************************/
/*!
* \brief         Selects the freeze frame to be reported in Obd mode 02
*
* \details       Selects the oldest freeze frame of a misfire or fuel system 
*                monitor if available, otherwise selects the oldest visible 
*                freeze frame
*
* \return        Index of the freeze frame to display in mode 02, if no 
*                candidate is found, return Dem_Cfg_GlobalObdIIFFCount()
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_FreezeFrameSetVisible
*****************************************************************************/
/*!
* \brief         Marks a given freeze frame slot as visible
*
* \details       Marks a given freeze frame slot as visible
*
* \param[in]     Index
*                Index of the freeze frame
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisible(
CONST(uint8, AUTOMATIC)  Index
);                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_FreezeFrameResetVisible
*****************************************************************************/
/*!
* \brief         Marks a given freeze frame slot as not visible
*
* \details       Marks a given freeze frame slot as not visible
*
* \param[in]     Index
*                Index of the freeze frame
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameResetVisible(
  CONST(uint8, AUTOMATIC)  Index
  );                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_FreezeFrameFreeEntry
*****************************************************************************/
/*!
* \brief         Marks freeze frame entry as unused
*
* \details       Reset eventId of a freeze frame entry
*
* \param[in]     Index
*                Index of the freeze frame
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(
  CONST(uint8, AUTOMATIC) Index
  );                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_MemObdFreezeFrame_SetFFOfEventVisible
*****************************************************************************/
/*!
* \brief         Marks a freeze frame slot related to an event as visible
*
* \details       Searches for a freeze frame slot related to the EventId
*                and marks it as visible
*
* \param[in]     EventId
*                Unique handle of the Event
*
* \pre           -
* \config        DEM_CFG_SUPPORT_OBDII == STD_ON
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_SetFFOfEventVisible(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMOBDFREEZEFRAME_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemObdFreezeFrame_Interface.h
 *********************************************************************************************************************/
