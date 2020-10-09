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
/*! \addtogroup Dem_UDSStatus
 *  \{
 *  \file       Dem_UDSStatus_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of EventUDSStatus subcomponent
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

#if !defined (DEM_EVENTUDSSTATUS_IMPLEMENTATION_H)
#define DEM_EVENTUDSSTATUS_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_UDSStatus_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

 /*!
 * \defgroup  Dem_UdsStatusClearMask  Macros encoding status masks to reset UDS status bits
 * Macros encoding status masks to reset UDS status bits
 * \{
 */
#define DEM_UDS_STATUS_TF_MASK                   DEM_BIT_MASK(0, DEM_1BYTE)  /*!< Byte mask to reset test failed */
#define DEM_UDS_STATUS_TFTOC_MASK                DEM_BIT_MASK(1, DEM_1BYTE)  /*!< Byte mask to reset test failed this operating cycle*/
#define DEM_UDS_STATUS_PDTC_MASK                 DEM_BIT_MASK(2, DEM_1BYTE)  /*!< Byte mask to reset pending dtc */
#define DEM_UDS_STATUS_CDTC_MASK                 DEM_BIT_MASK(3, DEM_1BYTE)  /*!< Byte mask to reset confirmed dtc */
#define DEM_UDS_STATUS_TNCSLC_MASK               DEM_BIT_MASK(4, DEM_1BYTE)  /*!< Byte mask to reset test not completed since last clear */
#define DEM_UDS_STATUS_TFSLC_MASK                DEM_BIT_MASK(5, DEM_1BYTE)  /*!< Byte mask to reset test failed since last clear */
#define DEM_UDS_STATUS_TNCTOC_MASK               DEM_BIT_MASK(6, DEM_1BYTE)  /*!< Byte mask to reset test not completed this operating cycle */
#define DEM_UDS_STATUS_WIR_MASK                  DEM_BIT_MASK(7, DEM_1BYTE)  /*!< Byte mask to reset warning indicator requested */
/*!
 * \}
 */

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
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_UDSStatus_Properties
 * \{
 */

 /* ****************************************************************************
 % Dem_UDSStatus_Test_TF()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TF) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TF()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TF);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TF()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TF_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TFTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TFTOC) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TFTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TFTOC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TFTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TFTOC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_PDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_PDTC) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_PDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_PDTC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_PDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_PDTC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_CDTC) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_CDTC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_CDTC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TNCSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCSLC(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TNCSLC) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TNCSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCSLC(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TNCSLC);
}
 

/* ****************************************************************************
 % DemDem_UDSStatus_Reset_TNCSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TNCSLC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TFSLC(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TFSLC) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TFSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TFSLC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TFSLC(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TFSLC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TNCTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TNCTOC) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TNCTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TNCTOC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TNCTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TNCTOC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_WIR) != 0);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_WIR);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_WIR(
CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
)
{
  return (Dem_UDSStatus_Type)((Status)& DEM_UDS_STATUS_WIR_MASK);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_UDSStatus_Public
 * \{
 */

/* ****************************************************************************
 % Dem_UDSStatus_IsNvRelevantStatusChange
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_IsNvRelevantStatusChange(
  CONST(uint8, AUTOMATIC)  OldEventStatus,
  CONST(uint8, AUTOMATIC)  NewEventStatus
  )
{
  boolean returnValue;

#if (DEM_CFG_USE_NVM == STD_OFF)                                                                                                 /* PRQA S 0883 */ /* MD_DEM_19.15 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OldEventStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NewEventStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */

  returnValue = FALSE;
#elif (DEM_CFG_SUPPORT_TESTFAILED_STORAGE == STD_ON)
  returnValue = (boolean)(OldEventStatus != NewEventStatus);
#else
   /* Ignore TF bit */
  returnValue = (boolean)(((OldEventStatus ^ NewEventStatus) & DEM_UDS_STATUS_TF_MASK) != 0);
#endif

  return returnValue;
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_EVENTUDSSTATUS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_UDSStatus_Implementation.h
 *********************************************************************************************************************/
