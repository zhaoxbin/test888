/* *********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------------------------------------------------
 */
/*!
 *  \ingroup    Dem_DtrIF
 *  \defgroup   Dem_MidLookup Mid/TID Lookup
 *  \{
 *  \file       Dem_MidLookup_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of MidLookup subcomponent
 *********************************************************************************************************************/

/* *********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
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
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 **********************************************************************************************************************/

#if !defined (DEM_MIDLOOKUP_INTERFACE_H)
#define DEM_MIDLOOKUP_INTERFACE_H


/* *********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_MidLookup_Types.h"
#include "Dem_Dtr_Types.h"
/* ------------------------------------------------------------------------- */


#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
/*!
 * \defgroup Dem_MidLookup_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetMidValue
 *****************************************************************************/
/*!
 * \brief         Get the Mid value for the Mid Index.
 *
 * \details       Get the Mid value for the Mid Index.
 *
 * \param[in]     MidHandle
 *                The Mid Index must be in range [0..NumberOfMids-1[.
 *
 * \return        Mid value for the Mid Index.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetMidTidValue
 *****************************************************************************/
/*!
 * \brief         Get the Tid value for the Mid Index.
 *
 * \details       Get the Tid value for the Mid Index.
 *
 * \param[in]     MidHandle
 *                The Mid Index must be in range [0..NumberOfMids-1[.
 *
 * \return        Tid value for the Mid Index.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidTidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetMidDtrId
 *****************************************************************************/
/*!
 * \brief         Get the Dtr Id for the Mid Index.
 *
 * \details       Get the Dtr Id for the Mid Index.
 *
 * \param[in]     MidHandle
 *                The Mid Index must be in range [0..NumberOfMids-1[.
 *
 * \return        Dtr Id for the Mid Index.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_GetMidDtrId(
  CONST(uint16, AUTOMATIC) MidHandle
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element.
 *
 * \details       Test if the iterator points to a valid element.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Cfg_MidIterGet() will return a valid element on this iterator
 * \return        FALSE
 *                Dem_Cfg_MidIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized.
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_MidIterExists(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator.
 *
 * \details       Get the element pointed to by the iterator.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to MID descriptor table
 *
 * \pre           IterPtr has been initialized.
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_MidIterGet(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator.
 *
 * \details       Initializes the iterator to enumerate MIDs.
 *
 * \param[in]     MidTableStartIndex
 *                StartIndex in MidTable
 *                The MidTableStartIndex must be in range [0..NumberOfMids-1[.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterInit(
  CONST(uint16, AUTOMATIC) MidTableStartIndex,
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
);
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_MidIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element.
 *
 * \details       Move the iterator to the next element.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized.
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterNext(
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_TestAvailabilityMid
 *****************************************************************************/
/*!
 * \brief         Tests if input Mid is an availability Mid.
 *
 * \details       Tests if input Mid is an availability Mid.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        True: Input Mid is an availability Mid.
 *                False: Input Mid is not an availability Mid.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestAvailabilityMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidIndexOfMid
 *****************************************************************************/
/*!
 * \brief         Get the index of a supported Mid based on a Mid.
 *
 * \details       Get the index of a supported Mid based on a Mid.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        The SupportedMid index
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidIndexOfMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidBitPositionOfMid
 *****************************************************************************/
/*!
 * \brief         Get bit position of a Mid within the supported Mid mask.
 *
 * \details       Get bit position of a Mid within the supported Mid mask.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        The bit position within the supported Mid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidBitPositionOfMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetInitialSupportedMidMask
 *****************************************************************************/
/*!
 * \brief         Get the initial 'Supported Mid mask' of MID.
 *
 * \details       Get the initial 'Supported Mid mask' of MID.
 *
 * \param[in]     SupportedMidIndex
 *                SupportedMidIndex must be in range [0..DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS[.
 *
 * \return        The initial 'Supported Mid Mask'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetInitialSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidMask
 *****************************************************************************/
/*!
 * \brief         Get the current 'Supported Mid Mask' of MID.
 *
 * \details       Get the current 'Supported Mid Mask' of MID.
 *
 * \param[in]     SupportedMidIndex
 *                SupportedMidIndex must be in range [0..DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS[.
 *
 * \return        The current 'Supported Mid Mask'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_SetSupportedMidMask
 *****************************************************************************/
/*!
 * \brief         Set the current 'Supported Mid Mask' of MIDs.
 *
 * \details       Set the current 'Supported Mid Mask' of MIDs.
 *
 * \param[in]     SupportedMidIndex
 *                SupportedMidIndex must be in range [0..DEM_DTR_MAX_NUMBER_SUPPORTED_MID_MASKS[.
 * \param[in]     SupportedMidValue
 *                The new 'Supported Mid Mask'.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex,
  CONST(uint32, AUTOMATIC) SupportedMidValue
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_TestVisibilityChanged
 *****************************************************************************/
/*!
 * \brief         Get the 'Visibility Changed' flag.
 *
 * \details       Get the 'Visibility Changed' flag.
 *
 * \return        The 'Visibility Changed' flag.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestVisibilityChanged(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_SetVisibilityChanged
 *****************************************************************************/
