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
/*! \addtogroup Dem_ExtDataElementIF
 *  \{
 *  \file       Dem_ExtDataElementIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_EXTDATAELEMENTIF_IMPLEMENTATION_H)
#define DEM_EXTDATAELEMENTIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtDataElementIF_Interface.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Cfg_Definitions.h"
#include "Dem_Error_Implementation.h"

#include "Dem_Data_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                  /* Subcomponents callbacks */
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_CONST_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_STOP_SEC_CONST_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_ExtDataElementIF_Properties
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_ExtDataElementIF_Private
 * \{
 */
#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectUserData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectUserData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || ((Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_CBK)
    && (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_UINT8_N))
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16 lDataSize;
    uint16 lWriteIndex;
    lDataSize = Dem_Cfg_DataSize(DataIndex);
    lWriteIndex = DestinationBuffer->WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, lDataSize) == E_OK)                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      if ((*((Dem_ReadDataStandardFPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(                                                     /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_DESTINATIONBUFFER */
        &DestinationBuffer->Buffer[lWriteIndex]) != E_OK)
      { /* In case the function failed, fill with padding bytes */
        Dem_MemSet(&DestinationBuffer->Buffer[lWriteIndex],                                                                      /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_DESTINATIONBUFFER */
          DEM_EXTDATAELEMENTIF_INVALID_DATA_PATTERN,
          lDataSize);                                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }      
    }
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectCSDataWithEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectCSDataWithEventId(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_CBK_WITH_EVENTID)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16 lDataSize;
    uint16 lWriteIndex;
    lDataSize = Dem_Cfg_DataSize(DataIndex);
    lWriteIndex = DestinationBuffer->WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, lDataSize) == E_OK)                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      if ((*((Dem_ReadDataExtendedFPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(                                                     /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_DESTINATIONBUFFER */
        EventId,
        &DestinationBuffer->Buffer[lWriteIndex]) != E_OK)
      { /* In case the function failed, fill with padding bytes */
        Dem_MemSet(&DestinationBuffer->Buffer[lWriteIndex],                                                                      /* PRQA S 0602 */ /* MD_DEM_20.2 */  /* SBSW_DEM_MEMSET_DESTINATIONBUFFER */
          DEM_EXTDATAELEMENTIF_INVALID_DATA_PATTERN,
          lDataSize);                                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }
    }
  }  
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Boolean
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Boolean(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN)
    || (Dem_Cfg_DataSize(DataIndex) > 1)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    boolean lDataAppl;
    uint8 lData;

    if ((*((Dem_ReadDataSRBooleanFPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lDataAppl) != E_OK)                                  /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = DEM_EXTDATAELEMENTIF_INVALID_DATA_1Byte;
    }
    else
    {
      lData = (uint8)lDataAppl;
    }

    Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, lData);                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }  
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Sint8
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Sint8(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_SINT8)
    || (Dem_Cfg_DataSize(DataIndex) > 1)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    sint8 lData;
    
    if ((*((Dem_ReadDataSRSint8FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                        /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = (sint8)DEM_EXTDATAELEMENTIF_INVALID_DATA_SIGNED;
    }
    Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, (uint8)lData);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* PRQA S 0291 */ /* MD_DEM_21.1_Always_Serialization */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Uint8
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Uint8(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_UINT8)
    || (Dem_Cfg_DataSize(DataIndex) > 1)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint8 lData;

    if ((*((Dem_ReadDataStandardFPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = DEM_EXTDATAELEMENTIF_INVALID_DATA_1Byte;
    }
    Dem_Data_WriteDestinationBufferUint8(DestinationBuffer, lData);                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Sint16
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Sint16(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_SINT16)
    || (Dem_Cfg_DataSize(DataIndex) > 2)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    sint16 lData;
    if ((*((Dem_ReadDataSRSint16FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = (sint16)DEM_EXTDATAELEMENTIF_INVALID_DATA_SIGNED;
    }
    Dem_Data_WriteDestinationBufferUint16(DestinationBuffer, (uint16)lData);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* PRQA S 0291 */ /* MD_DEM_21.1_Always_Serialization */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Sint16_Intel
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Sint16_Intel(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL)
    || (Dem_Cfg_DataSize(DataIndex) > 2)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    sint16 lData;

    if ((*((Dem_ReadDataSRSint16FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = (sint16)DEM_EXTDATAELEMENTIF_INVALID_DATA_SIGNED;
    }
    Dem_Data_WriteDestinationBufferUint16_Intel(DestinationBuffer, (uint16)lData);                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* PRQA S 0291 */ /* MD_DEM_21.1_Always_Serialization */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Uint16
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Uint16(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_UINT16)
    || (Dem_Cfg_DataSize(DataIndex) > 2)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16 lData;

    if ((*((Dem_ReadDataSRUint16FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = DEM_EXTDATAELEMENTIF_INVALID_DATA_2Byte;
    }
    Dem_Data_WriteDestinationBufferUint16(DestinationBuffer, lData);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Uint16_Intel
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Uint16_Intel(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL)
    || (Dem_Cfg_DataSize(DataIndex) > 2)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16 lData;

    if ((*((Dem_ReadDataSRUint16FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = DEM_EXTDATAELEMENTIF_INVALID_DATA_2Byte;
    }
    Dem_Data_WriteDestinationBufferUint16_Intel(DestinationBuffer, lData);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Sint32
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Sint32(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_SINT32)
    || (Dem_Cfg_DataSize(DataIndex) > 4)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    sint32 lData;

    if ((*((Dem_ReadDataSRSint32FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = (sint32)DEM_EXTDATAELEMENTIF_INVALID_DATA_SIGNED;
    }
    Dem_Data_WriteDestinationBufferUint32(DestinationBuffer, (uint32)lData);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* PRQA S 0291 */ /* MD_DEM_21.1_Always_Serialization */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Sint32_Intel
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Sint32_Intel(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL)
    || (Dem_Cfg_DataSize(DataIndex) > 4)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    sint32 lData;

    if ((*((Dem_ReadDataSRSint32FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = (sint32)DEM_EXTDATAELEMENTIF_INVALID_DATA_SIGNED;
    }
    Dem_Data_WriteDestinationBufferUint32_Intel(DestinationBuffer, (uint32)lData);                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* PRQA S 0291 */ /* MD_DEM_21.1_Always_Serialization */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Uint32
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Uint32(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_UINT32)
    || (Dem_Cfg_DataSize(DataIndex) > 4)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint32 lData;

    if ((*((Dem_ReadDataSRUint32FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = DEM_EXTDATAELEMENTIF_INVALID_DATA_4Byte;
    }
    Dem_Data_WriteDestinationBufferUint32(DestinationBuffer, lData);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Uint32_Intel
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Uint32_Intel(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL)
    || (Dem_Cfg_DataSize(DataIndex) > 4)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint32 lData;

    if ((*((Dem_ReadDataSRUint32FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(&lData) != E_OK)                                       /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
    { /* In case the function failed, fill with padding bytes */
      lData = DEM_EXTDATAELEMENTIF_INVALID_DATA_4Byte;
    }
    Dem_Data_WriteDestinationBufferUint32_Intel(DestinationBuffer, lData);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectSRData_Sint8_N
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectSRData_Sint8_N(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((DataIndex >= Dem_Cfg_GlobalDataElementCount())                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataCallbackType(DataIndex) != DEM_CFG_DATA_FROM_SR_PORT_SINT8_N)
    || (Dem_Cfg_DataCbkRead(DataIndex) == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16 lDataSize;
    uint16 lWriteIndex;
    lDataSize = Dem_Cfg_DataSize(DataIndex);
    lWriteIndex = DestinationBuffer->WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, lDataSize) == E_OK)                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      if ((*((Dem_ReadDataSRSint8FPtrType)Dem_Cfg_DataCbkRead(DataIndex)))(                                                      /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_DESTINATIONBUFFER */
        (Dem_SignedNvDataPtrType)(&DestinationBuffer->Buffer[lWriteIndex])) != E_OK)                                             /* PRQA S 0310 */ /* MD_DEM_11.4_sr */
      { /* In case the function failed, fill with padding bytes */
        Dem_MemSet(&DestinationBuffer->Buffer[lWriteIndex],                                                                      /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_DESTINATIONBUFFER */
          DEM_DATASTORAGEIF_INVALID_DATA_PATTERN,
          lDataSize);                                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
      }
    }
  }
}
#endif

#if ( ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   ||   (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   ||   (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) ) \
   && (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON) )
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectRootCauseEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectRootCauseEventId(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Data_WriteDestinationBufferUint16(DestinationBuffer, EventId);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}
#endif


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_ExtDataElementIF_Public
 * \{
 */
#if ( (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) \
   || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) )
/* ****************************************************************************
% Dem_ExtDataElementIF_InitCollectDidInfo
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_InitCollectDidInfo(
  CONST(Dem_ExtDataElementIF_CollectDidInfoPtrType, AUTOMATIC)  CollectDidInfoPtr,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  CollectDidInfoPtr->MemoryEntryId = DEM_MEMORYENTRY_HANDLE_INVALID;                                                             /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
  CollectDidInfoPtr->SourceBuffer = (Dem_ConstSharedDataPtrType)NULL_PTR;                                                        /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */                   
  CollectDidInfoPtr->DestinationBuffer = DestinationBuffer;                                                                      /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
  CollectDidInfoPtr->EventId = EventId;                                                                                          /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
  CollectDidInfoPtr->ReadIndex = 0;                                                                                              /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
}
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) )
/* ****************************************************************************
% Dem_ExtDataElementIF_CollectDataElement
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ExtDataElementIF_CollectDataElement(
CONST(Dem_ExtDataElementIF_CollectDidInfoPtrType, AUTOMATIC)  CollectDidInfoPtr,                                                 /* PRQA S 3673 */ /* MD_DEM_16.7_Design */
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  boolean lReturnValue;

  lReturnValue = TRUE;

  switch (Dem_Cfg_DataCallbackType(DataIndex))
  {
  case DEM_CFG_DATA_FROM_CBK:
  case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
    Dem_ExtDataElementIF_CollectUserData(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
    Dem_ExtDataElementIF_CollectCSDataWithEventId(CollectDidInfoPtr->DestinationBuffer, DataIndex, CollectDidInfoPtr->EventId);  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
    Dem_ExtDataElementIF_CollectSRData_Boolean(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
    Dem_ExtDataElementIF_CollectSRData_Sint8(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
    Dem_ExtDataElementIF_CollectSRData_Uint8(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
    Dem_ExtDataElementIF_CollectSRData_Sint16(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
    Dem_ExtDataElementIF_CollectSRData_Sint16_Intel(CollectDidInfoPtr->DestinationBuffer, DataIndex);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
    Dem_ExtDataElementIF_CollectSRData_Uint16(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
    Dem_ExtDataElementIF_CollectSRData_Uint16_Intel(CollectDidInfoPtr->DestinationBuffer, DataIndex);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
    Dem_ExtDataElementIF_CollectSRData_Sint32(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
    Dem_ExtDataElementIF_CollectSRData_Sint32_Intel(CollectDidInfoPtr->DestinationBuffer, DataIndex);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
    Dem_ExtDataElementIF_CollectSRData_Uint32(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
    Dem_ExtDataElementIF_CollectSRData_Uint32_Intel(CollectDidInfoPtr->DestinationBuffer, DataIndex);                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
    Dem_ExtDataElementIF_CollectSRData_Sint8_N(CollectDidInfoPtr->DestinationBuffer, DataIndex);                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

# if (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON)
  case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
    Dem_ExtDataElementIF_CollectRootCauseEventId(CollectDidInfoPtr->DestinationBuffer, CollectDidInfoPtr->EventId);              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;
# endif

  default:
    lReturnValue = FALSE;
    break;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) \
   || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_ExtDataElementIF_CollectStoredDid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_CollectStoredDid(
  CONST(Dem_ExtDataElementIF_CollectDidInfoPtrType, AUTOMATIC)  CollectDidInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  Dem_Cfg_DidDataIterType lDataIter;

  /* Each DID consists of 1-* data elements. */
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;

    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      (void) Dem_ExtDataElementIF_CollectDataElement(CollectDidInfoPtr, lDataIndex);                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_ExtDataElementIF_DagGetCurrentOdometer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_DagGetCurrentOdometer(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint32 lPreciseOdometer;
  Std_ReturnType lReturnValue;
  Dem_OemCbkGetCurrentOdometerFptrType Dem_OemGetCurrentOdometerCbk;

  Dem_OemGetCurrentOdometerCbk = Dem_Cfg_OemCbkGetCurrentOdometer();
  if (Dem_OemGetCurrentOdometerCbk != NULL_PTR)
  {
    /* receives bussed odometer in unit 0.1km per bit */ 
    lReturnValue = (*Dem_OemGetCurrentOdometerCbk)(&lPreciseOdometer);                                                           /* SBSW_DEM_GETCURRENTODOMETER_FPTR */
  }
  else
  {
    /* Set the odometer value as invalid */
    lPreciseOdometer = 0x00FFFFFFuL;
    lReturnValue = E_NOT_OK;
  }

  if ( (lReturnValue != E_OK)
    || (lPreciseOdometer == 0x00FFFFFFuL) )
  {
    /* signal invalid */
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER, 0xFFU);
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER + 1, 0xFFU);
  }
  else
  if (lPreciseOdometer == 0x00FFFFFEuL)
  {
    /* signal unavailable */
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER, 0xFFU);
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER + 1, 0xFEU);
  }
  else
  {
    uint16 lScaledOdometer;
    /* Conversion from bussed odometer value to internal odometer is divide by 160 (=0xA0). */
    /* The cast to uint16 is taken directly from the specification */
    lScaledOdometer = (uint16)((lPreciseOdometer / 0xA0uL) & 0x0000FFFFuL);

    if (lScaledOdometer > 0xFFFDu)
    {
      lScaledOdometer = 0xFFFDu;
    }
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER, Dem_GetHiByte(lScaledOdometer));
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER + 1, Dem_GetLoByte(lScaledOdometer));
  }
}
#endif

#if (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_ExtDataElementIF_DagGetOperatingTime
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_DagGetOperatingTime(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint32 lOperatingTime;
  uint8 lOperatingTimeStatus;

# if (DEM_CFG_USE_OHDS == STD_ON)
  if (OHDS_Dem_GetOperatingHours(&lOperatingTime, &lOperatingTimeStatus) != E_OK)                                                /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
  {
    lOperatingTime = 0xffffffffU;
    lOperatingTimeStatus = 0xff;
  }

  Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_TIME, Dem_GetHiHiByte(lOperatingTime));
  Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_TIME + 1, Dem_GetHiLoByte(lOperatingTime));
  Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_TIME + 2, Dem_GetLoHiByte(lOperatingTime));
  Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_TIME + 3, Dem_GetLoLoByte(lOperatingTime));
  Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_TIMESTATUS, lOperatingTimeStatus);
} /* (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) */
#endif

#if (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_ExtDataElementIF_DagGetExternalTester
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtDataElementIF_DagGetExternalTester(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  Buffer
  )
{
  boolean lTesterPresent;
  Std_ReturnType lReturnValue;
  Dem_OemCbkGetExternalTesterStatusFptrType Dem_OemGetExternalTesterStatusCbk;

  Dem_OemGetExternalTesterStatusCbk = Dem_Cfg_OemCbkGetExternalTesterStatus();
  if (Dem_OemGetExternalTesterStatusCbk != NULL_PTR)
  {
    lReturnValue = (*Dem_OemGetExternalTesterStatusCbk)(&lTesterPresent);                                                        /* SBSW_DEM_OEMEXTERNALTESTERSTATUS_FPTR */
  }
  else
  {
    lTesterPresent = FALSE;
    lReturnValue = E_NOT_OK;
  }

  if (lReturnValue != E_OK)
  { /* assume 'false' was returned. */
    *Buffer = 0x00;                                                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
# if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (lTesterPresent > TRUE)
    {
      Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_DATA);
      *Buffer = 0x00;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
# endif
    {
      *Buffer = lTesterPresent; /* Boolean -> Assume 0x00/0x01 */                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_EXTDATAELEMENTIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtDataElementIF_Implementation.h
 *********************************************************************************************************************/
