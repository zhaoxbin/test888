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
/*! \ingroup    Dem_Event
 *  \defgroup   Dem_UDSStatus EventUDS Status
 *  \{
 *  \file       Dem_UDSStatus_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of EventUDSStatus subcomponent
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

#if !defined (DEM_EVENTUDSSTATUS_INTERFACE_H)
#define DEM_EVENTUDSSTATUS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_UDSStatus_Types.h"
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
 * \defgroup Dem_UDSStatus_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_UDSStatus_Test_TF
 *****************************************************************************/
/*!
 * \brief         Test test failed state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The TF bit is set
 * \return        FALSE
 *                The TF bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_TF
 *****************************************************************************/
/*!
 * \brief         Set test failed state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with TF bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_TF
 *****************************************************************************/
/*!
 * \brief         Reset test failed state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with TF bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_TFTOC
 *****************************************************************************/
/*!
 * \brief         Test test failed this operation cycle state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The TFTOC bit is set
 * \return        FALSE
 *                The TFTOC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_TFTOC
 *****************************************************************************/
/*!
 * \brief         Set test failed this operating cycle state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TFTOC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_TFTOC
 *****************************************************************************/
/*!
 * \brief         Reset test failed this operating cycle state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TFTOC bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_PDTC
 *****************************************************************************/
/*!
 * \brief         Test pending DTC state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The PDTC bit is set
 * \return        FALSE
 *                The PDTC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_PDTC
 *****************************************************************************/
/*!
 * \brief         Set pending DTC state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test PDTC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_PDTC
 *****************************************************************************/
/*!
 * \brief         Reset pending DTC state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test PDTC bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_CDTC
 *****************************************************************************/
/*!
 * \brief         Test confirmed DTC state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The CDTC bit is set
 * \return        FALSE
 *                The CDTC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_CDTC
 *****************************************************************************/
/*!
 * \brief         Set confirmed DTC state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test CDTC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_CDTC
 *****************************************************************************/
/*!
 * \brief         Reset confirmed DTC state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test CDTC bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_TNCSLC
 *****************************************************************************/
/*!
 * \brief         Test test not completed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The TNCSLC bit is set
 * \return        FALSE
 *                The TNCSLC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_TNCSLC
 *****************************************************************************/
/*!
 * \brief         Set test not completed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TNCSLC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_TNCSLC
 *****************************************************************************/
/*!
 * \brief         Reset test not completed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TNCSLC bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_TFSLC
 *****************************************************************************/
/*!
 * \brief         Test test failed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The TFSLC bit is set
 * \return        FALSE
 *                The TFSLC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TFSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_TFSLC
 *****************************************************************************/
/*!
 * \brief         Set test failed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TFSLC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TFSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_TFSLC
 *****************************************************************************/
/*!
 * \brief         Reset test failed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TFSLC bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TFSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_TNCTOC
 *****************************************************************************/
/*!
 * \brief         Test test not completed this operating cycle state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The TNCTOC bit is set
 * \return        FALSE
 *                The TNCTOC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_TNCTOC
 *****************************************************************************/
/*!
 * \brief         Set test not completed this operating cycle state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TNCTOC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_TNCTOC
 *****************************************************************************/
/*!
 * \brief         Reset test not completed this operating cycle state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TNCTOC bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Test_WIR
 *****************************************************************************/
/*!
 * \brief         Test warning indicator requested state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The WIR bit is set
 * \return        FALSE
 *                The WIR bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Set_WIR
 *****************************************************************************/
/*!
 * \brief         Set warning indicator requested state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test WIR bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_UDSStatus_Reset_WIR
 *****************************************************************************/
/*!
 * \brief         Reset warning indicator requested state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test WIR bit reset

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
 
/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_UDSStatus_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_UDSStatus_IsNvRelevantStatusChange
 *****************************************************************************/
/*!
 * \brief         Check, if the status change is relevant to store the NV
 *                event-status memory block
 *
 * \details       Check, if the status change is relevant to store the NV
 *                event-status memory block
 *
 * \param[in]     OldEventStatus
 *                Old event status
 * \param[in]     NewEventStatus
 *                New event status
 *
 * \return        TRUE
 *                Relevant status bit change
 * \return        FALSE
 *                No or not relevant status bit change
 *
 * \pre           With (DEM_CFG_USE_NVM == STD_OFF) the result is always FALSE
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_IsNvRelevantStatusChange(
  CONST(uint8, AUTOMATIC)  OldEventStatus,
  CONST(uint8, AUTOMATIC)  NewEventStatus
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_EVENTUDSSTATUS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_UDSStatus_Interface.h
 *********************************************************************************************************************/