/*!
 * \brief         Set the 'Visibility Changed' flag.
 *
 * \details       Set the 'Visibility Changed' flag.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetVisibilityChanged(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_ResetVisibilityChanged
 *****************************************************************************/
/*!
 * \brief         Reset the 'Visibility Changed' flag.
 *
 * \details       Reset the 'Visibility Changed' flag.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_ResetVisibilityChanged(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_MidLookup_IsMidSupported
 *****************************************************************************/
/*!
 * \brief         Tests whether a Mid is supported.
 *
 * \details       Tests whether a Mid is supported.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        TRUE
 *                The Mid is supported
 * \return        FALSE
 *                The Mid is not supported
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsMidSupported(
  CONST(uint8, AUTOMATIC)  Mid
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_FindHandleOfMid
 *****************************************************************************/
/*!
 * \brief         Returns the handle into the configuration table of the Mid.
 *
 * \details       Returns the handle into the configuration table of the Mid.
 *
 * \param[in]     Mid
 *                Mid value
 *
 * \return        The Mid handle
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MidLookup_FindHandleOfMid(
  CONST(uint8, AUTOMATIC) Mid
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* *********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 **********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MidLookup_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MidLookup_Init
 *****************************************************************************/
/*!
 * \brief         Initializes MidLookup functionality.
 *
 * \details       This function controls initialization of the MidLookup
 *                subcomponent.
 *
 * \pre           May only be called during initialization.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_Init(
  void
  );

/* ****************************************************************************
 * Dem_MidLookup_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-initializes MidLookup.
 *
 * \details       This function performs basic initialization to allow later
 *                full initialization.
 *
 * \pre           May only be called during pre-initialization.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_MidLookup_UpdateMidVisibility
 *****************************************************************************/
/*!
 * \brief         Requests the immediate update of the available OBD MIDs.
 *
 * \details       As the visibility status of Dtrs can change during runtime
 *                and therefore MIDs might also not be visible anymore
 *                the application can trigger the update of the available
 *                OBD MIDs.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_UpdateMidVisibility(
  void
  );

/* ****************************************************************************
 * Dem_MidLookup_NotifyVisibilityChanged()
 *****************************************************************************/
/*!
 * \brief         Notification to report a change in visibility.
 *
 * \details       If the visibility is reported changed, the next request
 *                to read supported Mids will recalculate the supported Mids
 *                automatically. The process can be started immediate with
 *                \see Dem_MidLookup_UpdateMidVisibility.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_NotifyVisibilityChanged(
  void
  );

/* ****************************************************************************
 * Dem_MidLookup_IsSupportedMid
 *****************************************************************************/
/*!
 * \brief         Check if a Mid is a supported Mid.
 *
 * \details       Check if a Mid is a supported Mid, i.e. 0x00, 0x20, 0x40....
 *
 * \param[in]     Mid
 *                MonitorId to check
 *
 * \return        TRUE
 *                MonitorId is a supported Mid
 * \return        TRUE
 *                MonitorId is not supported Mid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsSupportedMid(
  CONST(uint8, AUTOMATIC)  Mid
  );

/* ****************************************************************************
 * Dem_MidLookup_GetSupportedMidValue
 *****************************************************************************/
/*!
 * \brief         Get the SupportedMidMask of a Mid.
 *
 * \details       Get the SupportedMidMask of a Mid. This will recalculate the
 *                Mid Visibility if changes are pending.
 *
 * \param[in]     Mid
 *                Requested MonitorId. This will return the value of
 *                the supported Mid Mask corresponding to the passed MonitorId.
 *
 * \return        Supported Mid Mask
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidValue(
  CONST(uint8, AUTOMATIC)  Mid
  );

/* ****************************************************************************
 * Dem_MidLookup_GetTidCountOfMid
 *****************************************************************************/
/*!
 * \brief         Get the number of available TIDs for a MID.
 *
 * \details       Get the number of available TIDs for a MID.
 *
 * \param[in]     Mid
 *                MonitorId
 * \param[out]    TidCount
 *                Number of available Tids for the requested Mid
 *
 * \return        E_OK
 *                DTR data was successfully copied
 * \return        E_NOT_OK
 *                DTR data was not copied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MidLookup_GetTidCountOfMid(
  CONST(uint8, AUTOMATIC)  Mid,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  TidCount
  );

/* ****************************************************************************
 * Dem_MidLookup_FindDtrId
 *****************************************************************************/
/*!
 * \brief         Get the DTR handle for a OBDMID / TID combination.
 *
 * \details       Returns the DTR handle for a OBDMID / TID combination.
 *
 * \param[in]     Mid
 *                Mid number
 * \param[in]     TidIndex
 *                Zero based index of the requested Tid
 * \param[out]    Tid
 *                Tid number of the selected Tid
 *
 * \return        The DTR handle requested. The handle is invalid if the Mid/Tid
 *                combination does not exist.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_FindDtrId(
  CONST(uint8, AUTOMATIC) Mid,
  CONST(uint8, AUTOMATIC) TidIndex,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)  Tid
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MIDLOOKUP_INTERFACE_H */

/*!
 * \}
 */
/* *********************************************************************************************************************
 *  END OF FILE: Dem_MidLookup_Declarations.h
 **********************************************************************************************************************/
