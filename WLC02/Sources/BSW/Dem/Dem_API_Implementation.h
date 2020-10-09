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
/*! \addtogroup Dem_API
 *  \{
 *  \file       Dem_API_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of API subcomponent
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

#if !defined (DEM_API_IMPLEMENTATION_H)
#define DEM_API_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_API_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Implementation.h"
#include "Dem_InitState_Implementation.h"
#include "Dem_DtrIF_Implementation.h"
#include "Dem_ClientAccess_Implementation.h"
#include "Dem_EventQueue_Implementation.h"
#include "Dem_ClearTask_Implementation.h"
#include "Dem_EnableCondition_Implementation.h"
#include "Dem_StorageCondition_Implementation.h"
#include "Dem_EnvDataSwcApi_Implementation.h"
#include "Dem_Scheduler_Implementation.h"
#include "Dem_Dcm_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_Event_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_DTCReporting_Implementation.h"
#include "Dem_OperationCycle_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_Memory_Implementation.h"
#include "Dem_Prestore_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_Indicator_Implementation.h"
#include "Dem_Statistics_Implementation.h"
#include "Dem_MemObdFreezeFrame_Implementation.h"

                                                   /* subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
/*! Currently active module configuration */
P2CONST(Dem_ConfigType, DEM_VAR_NOINIT, DEM_INIT_DATA)  Dem_GlobalConfigPtr;                                                     /* PRQA S 3406 */ /* MD_DEM_8.5 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_API_Private
 * \{
 */

/* ****************************************************************************
 % Dem_MasterMainFunctionTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionTimer(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
    {
      Dem_Timer_MainFunction();
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_MAINFUNCTION_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}

/* ****************************************************************************
 % Dem_MasterMainFunctionWorker
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
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionWorker(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
    {
      Dem_Scheduler_MainFunction();
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_MAINFUNCTION_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_API_Public
 * \{
 */

                                                   /* Interface EcuM <-> Dem */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_InitMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_InitMemory(
  void
  )
{
  Dem_Satellite_IdType lSatelliteId;
  for (lSatelliteId = 0;
       lSatelliteId < Dem_Cfg_GlobalSatelliteCount();
       ++lSatelliteId)
  {
    Dem_SatelliteCore_MemoryInit(lSatelliteId);
  }

  Dem_InitState_SetInitState(DEM_INITSTATE_UNINITIALIZED);
}

/* ****************************************************************************
 % Dem_MainFunctionTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionTimer(
  void
  )
{
  Dem_MasterMainFunctionTimer();
  Dem_SatelliteMainFunction();
}

/* ****************************************************************************
 % Dem_MainFunctionWorker
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionWorker(
  void
  )
{
  Dem_MasterMainFunctionWorker();
}

/* ****************************************************************************
 % Dem_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MainFunction(
  void
  )
{
  Dem_MainFunctionTimer();
  Dem_MainFunctionWorker();
}

/* ****************************************************************************
 % Dem_SatellitePreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_SatellitePreInit(
  Dem_SatelliteInfoType SatelliteId
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_InitState_TestSatelliteInState(SatelliteId, DEM_INITSTATE_UNINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_SatelliteSat_PreInit(SatelliteId);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SATELLITEPREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}

/* ****************************************************************************
 % Dem_MasterPreInit
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
FUNC(void, DEM_CODE)
Dem_MasterPreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                          /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_UNINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
    if (ConfigPtr == NULL_PTR)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
      EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
# endif
    }
    else
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
    if (Dem_Cfg_InitPtrFinalMagicNumber(ConfigPtr) != DEM_CFG_FINAL_MAGIC_NUMBER)                                                /* SBSW_DEM_POINTER_FORWARD_API */
    {
      EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
    }
    else
    if (Dem_Cfg_InitPtrCompatibilityVersion(ConfigPtr) != DEM_CFG_GEN_COMPATIBILITY_VERSION)                                     /* SBSW_DEM_POINTER_FORWARD_API */
    {
      EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
    }
    else
# endif
#endif
    {
      /* ----- Implementation ---------------------------------------------- */
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
      Dem_GlobalConfigPtr = ConfigPtr;
#endif
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
      Dem_LineOfRuntimeError = 0;
      Dem_FileOfRuntimeError = "";
#endif

      {
        Dem_Satellite_IdType lSatelliteId;
        for (lSatelliteId = 0;
             lSatelliteId < Dem_Cfg_GlobalSatelliteCount();
             ++lSatelliteId)
        {
          Dem_SatelliteCore_MemoryInit(lSatelliteId);
        }
      }
      Dem_Queue_PreInit();
      Dem_EnableCondition_PreInit();
      Dem_StorageCondition_PreInit();
      Dem_OperationCycle_PreInit();
      Dem_Event_PreInit();
      Dem_DTC_PreInit();
      Dem_DtrIF_PreInit();

      /* At this point:
       - BSW error reporting is enabled (Dem_ReportErrorStatus)
       - NvM has write access to RAM buffers (Dem may not access them!) */
      Dem_InitState_SetInitState(DEM_INITSTATE_PREINITIALIZED);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_PREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Cfg_GlobalSatelliteCount() != 1)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_MasterPreInit(ConfigPtr);                                                                                                /* SBSW_DEM_POINTER_FORWARD_API */
    Dem_SatellitePreInit(DEM_SATELLITE_APPLICATION_ZERO);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_PREINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}

/* ****************************************************************************
 % Dem_SatelliteInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_SatelliteInit(
  Dem_SatelliteInfoType  SatelliteId
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_InitState_TestSatelliteInState(SatelliteId, DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_SatelliteSat_Init(SatelliteId);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SATELLITEINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MasterInit
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
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                          /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ( (Dem_InitState_TestMasterInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)                                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestMasterInState(DEM_INITSTATE_SHUTDOWN) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_InitState_TestAllSatellitesAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_CFG_USE_INIT_POINTER == STD_ON)
  if ( (Dem_InitState_TestMasterInState(DEM_INITSTATE_SHUTDOWN) == TRUE)
    && (ConfigPtr != NULL_PTR)
    && (Dem_GlobalConfigPtr != ConfigPtr) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
    if (ConfigPtr != NULL_PTR)
    {
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
      if (Dem_Cfg_InitPtrFinalMagicNumber(ConfigPtr) != DEM_CFG_FINAL_MAGIC_NUMBER)                                              /* SBSW_DEM_POINTER_FORWARD_API */
      {
        EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
      }
      else
      if (Dem_Cfg_InitPtrCompatibilityVersion(ConfigPtr) != DEM_CFG_GEN_COMPATIBILITY_VERSION)                                   /* SBSW_DEM_POINTER_FORWARD_API */
      {
        EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
      }
      else
# endif
      {
        /* Replace preliminary with final configuration */
        Dem_GlobalConfigPtr = ConfigPtr;
      }
    }
#endif
    Dem_Scheduler_Init();
    Dem_Timer_Init();
    Dem_ClientAccess_Init();
    Dem_EventQueueCore_Init();
    Dem_ClearTask_Init();
    Dem_Queue_Init();
    Dem_Nvm_Init();
    Dem_Memory_Init();
    Dem_Indicator_Init();
    Dem_Event_Init();
    Dem_DTC_Init();
    Dem_OperationCycle_Init();
#if (DEM_FEATURE_NEED_OBD == STD_ON)
    Dem_Mem_Init_RestoreMemoryObd();
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
# if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
    if (Dem_Mem_GetPermanentActivationState() == TRUE)
# endif
    {
      Dem_Memory_PermanentFillUp();
    }
#endif

    Dem_DtrIF_Init();
    Dem_Dcm_Init();

    Dem_InitState_SetInitState(DEM_INITSTATE_INITIALIZED);
#if (DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON)
# if (DEM_CFG_USE_MULTI_PARTITION_FIM == STD_ON)
    FiM_DemInitMaster();
# else
    FiM_DemInit();
# endif
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_INIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_Init(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_Cfg_GlobalSatelliteCount() != 1)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestMasterInState(DEM_INITSTATE_SHUTDOWN) == TRUE)
    {
      Dem_MasterInit(ConfigPtr);                                                                                                 /* SBSW_DEM_POINTER_FORWARD_API */
    }
    else
    {
      Dem_MasterInit(ConfigPtr);                                                                                                 /* SBSW_DEM_POINTER_FORWARD_API */
      Dem_SatelliteInit(DEM_SATELLITE_APPLICATION_ZERO);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_INIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Shutdown
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
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_Shutdown(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
    boolean lPostRunRequested;
    lPostRunRequested = FALSE;
    (void)Dem_PostRunRequested(&lPostRunRequested);                                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
    if (lPostRunRequested == TRUE)
    { /* Only set the error, but perform the shutdown. We are not going to stop
       * the shutdown anyway, so rescue as much state as possible */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
#endif

    Dem_InitState_SetInitState(DEM_INITSTATE_SHUTDOWN);

    Dem_DtrIF_Shutdown();

    Dem_OperationCycle_Shutdown();

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
    /* copy debounce values from debounce array to nvram mirror */
    Dem_Mem_CopyDataDebounceNv();
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_DEBOUNCE), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
    Dem_Nvm_Shutdown();
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SHUTDOWN_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MasterMainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_MasterMainFunction(
  void
  )
{
  Dem_MasterMainFunctionTimer();
  Dem_MasterMainFunctionWorker();
}

/* ****************************************************************************
 % Dem_SatelliteMainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_SatelliteMainFunction(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()
  Dem_Satellite_IdType lSatelliteId;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)
  lSatelliteId = Dem_Satellite_GetCurrentSatelliteId();

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestSatelliteAtLeastInState(lSatelliteId, DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_InitState_TestSatelliteAtLeastInState(lSatelliteId, DEM_INITSTATE_INITIALIZED) == TRUE)
    {
      Dem_SatelliteSat_MainFunction(lSatelliteId);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SATELLITEMAINFUNCTION_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}

#if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
/* ****************************************************************************
 % Dem_RequestNvSynchronization
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_RequestNvSynchronization(
  void
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
# if (DEM_CFG_USE_NVM == STD_ON)
    Dem_Nvm_SetSynchronizationFlag();
    lReturnValue = E_OK;
# else
    lReturnValue = E_NOT_OK;
# endif
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REQUESTNVSYNCHRONIZATION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_VERSION_INFO == STD_ON)
/* ****************************************************************************
 % Dem_GetVersionInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, DEM_CODE)
Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)  versioninfo
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (versioninfo == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    versioninfo->vendorID = DEM_VENDOR_ID;                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->moduleID = DEM_MODULE_ID;                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;                                                                        /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;                                                                        /* SBSW_DEM_POINTER_WRITE_API */
    versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;                                                                        /* SBSW_DEM_POINTER_WRITE_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETVERSIONINFO_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif
}
#endif /* (DEM_CFG_SUPPORT_VERSION_INFO == STD_ON) */

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_SetEventAvailable
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
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventAvailable(
  uint16  EventId,
  boolean  AvailableStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
#  if ( (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON) || (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON) )
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  else
  if (Dem_InitState_TestMasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  endif
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (AvailableStatus > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)
    {
      if (AvailableStatus == TRUE)
      {
        Dem_Event_Reconnect(EventId);
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = Dem_Event_Disconnect(EventId);
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETEVENTAVAILABLE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_SetDTCSuppression
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
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCSuppression(
  uint8  ClientId,
  boolean  SuppressionStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (SuppressionStatus > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
      lReturnValue = Dem_ClientAccess_EventChangeDtcSuppression(ClientId, SuppressionStatus);
      break;

    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETDTCSUPPRESSION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_GetDTCSuppression
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
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSuppression(
  uint8  ClientId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  SuppressionStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

    /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (SuppressionStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
      lReturnValue = Dem_ClientAccess_EventRetrieveDtcSuppression(ClientId, SuppressionStatus);                                  /* SBSW_DEM_POINTER_FORWARD_API */
      break;

    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCSUPPRESSION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_SetEnableCondition
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEnableCondition(
  uint8  EnableCondition,                                                                                                        /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  boolean  ConditionFulfilled
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if ( (EnableCondition == DEM_ENABLECONDITION_CONTROLDTCSETTING)                                                                /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (EnableCondition >= Dem_EnableCondition_GetGlobalEnableConditionCount()) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (ConditionFulfilled == TRUE)
    {
      Dem_EnableCondition_SetEnableConditionFulfilled(EnableCondition);
    }
    else
    {
      Dem_EnableCondition_ResetEnableConditionFulfilled(EnableCondition);
    }

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETENABLECONDITION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_SetStorageCondition
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetStorageCondition(
  uint8  StorageCondition,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  boolean  ConditionFulfilled
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_StorageCondition_GetGlobalStorageConditionCount() <= StorageCondition)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (ConditionFulfilled > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (ConditionFulfilled == TRUE)
    {
      Dem_StorageCondition_SetStorageConditionFulfilled(StorageCondition);
    }
    else
    {
      Dem_StorageCondition_ResetStorageConditionFulfilled(StorageCondition);
    }

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETSTORAGECONDITION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON) */

/* ****************************************************************************
 % Dem_ReportErrorStatus
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
 *
 */
FUNC(void, DEM_CODE)
Dem_ReportErrorStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventStatus >= DEM_EVENT_STATUS_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
  if ( (Dem_Cfg_EventSupportDebounceNv(EventId) == TRUE)                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  if (Dem_Satellite_CheckEventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    (void)Dem_SatelliteSat_ReportMonitorTrigger(EventId, EventStatus);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REPORTERRORSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_SetEventStatus
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
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventStatus(
  Dem_EventIdType     EventId,                                                                                                   /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  Dem_EventStatusType EventStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventStatus >= DEM_EVENT_STATUS_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (EventStatus > DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED)                                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
    && (Dem_Cfg_EventObdRelated(EventId) == FALSE) 
# endif
    )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
  if ( (Dem_Cfg_EventSupportDebounceNv(EventId) == TRUE)                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  if (Dem_Satellite_CheckEventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_SatelliteSat_ReportMonitorTrigger(EventId, EventStatus);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETEVENTSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_ResetEventStatus
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventStatus(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_Satellite_CheckEventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_SatelliteSat_ResetEventStatus(EventId);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_RESETEVENTSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_PrestoreFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_PrestoreFreezeFrame(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_Satellite_CheckEventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Prestore_EventPrestoreFreezeFrame(EventId);
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_PRESTOREFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_ClearPrestoredFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_Satellite_CheckEventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Prestore_EventClearPrestoredFreezeFrame(EventId);
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_CLEARPRESTOREDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

/* ****************************************************************************
 % Dem_ResetEventDebounceStatus
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
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventDebounceStatus(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  Dem_DebounceResetStatusType  DebounceResetStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_PREINITIALIZED) == FALSE)            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestSatelliteInState(Dem_Cfg_EventSatelliteId(EventId), DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (DebounceResetStatus >= DEM_DEBOUNCE_STATUS_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
  if ( (Dem_Cfg_EventSupportDebounceNv(EventId) == TRUE)                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  if (Dem_Satellite_CheckEventApplicationId(EventId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      if (DebounceResetStatus == DEM_DEBOUNCE_STATUS_RESET)
      {
        Dem_SatelliteSat_ResetDebounceStatus(
            Dem_Cfg_EventSatelliteId(EventId),
            Dem_Cfg_EventSatelliteEventId(EventId));

      }
      else
      {
        Dem_SatelliteSat_FreezeDebounceStatus(
            Dem_Cfg_EventSatelliteId(EventId),
            Dem_Cfg_EventSatelliteEventId(EventId));
      }

      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_RESETEVENTDEBOUNCESTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetDebouncingOfEvent
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDebouncingOfEvent(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA)  DebouncingState
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DebouncingState == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      (*DebouncingState) =                                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
          Dem_SatelliteSat_GetDebouncingState(
              Dem_Cfg_EventSatelliteId(EventId),
              Dem_Cfg_EventSatelliteEventId(EventId));
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDEBOUNCINGOFEVENT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_SetOperationCycleState
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetOperationCycleState(
  uint8  OperationCycleId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  Dem_OperationCycleStateType  CycleState
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (OperationCycleId >= Dem_Cfg_GlobalCycleCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (CycleState >= DEM_CYCLE_STATE_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_OperationCycle_SetState(OperationCycleId, CycleState);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETOPERATIONCYCLESTATE_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetOperationCycleState
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOperationCycleState(
  uint8  OperationCycleId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_APPL_DATA)  CycleState
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (OperationCycleId >= Dem_Cfg_GlobalCycleCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (CycleState == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
     lReturnValue = E_OK;
     *CycleState = Dem_OperationCycle_GetCycleState(OperationCycleId);                                                           /* SBSW_DEM_POINTER_WRITE_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETOPERATIONCYCLESTATE_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetIndicatorStatus
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIndicatorStatus(
  uint8  IndicatorId,                                                                                                            /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA)  IndicatorStatus                                                      /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (IndicatorStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *IndicatorStatus = Dem_Indicator_GetIndicatorStatus(IndicatorId);                                                            /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETINDICATORSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_GetWIRStatus
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetWIRStatus(
  Dem_EventIdType EventId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) WIRStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (WIRStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      *WIRStatus = Dem_DTC_GetWIRStatus(EventId);                                                                                /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETWIRSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) */

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_SetWIRStatus
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetWIRStatus(
  Dem_EventIdType EventId,                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  boolean WIRStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (WIRStatus > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      lReturnValue = Dem_DTC_SetWIRStatus(EventId, WIRStatus);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETWIRSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) */

/* ****************************************************************************
 % Dem_SelectDTC
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
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectDTC(
  uint8              ClientId,
  uint32             DTC,
  Dem_DTCFormatType  DTCFormat,
  Dem_DTCOriginType  DTCOrigin
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_ClientAccess_TestSelectorValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTC > DEM_DTC_GROUP_ALL_DTCS)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCFormat >= DEM_DTC_FORMAT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin >= DEM_DTC_ORIGIN_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin == 0)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  if (Dem_ClientAccess_TestSelectDTCLocked(ClientId) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_SUPPORT_DCM == STD_ON)
    (void) Dem_ClientAccess_EnableDTCRecordUpdate(ClientId);
#endif
    Dem_ClientAccess_SelectDTC(ClientId, DTC, DTCFormat, DTCOrigin);
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SELECTDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetDTCSelectionResult
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
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSelectionResult(
  uint8 ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_ClientAccess_TestSelectorValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
      lReturnValue = E_OK;
      break;

    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }
  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCSELCETIONRESULT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_GetMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetMonitorStatus(
  Dem_EventIdType  EventId,
  P2VAR(Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA)  MonitorStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (MonitorStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      (*MonitorStatus) = Dem_Satellite_GetMonitorStatus(                                                                         /* SBSW_DEM_POINTER_WRITE_API */
                           Dem_Cfg_EventSatelliteId(EventId),
                           Dem_Cfg_EventSatelliteEventId(EventId)
                           );
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETMONITORSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_GetEventUdsStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventUdsStatus(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  UDSStatusByte
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (UDSStatusByte == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Event_GetEventUDSStatus(EventId, UDSStatusByte);                                                          /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTUDSSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetEventFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFailed(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventFailed == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Event_GetEventFailed(EventId, EventFailed);                                                               /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTFAILED_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetEventTested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventTested(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventTested == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_Event_GetEventTested(EventId, EventTested);                                                               /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTTESTED_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_GetEventFreezeFrameDataEx
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  uint8  RecordNumber,                                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  uint16  DataId,                                                                                                                /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)
  DEM_IGNORE_UNUSED_ARGUMENT(BufSize)                                                                                            /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DestBuffer == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (BufSize == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx(EventId, RecordNumber, DataId, DestBuffer, BufSize);              /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTFREEZEFRAMEDATAEX_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  uint8  RecordNumber,                                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,                                                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize                                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DestBuffer == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (BufSize == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx(EventId, RecordNumber, DestBuffer, BufSize);                   /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTEXTENDEDDATARECORDEX_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

                                /* Service Interface EvMemOverflowIndication */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 % Dem_GetEventMemoryOverflow
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventMemoryOverflow(
  uint8  ClientId,
  Dem_DTCOriginType  DTCOrigin,                                                                                                  /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  OverflowIndication
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)
  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin == 0)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin >= DEM_DTC_ORIGIN_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (OverflowIndication == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    switch (DTCOrigin)
    {
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
      *OverflowIndication = Dem_Memory_GetOverflow(DEM_CFG_MEMORYID_PRIMARY);                                                       /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
      *OverflowIndication = Dem_Memory_GetOverflow(DEM_CFG_MEMORYID_SECONDARY);                                                     /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;
# endif

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      *OverflowIndication = Dem_Memory_GetOverflow(DEM_CFG_MEMORYID_PERMANENT);                                                     /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;
# endif

    default:
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTMEMORYOVERFLOW_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON) */

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 % Dem_GetNumberOfEventMemoryEntries
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfEventMemoryEntries(
  uint8  ClientId,
  Dem_DTCOriginType  DTCOrigin,                                                                                                  /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  NumberOfEventMemoryEntries
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)
  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin == 0)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCOrigin >= DEM_DTC_ORIGIN_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (NumberOfEventMemoryEntries == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    switch (DTCOrigin)
    {
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
      *NumberOfEventMemoryEntries = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PRIMARY);                             /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
      *NumberOfEventMemoryEntries = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_SECONDARY);                           /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;
# endif

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      *NumberOfEventMemoryEntries = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PERMANENT);                           /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
      break;
# endif

    default:
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNUMBEROFEVENTMEMORYENTRIES_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON) */

/* ****************************************************************************
 % Dem_GetEventIdOfDTC
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
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventIdOfDTC(
  uint8  ClientId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA)  EventId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
      lReturnValue = Dem_Dcm_GetEventIdOfSelectedDTC(ClientId, EventId);                                                         /* SBSW_DEM_POINTER_FORWARD_API */
      break;

    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTIDOFDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */

/* Service Interface ClearDTC */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_ClearDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearDTC(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = DEM_CLEAR_FAILED;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    switch (Dem_ClientAccess_GetSelectionResult(ClientId))
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
      lReturnValue = Dem_ClientAccess_ClearDTC(ClientId);
      break;

    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_CLEARDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}

                                                                      /* DTR */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_SetDTR
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTR(
  uint16 DTRId,                                                                                                                  /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  sint32 TestResult,
  sint32 LowerLimit,
  sint32 UpperLimit,
  Dem_DTRControlType Ctrlval
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_DtrIF_IsValidHandle(DTRId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (LowerLimit > UpperLimit)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Ctrlval > DEM_DTR_CTL_INVISIBLE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
#endif
  {
    lReturnValue = Dem_DtrIF_SetDtr(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETDTR_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_UpdateAvailableOBDMIDs
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_UpdateAvailableOBDMIDs(
  void
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    Dem_DtrIF_UpdateMidVisibility();
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_UPDATEAVAILABLEOBDMIDS_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_GetEventEnableCondition
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
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventEnableCondition(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  ConditionFulfilled
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

    /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if ((EventId == DEM_EVENT_INVALID) || (EventId >= Dem_Cfg_GlobalEventCount()))                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (ConditionFulfilled == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      *ConditionFulfilled = Dem_EnableCondition_TestEventProcessingPrecondition(EventId);                                        /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETENABLECONDITION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) */

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 % Dem_SetHideObdOccurrences
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetHideObdOccurrences(
  boolean DoHide
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (DoHide > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (DoHide == TRUE)
    {
      Dem_DTCReporting_SetObdHideOccurrences();
    }
    else
    {
      Dem_DTCReporting_ResetObdHideOccurrences();
    }
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETHIDEOBDOCCURRENCES_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON) */

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 % Dem_GetHideObdOccurrences
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetHideObdOccurrences(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsHidden
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (IsHidden == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *IsHidden = (boolean)(Dem_DTCReporting_TestObdHideOccurrences() == TRUE);                                                    /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETHIDEOBDOCCURRENCES_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON) */
                                      /* Service Interface DiagnosticMonitor */
/* ------------------------------------------------------------------------- */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_SetEventDisabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventDisabled(
  Dem_EventIdType  EventId                                                                                                       /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    DEM_IGNORE_UNUSED_ARGUMENT(EventId)                                                                                          /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
# if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
    if ( (Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_NONE)                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_Event_TestEventUnavailable(EventId) == FALSE)
      )
    {
      Dem_Util_SetReadinessGroupDisabled(Dem_Cfg_EventReadinessGroup(EventId));
      lReturnValue = E_OK;
    }
# endif
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETEVENTDISABLED_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

                                         /* Service Interface DiagnosticInfo */
/* ------------------------------------------------------------------------- */
/* ****************************************************************************
 % Dem_GetDTCOfEvent
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCOfEvent(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  Dem_DTCFormatType  DTCFormat,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  DTCOfEvent
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCFormat >= DEM_DTC_FORMAT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (NULL_PTR == DTCOfEvent)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    uint32 lDtc;

    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      /* Dispatch requested DTC format */
      switch (DTCFormat)
      {
      case DEM_DTC_FORMAT_UDS:
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
      case DEM_DTC_FORMAT_OBD:  /* Fall through as UDS and WWH OBD share the same DTC number */
#endif
        lDtc = Dem_Cfg_EventUdsDtc(EventId);
        if (DEM_CFG_DTC_UDS_INVALID != lDtc)
        {
          *DTCOfEvent = lDtc;                                                                                                    /* SBSW_DEM_POINTER_WRITE_API */
          lReturnValue = E_OK;
        }
        else
        {
          lReturnValue = DEM_E_NO_DTC_AVAILABLE;
        }
        break;

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      case DEM_DTC_FORMAT_J1939:
        lDtc = Dem_Cfg_EventJ1939Dtc(EventId);
        if (DEM_CFG_DTC_J1939_INVALID != lDtc)
        {
          *DTCOfEvent = lDtc;                                                                                                    /* SBSW_DEM_POINTER_WRITE_API */
          lReturnValue = E_OK;
        }
        else
        {
          lReturnValue = DEM_E_NO_DTC_AVAILABLE;
        }
        break;
#endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
      case DEM_DTC_FORMAT_OBD:
        lDtc = Dem_Cfg_EventObdDtc(EventId);
        if (DEM_CFG_DTC_OBD_INVALID != lDtc)
        { /* copy valid DTC number to out parameter */
          *DTCOfEvent = (uint32)(lDtc << 8);                                                                                     /* SBSW_DEM_POINTER_WRITE_API */
          lReturnValue = E_OK;
        }
        else
        {
          lReturnValue = DEM_E_NO_DTC_AVAILABLE;
        }
        break;
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

      default:                                                                                                                   /* PRQA S 2018 */ /* MD_DEM_14.1 */
        /* MISRA case */
        break;
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCOFEVENT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFaultDetectionCounter(
  Dem_EventIdType  EventId,                                                                                                      /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter                                                                  /* PRQA S 3673 */ /* MD_DEM_16.7 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (FaultDetectionCounter == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
    {
      lReturnValue =
          Dem_Satellite_GetFaultDetectionCounter(                                                                                /* SBSW_DEM_POINTER_FORWARD_API */
              Dem_Cfg_EventSatelliteId(EventId),
              Dem_Cfg_EventSatelliteEventId(EventId),
              FaultDetectionCounter);
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETFAULTDETECTIONCOUNTER_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

                                         /* Service Interface IUMPRNumerator */
/* ------------------------------------------------------------------------- */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_RepIUMPRFaultDetect
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
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRFaultDetect(
  Dem_RatioIdType  RatioID                                                                                                       /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (RatioID >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (RatioID == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    Dem_RatioIdIndexType lRatioIndex;
    lRatioIndex = Dem_Cfg_EventRatioIdIdx(RatioID);

# if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (lRatioIndex == DEM_CFG_RATIOINDEX_INVALID)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
    }
    else
    if (Dem_Cfg_ObdRatioIdType(lRatioIndex) != DEM_RATIO_API)
    { /* API only allowed for ratios with RatioIdType = API */
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
    }
    else
# endif
    {
      /* ----- Implementation ---------------------------------------------- */
      if ( (Dem_Cfg_EventAvailableByVariant(RatioID) == TRUE)                                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(RatioID)) == FALSE) )
      {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
        Dem_EnterCritical_DiagMonitor();                                                                                         /* PRQA S 3109 */ /* MD_MSR_14.3 */

        Dem_Esm_RatioQueueAsync(lRatioIndex);

        Dem_LeaveCritical_DiagMonitor();                                                                                         /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
        lReturnValue = E_OK;
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REPIUMPRFAULTDETECT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_IUMPRLockNumerators
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_IUMPRLockNumerators(
  void
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint8 lNumeratorsLocked;

    /* ----- Implementation ------------------------------------------------ */
    lNumeratorsLocked = Dem_Mem_GetGlobalNumeratorsLocked();
    lNumeratorsLocked = DEM_ESM_SET_IUMPR_NUMERATORS_LOCKED(lNumeratorsLocked);

    Dem_Mem_SetGlobalNumeratorsLocked(lNumeratorsLocked);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                DEM_NVM_BLOCKSTATE_DIRTY);

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_IUMPRLOCKNUMERATORS_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_RepIUMPRDenLock
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
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRDenLock(
  Dem_RatioIdType  RatioID                                                                                                       /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (RatioID >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (RatioID == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    Dem_RatioIdIndexType  lRatioIndex;
    lRatioIndex = Dem_Cfg_EventRatioIdIdx(RatioID);

# if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (lRatioIndex == DEM_CFG_RATIOINDEX_INVALID)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
    }
    else
    if (Dem_Cfg_ObdIumprDenGroup(lRatioIndex) != DEM_IUMPR_DEN_PHYS_API)
    { /* API only allowed for ratios with IUMPR-Group = PHYS_API */
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
    }
    else
# endif
    {
      /* ----- Implementation ---------------------------------------------- */
      if ( (Dem_Cfg_EventAvailableByVariant(RatioID) == TRUE)                                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(RatioID)) == FALSE) )
      {
        uint8 lRatioStatus;

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
        Dem_EnterCritical_DiagMonitor();                                                                                         /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* set locked state */
        lRatioStatus = Dem_Mem_GetIumprStatus(lRatioIndex);
        lRatioStatus = DEM_ESM_SET_IUMPR_DEN_LOCKED(lRatioStatus);
        Dem_Mem_SetIumprStatus(lRatioIndex, lRatioStatus);

        /* don't set pending flag --> ratio will not be incremented if lock is set */

        Dem_LeaveCritical_DiagMonitor();                                                                                         /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

        lReturnValue = E_OK;
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REPIUMPRDENLOCK_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_RepIUMPRDenRelease
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
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRDenRelease(
  Dem_RatioIdType  RatioID                                                                                                       /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (RatioID >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (RatioID == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    Dem_RatioIdIndexType  lRatioIndex;
    lRatioIndex = Dem_Cfg_EventRatioIdIdx(RatioID);

# if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (lRatioIndex == DEM_CFG_RATIOINDEX_INVALID)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
    }
    else
    if (Dem_Cfg_ObdIumprDenGroup(lRatioIndex) != DEM_IUMPR_DEN_PHYS_API)
    { /* API only allowed for ratios with IUMPR-Group = PHYS_API */
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
    }
    else
# endif
    {
      uint8 lRatioStatus;

      /* ----- Implementation ---------------------------------------------- */
      if ( (Dem_Cfg_EventAvailableByVariant(RatioID) == TRUE)                                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(RatioID)) == FALSE) )
      {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
        Dem_EnterCritical_DiagMonitor();                                                                                         /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* clear locked state */
        lRatioStatus = Dem_Mem_GetIumprStatus(lRatioIndex);
        lRatioStatus = DEM_ESM_RESET_IUMPR_DEN_LOCKED(lRatioStatus);
        Dem_Mem_SetIumprStatus(lRatioIndex, lRatioStatus);

        Dem_LeaveCritical_DiagMonitor();                                                                                         /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

        if ( (DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_REACHED(Dem_Mem_GetGeneralDenominatorStatus()) == TRUE)
          && (DEM_ESM_TEST_IUMPR_DEN_INCREMENTED(lRatioStatus) == FALSE) )
        {
          /* conditions for increment seem to be fulfilled; set pending flag and increment on task level */
          Dem_Mem_IumprSetUpdatePending(lRatioIndex, TRUE);
          Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_IUMPR);
        }

        lReturnValue = E_OK;
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_REPIUMPRDENRELEASE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_SetIUMPRDenCondition
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
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRDenCondition(
  Dem_IumprDenomCondIdType ConditionId,                                                                                          /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  Dem_IumprDenomCondStatusType ConditionStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ConditionId == 0)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (ConditionId >= DEM_IUMPR_DEN_COND_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint8 lDenominatorGroup;
    uint8 lGenDenominatorStatus;

    lReturnValue = E_OK;
    lGenDenominatorStatus = Dem_Mem_GetGeneralDenominatorStatus();

    /* ----- Implementation ------------------------------------------------ */
    switch (ConditionId)
    {
    case DEM_IUMPR_GENERAL_DENOMINATOR:
      /* --- General Denominator Handling --- */
      if (ConditionStatus == DEM_IUMPR_DEN_STATUS_REACHED)
      {
        if (DEM_ESM_TEST_IUMPR_GENDEN_INCREMENTED(lGenDenominatorStatus) == FALSE)
        {
          /* general conditions fulfilled and denominator not yet incremented in this DCY */

          /* general denominator not yet incremented in this DCY */
          /* --> no overrun handling; value shall rollover and increment to zero  [CCR1968.2 (g)(5.2.1)(E)] */
          Dem_Mem_SetGeneralDenominator(Dem_Mem_GetGeneralDenominator() + 1);
          lGenDenominatorStatus = DEM_ESM_SET_IUMPR_GENDEN_CONDITIONS_REACHED(lGenDenominatorStatus);
          lGenDenominatorStatus = DEM_ESM_SET_IUMPR_GENDEN_INCREMENTED(lGenDenominatorStatus);

          /* update NvM */
          Dem_Mem_SetGeneralDenominatorStatus(lGenDenominatorStatus);
          Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                      DEM_NVM_BLOCKSTATE_DIRTY);
        }
      }
      else
      {
        /* general conditions not (yet) fulfilled */
        lGenDenominatorStatus = DEM_ESM_RESET_IUMPR_GENDEN_CONDITIONS_REACHED(lGenDenominatorStatus);

        if (ConditionStatus == DEM_IUMPR_DEN_STATUS_INHIBITED)
        {
          /* erroneous inputs: also set incremented flag to prevent, that general denominator is incremented in this DCY */
          lGenDenominatorStatus = DEM_ESM_SET_IUMPR_GENDEN_CONDITIONS_FAILED(lGenDenominatorStatus);
          lGenDenominatorStatus = DEM_ESM_SET_IUMPR_GENDEN_INCREMENTED(lGenDenominatorStatus);
        }

        /* update NvM */
        Dem_Mem_SetGeneralDenominatorStatus(lGenDenominatorStatus);
        Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                    DEM_NVM_BLOCKSTATE_DIRTY);
      }
      lDenominatorGroup = DEM_IUMPR_DEN_NONE;
      break;

    case DEM_IUMPR_DEN_COND_COLDSTART:
      lDenominatorGroup = DEM_IUMPR_DEN_COLDSTART;
      break;

    case DEM_IUMPR_DEN_COND_EVAP:
      lDenominatorGroup = DEM_IUMPR_DEN_EVAP;
      break;

    case DEM_IUMPR_DEN_COND_500MI:
      lDenominatorGroup = DEM_IUMPR_DEN_500MI;
      break;

    default:                                                                                                                     /* PRQA S 2018 */ /* MD_DEM_14.1 */
      /* MISRA case */
      lDenominatorGroup = DEM_IUMPR_DEN_COND_INVALID;
      lReturnValue = E_NOT_OK;
      break;
    }

    if (
# if (DEM_DEV_ERROR_DETECT == STD_OFF)
        (lDenominatorGroup != DEM_IUMPR_DEN_COND_INVALID) &&
# endif
        (DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_FAILED(Dem_Mem_GetGeneralDenominatorStatus()) == FALSE)
       )
    {
      /* Conditions for a denominator group have been changed and general conditions are not failed */
      Dem_Cfg_ObdRatioIdIterType lRatioIter;

      for (Dem_Cfg_ObdRatioIdIterInit(&lRatioIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_ObdRatioIdIterExists(&lRatioIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_ObdRatioIdIterNext(&lRatioIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        uint8 lRatioDenominator;

        /* depending on the configured ratio, either respect the general denominator or a
           specific denominator condition */
        lRatioDenominator = Dem_Cfg_ObdIumprDenGroup(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter));                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
        if (lRatioDenominator == DEM_IUMPR_DEN_PHYS_API)
        {
          lRatioDenominator = DEM_IUMPR_DEN_NONE;
        }

        /* update ratio specific denominator condition flag for all ratios that belong to the respective group */
        /* the groups "NONE" and "PHYS_API" are updated together with general denominator */
        if (lRatioDenominator == lDenominatorGroup)
        {
          uint8 lRatioStatus;

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
          Dem_EnterCritical_DiagMonitor();                                                                                       /* PRQA S 3109 */ /* MD_MSR_14.3 */

          /* the denominator status of the current ratio is affected by new condition status */
          lRatioStatus = Dem_Mem_GetIumprStatus(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter));                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */

          if (ConditionStatus == DEM_IUMPR_DEN_STATUS_REACHED)
          {
            /* denominator conditions are fulfilled */
            lRatioStatus = DEM_ESM_SET_IUMPR_DEN_CONDITIONS_REACHED(lRatioStatus);

            if ( (DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_REACHED(Dem_Mem_GetGeneralDenominatorStatus()) == TRUE)
              && (DEM_ESM_TEST_IUMPR_DEN_INCREMENTED(lRatioStatus) == FALSE) )
            {
              /* conditions for increment seem to be fulfilled; set pending flag and increment on task level */
              Dem_Mem_IumprSetUpdatePending(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), TRUE);                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
              Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_IUMPR);
            }
          }
          else
          {
            /* denominator conditions not fulfilled */
            lRatioStatus = DEM_ESM_RESET_IUMPR_DEN_CONDITIONS_REACHED(lRatioStatus);
            /* ratio will not be incremented, so pending flag need not be set */
          }

          Dem_Mem_SetIumprStatus(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), lRatioStatus);                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */

          Dem_LeaveCritical_DiagMonitor();                                                                                       /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

          Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                      DEM_NVM_BLOCKSTATE_DIRTY);
        }
      }
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETIUMPRDENCONDITION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_SetIUMPRFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRFilter(
  Dem_IumprReadinessGroupType IumprReadinessGroup,
  Dem_DTCOriginType  DTCOrigin
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if ( (IumprReadinessGroup >= DEM_IUMPR_READINESS_GROUP_INVALID)
    && (IumprReadinessGroup != DEM_IUMPR_ALLGROUPS) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ((DTCOrigin == 0) || (DTCOrigin >= DEM_DTC_ORIGIN_INVALID))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    Dem_Dcm_IumprFilterInfo.ReadinessGroup = IumprReadinessGroup;
    Dem_Dcm_IumprFilterInfo.CurrentEvent = DEM_EVENT_INVALID;

    switch (Dem_ClientAccess_MemoryIdFromOrigin(DTCOrigin))
    {
    case DEM_CFG_MEMORYID_PRIMARY:
      Dem_Dcm_IumprFilterInfo.FirstEvent = Dem_Cfg_GlobalPrimaryFirst();
      Dem_Dcm_IumprFilterInfo.LastEvent = Dem_Cfg_GlobalPrimaryLast();
      lReturnValue = E_OK;
      break;

    case DEM_CFG_MEMORYID_SECONDARY:
      Dem_Dcm_IumprFilterInfo.FirstEvent = Dem_Cfg_GlobalSecondaryFirst();
      Dem_Dcm_IumprFilterInfo.LastEvent = Dem_Cfg_GlobalSecondaryLast();
      lReturnValue = E_OK;
      break;

    default:
      /* not supported memory location for IUMPR filtering */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETIUMPRFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_GetNumberOfFilteredIUMPR
 *****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFilteredIUMPR(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  NumberOfFilteredRatios                                                                /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
)
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (NumberOfFilteredRatios == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_EventIdType lEventId;

    lEventId = Dem_Dcm_IumprFilterInfo.FirstEvent;
    if (lEventId != DEM_EVENT_INVALID)
    {
      *NumberOfFilteredRatios = 0;                                                                                               /* SBSW_DEM_POINTER_WRITE_API */
      for (lEventId = Dem_Dcm_IumprFilterInfo.FirstEvent;
        lEventId <= Dem_Dcm_IumprFilterInfo.LastEvent;
        ++lEventId)
      {
        Dem_RatioIdIndexType  lRatioIndex;
        lRatioIndex = Dem_Cfg_EventRatioIdIdx(lEventId);

        /* Skip suppressed or deactivated events. RatioId == EventId */
        if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_DTC_TestDtcSuppressed(lEventId) == FALSE)
          && (Dem_Event_TestEventSuppressed(lEventId) == FALSE))
        {
          /* either only a specific ratio group is selected or all groups are selected */
          if ( (Dem_Dcm_IumprFilterInfo.ReadinessGroup == Dem_Cfg_ObdRatioReadinessGroupType(lRatioIndex))
            || (Dem_Dcm_IumprFilterInfo.ReadinessGroup == DEM_IUMPR_ALLGROUPS))
          {
            ++(*NumberOfFilteredRatios);                                                                                         /* SBSW_DEM_POINTER_WRITE_API */
          }
        }
      }
      lReturnValue = E_OK;
    }
    else
    {
      /* initial call to Dem_SetIUMPRFilter is missing */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNUMBEROFFILTEREDIUMPR_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_GetIUMPRGeneralData
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIUMPRGeneralData(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  GeneralDenominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCycles,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCyclesHybrid
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (GeneralDenominator == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (IgnitionCycles == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (IgnitionCyclesHybrid == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *GeneralDenominator = Dem_Mem_GetGeneralDenominator();                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    *IgnitionCycles = Dem_Mem_GetIgnitionCycleCounter();                                                                         /* SBSW_DEM_POINTER_WRITE_API */
# if (DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID == STD_ON)
    *IgnitionCyclesHybrid = Dem_Mem_GetIgnitionCycleCounterHybrid();                                                             /* SBSW_DEM_POINTER_WRITE_API */
# else
    *IgnitionCyclesHybrid = 0;                                                                                                   /* SBSW_DEM_POINTER_WRITE_API */
# endif

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETIUMPRGENERALDATA_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_GetNextIUMPRRatioDataAndDTC
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
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextIUMPRRatioDataAndDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (UdsDtcNumber == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ObdDtcNumber == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Denominator == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Numerator == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_EventIdType lEventId;

    lEventId = Dem_Dcm_IumprFilterInfo.FirstEvent;
    if (lEventId != DEM_EVENT_INVALID)
    {
      lEventId = Dem_Dcm_IumprFilterInfo.CurrentEvent;

      if (Dem_Dcm_IumprFilterInfo.CurrentEvent == DEM_EVENT_INVALID)
      { /* Initial call after set filter, set current event to first event */
        lEventId = Dem_Dcm_IumprFilterInfo.FirstEvent;
      }
      else
      {
        lEventId += 1; /* add 1 for the next possible element */
      }


      for (; lEventId <= Dem_Dcm_IumprFilterInfo.LastEvent; ++lEventId)
      {
        Dem_RatioIdIndexType  lRatioIndex;

        lRatioIndex = Dem_Cfg_EventRatioIdIdx(lEventId);

        /* Skip suppressed or deactivated events. RatioId == EventId */
        if ((lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_DTC_TestDtcSuppressed(lEventId) == FALSE)
          && (Dem_Event_TestEventSuppressed(lEventId) == FALSE)
          )
        {
          /* either only a specific ratio group is selected or all groups are selected */
          if ((Dem_Dcm_IumprFilterInfo.ReadinessGroup == Dem_Cfg_ObdRatioReadinessGroupType(lRatioIndex))
            || (Dem_Dcm_IumprFilterInfo.ReadinessGroup == DEM_IUMPR_ALLGROUPS))
          {
            *UdsDtcNumber = Dem_Cfg_EventUdsDtc(lEventId);                                                                       /* SBSW_DEM_POINTER_WRITE_API */
            *ObdDtcNumber = Dem_Cfg_EventObdDtc(lEventId);                                                                       /* SBSW_DEM_POINTER_WRITE_API */
            *Denominator = Dem_Mem_GetDenominator(lRatioIndex);                                                                  /* SBSW_DEM_POINTER_WRITE_API */
            *Numerator = Dem_Mem_GetNumerator(lRatioIndex);                                                                      /* SBSW_DEM_POINTER_WRITE_API */

            lReturnValue = E_OK;
            break;
          }
        }
      }

      if (lEventId <= Dem_Dcm_IumprFilterInfo.LastEvent)
      {
        Dem_Dcm_IumprFilterInfo.CurrentEvent = lEventId;
      }
    }
    else
    {
      /* initial call to Dem_SetIUMPRFilter is missing */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTIUMPRRATIODATAANDDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_GetCurrentIUMPRRatioDataAndDTC
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
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetCurrentIUMPRRatioDataAndDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (UdsDtcNumber == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ObdDtcNumber == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Denominator == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Numerator == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_EventIdType lEventId;

    lEventId = Dem_Dcm_IumprFilterInfo.CurrentEvent;
    if (lEventId != DEM_EVENT_INVALID)
    {
      Dem_RatioIdIndexType  lRatioIndex;

      lRatioIndex = Dem_Cfg_EventRatioIdIdx(lEventId);

        /* Exclude suppressed or deactivated events. RatioId == EventId */
      if ( (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_DTC_TestDtcSuppressed(lEventId) == FALSE)
        && (Dem_Event_TestEventSuppressed(lEventId) == FALSE)
        )
      {
        *UdsDtcNumber = Dem_Cfg_EventUdsDtc(lEventId);                                                                           /* SBSW_DEM_POINTER_WRITE_API */
        *ObdDtcNumber = Dem_Cfg_EventObdDtc(lEventId);                                                                           /* SBSW_DEM_POINTER_WRITE_API */
        *Denominator = Dem_Mem_GetDenominator(lRatioIndex);                                                                      /* SBSW_DEM_POINTER_WRITE_API */
        *Numerator = Dem_Mem_GetNumerator(lRatioIndex);                                                                          /* SBSW_DEM_POINTER_WRITE_API */

        lReturnValue = E_OK;
      }
    }
    else
    {
      /* initial call to Dem_GetNextIUMPRRatioDataAndDTC is missing */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETCURRENTIUMPRRATIODATAANDDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

                                         /* Service Interface EventAvailable */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_GetEventAvailable
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
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventAvailable(
  uint16  EventId,                                                                                                               /* PRQA S 1330, 3206 */ /* MD_DEM_16.4_rte, MD_DEM_3206 */
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  AvailableStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
#  if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  else
  if (Dem_InitState_TestMasterAtLeastInState(DEM_INITSTATE_PREINITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
#  endif
  else
  if (EventId == DEM_EVENT_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (AvailableStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *AvailableStatus = (boolean)( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE) &&                                          /* SBSW_DEM_POINTER_WRITE_API */ /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                                  (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) );
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETEVENTAVAILABLE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

                                               /* Permanent Fault Code Cycle */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_SetPfcCycleQualified
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetPfcCycleQualified(
  void
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
/* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */

    Dem_OperationCycle_SetObdCycleStates(DEM_OPERATIONCYCLE_SET_PFC_CYCLE(Dem_OperationCycle_GetObdCycleStates()));

    Dem_LeaveCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: StateManager */

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETPFCCYCLEQUALIFIED_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif
                                             /* Permanent Storage Activation */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 % Dem_EnablePermanentStorage
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnablePermanentStorage(
  void
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    boolean lCurrentPermanentActivationState;

    /* ----- Implementation ------------------------------------------------ */
/* >>>> -------------------------------- Enter Critical Section: DcmApi
 * Critical section to read current value and write new value. This guarantees Dem_Memory_PermanentFillUp is called
 * only once.  */
    Dem_EnterCritical_DcmApi();                                                                                                  /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* PDTC storage may be activated from task level or by a diagnostic request */
    lCurrentPermanentActivationState = Dem_Mem_GetPermanentActivationState();
    if (lCurrentPermanentActivationState == FALSE)
    {
      /* permanent storage is not yet active */
      Dem_Mem_SetPermanentActivationState(TRUE);
    }

    Dem_LeaveCritical_DcmApi();                                                                                                  /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DcmApi */

    if (lCurrentPermanentActivationState == FALSE)
    {
      Dem_Memory_PermanentFillUp();
    } /* else: permanent storage is already active; nothing to do */

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_ENABLEPERMANENTSTORAGE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 % Dem_GetPermanentStorageState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetPermanentStorageState(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  isEnabled
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (isEnabled == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *isEnabled = (boolean)(Dem_Mem_GetPermanentActivationState() == TRUE);                                                       /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETPERMANENTSTORAGESTATE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

                                                               /* B1 Counter */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_GetB1Counter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetB1Counter(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  B1Counter
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (B1Counter == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    /* internal resolution of 1min/bit must be converted to 1h/bit */
    *B1Counter = (uint16)(Dem_Mem_GetB1Counter()/60);                                                                            /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETB1COUNTER_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif
                                                                 /* PID Data */
/* ------------------------------------------------------------------------- */
#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 % Dem_ReadDataOfPID01
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_ReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  PID01value
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (PID01value == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_Dcm_ReadDataOfPID01(PID01value, 4);                                                                                      /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_READDATAOFPID01_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_FEATURE_NEED_OBD_SUPPORT == STD_ON) && (DEM_CFG_SUPPORT_PID01 == STD_ON) */

                                                     /* Extension to Autosar */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_PostRunRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_PostRunRequested(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsRequested
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (IsRequested == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
#endif
  {
    /* ----- Implementation ------------------------------------------------ */
#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
    if ( (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_Nvm_IsCurrentlyWrittenBlockModified() == TRUE ) )
    { /* Currently waiting for NvM JobResult, and the same block is still in the process
         of committing a previous data set - we are not allowed to mark this block using
         NvM_SetRamBlockStatus -> return TRUE to request more time untile the situation
         has resulved itself */
      *IsRequested = TRUE;                                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    }
    else
    {
      *IsRequested = FALSE;                                                                                                      /* SBSW_DEM_POINTER_WRITE_API */
    }
    lReturnValue = E_OK;
#else
  /* No immediate Nv-Write is supported, always return false */
    *IsRequested = FALSE;                                                                                                        /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_POSTRUNREQUESTED_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  return lReturnValue;
}
                                                                /* Callbacks */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_NvM_InitAdminData
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
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAdminData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    uint8 lCycleIterator;

    /* ----- Implementation ------------------------------------------------ */
    Dem_Cfg_AdminData.ImplementationVersion = Dem_Make16Bit(DEM_SW_MAJOR_VERSION, DEM_SW_MINOR_VERSION);
    Dem_Cfg_AdminData.ConfigurationId = Dem_Cfg_GlobalConfigurationId();

    for (lCycleIterator = 0U; lCycleIterator < Dem_Cfg_GlobalCycleCount(); ++lCycleIterator)
    {
      Dem_OperationCycle_SetCycleCounter(lCycleIterator, 0U);
    }
#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
    Dem_Cfg_AdminData.MemoryOverflow = 0U;
#endif

#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
    Dem_Cfg_AdminData.CycleState = 0x00U;
# if (DEM_FEATURE_NEED_OBD == STD_ON)
    Dem_Cfg_AdminData.CycleState = (uint8)(Dem_Cfg_AdminData.CycleState | (uint8)(1U << Dem_Cfg_GlobalObdDrivingCycleId()));
# endif
#endif /* (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON) */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
    /* clear the qualified driving cycle state and the Pfc cycle state */
    Dem_OperationCycle_SetObdCycleStates(0x00);

# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
    /* Clear PID21 and PID4D aging counter */
    Dem_Mem_SetPidAgingCounter(0);
# endif

# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
    /* Clear Odometer for MIL on */
    Dem_Mem_SetOdometerMilOn(0);
# endif
# if (DEM_CFG_SUPPORT_PID30 == STD_ON)
    /* Clear WarmUpCountAtClear */
    Dem_Mem_SetWarmUpCountSinceClear(0);
# endif
# if (DEM_CFG_SUPPORT_PID31 == STD_ON)
    /* Set Odometer at clear to invalid, so the first valid odometer is stored on main task */
    Dem_Mem_SetOdometerAtClear(DEM_MEM_SET_ODOMETER_INVALID(0));
# endif
# if (DEM_CFG_SUPPORT_PID4D == STD_ON)
    Dem_Mem_SetEngineTimeMilOn(0);
# endif
# if (DEM_CFG_SUPPORT_PID4E == STD_ON)
    Dem_Mem_SetEngineTimeSinceClear(0);
# endif
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    Dem_Mem_SetB1Counter(0);
    Dem_Mem_SetB1HealingCounter(0);
    Dem_Mem_SetContinuousMiCounter(0);
    Dem_Mem_SetContinuousMiAgingCounter(DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED);
    Dem_Mem_SetContinuousMiHealingCounter(DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED);
    Dem_Mem_SetContinuousMiAgingTimer(DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED);
    Dem_Mem_SetCumulativeEngRuntime(0);
# endif

# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
    /* Clear Ignition Cycle Counter(s) */
    Dem_Mem_SetIgnitionCycleCounter(0);
#  if (DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID == STD_ON)
    Dem_Mem_SetIgnitionCycleCounterHybrid(0);
#  endif
# endif
# if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
    Dem_Mem_SetPermanentActivationState(FALSE);
    Dem_Mem_SetPermanentActivationDistance(DEM_MEM_SET_ODOMETER_INVALID(0));
# endif
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */
#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
    Dem_Mem_SetPid41DisabledMask(0);
#endif
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}

/* ****************************************************************************
 % Dem_NvM_InitStatusData
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
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitStatusData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#endif
  {
    Dem_EventIdType lEventId;

    /* ----- Implementation ------------------------------------------------ */
    for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
    {
      Dem_Event_InitNvData(lEventId);
    }

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
    {
      uint16 lMilGroupIndex;
      lMilGroupIndex = Dem_Cfg_GlobalMilGroupCount();
      while (lMilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
      {
        lMilGroupIndex--;
        Dem_Mem_InitMilGroupTripCount(lMilGroupIndex);
        Dem_EventInternalStatus_SetMilGroupPendingCount(lMilGroupIndex, 0);
      }
    }
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    {
      Dem_Memory_InitConfirmedChronology();
    }
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
    /* all monitors are set to not complete -> reserved bits are set to 0 */
    if ((Dem_Cfg_GlobalPid01SupportedMask() & DEM_READINESS_SUPPORT_COMPRESSION) != 0)
    {
      Dem_Mem_SetPid01CompletedMask(DEM_READINESS_INITIALIZE_PID01COMPLETED_COMPRESSION);
    }
    else
    {
      Dem_Mem_SetPid01CompletedMask(DEM_READINESS_INITIALIZE_PID01COMPLETED_SPARK);
    }
#endif

    Dem_Statistics_SetFirstFailedEvent(DEM_EVENT_INVALID);
    Dem_Statistics_SetFirstConfirmedEvent(DEM_EVENT_INVALID);
    Dem_Statistics_SetMostRecentFailedEvent(DEM_EVENT_INVALID);
    Dem_Statistics_SetMostRecentConfirmedEvent(DEM_EVENT_INVALID);
  }

  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitDebounceData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDebounceData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_MemSet((Dem_NvDataPtrType)&Dem_Cfg_DebounceData[0], 0x00, Dem_Cfg_GlobalDebounceStorageEventCount()*sizeof(Dem_Cfg_DebounceData[0]));       /* PRQA S 0602, 3109, 0310 */ /* MD_DEM_20.2, MD_MSR_14.3, MD_DEM_11.4_cpy */ /* SBSW_DEM_MEMSET_DEBOUNCEDATA */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitEventAvailableData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitEventAvailableData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_MemSet((Dem_NvDataPtrType)&Dem_Cfg_EventAvailableData[0], 0x00, Dem_Cfg_GlobalEventAvailableDataSize() * sizeof(Dem_Cfg_EventAvailableData[0]));   /* PRQA S 0310, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_EVENTAVAILABLEDATA */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitObdFreezeFrameData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdFreezeFrameData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    uint8 lFreezeFrameIndex;

    /* ----- Implementation ------------------------------------------------ */
    lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();

    while (lFreezeFrameIndex != 0U)
    {
      lFreezeFrameIndex--;
      Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lFreezeFrameIndex);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitObdPermanentData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdPermanentData(
  void
  )
{
  /* ----- Development Error Checks ---------------------------------------- */

  /* Do not check for preinitialization phase */

  /* ----- Implementation -------------------------------------------------- */
  uint8 lPermanentIndex;

  lPermanentIndex = Dem_Cfg_GlobalPermanentMaxCount();

  while(lPermanentIndex != 0)
  {
    --lPermanentIndex;
    Dem_Mem_PermanentSetEvent(lPermanentIndex, DEM_EVENT_INVALID);
    Dem_Mem_PermanentSetStatus(lPermanentIndex, DEM_ESM_PERMANENT_NONE);
  }

  Dem_Mem_PermanentSetInitPattern(DEM_MEM_PERMANENT_INIT_PATTERN);

  /* ----- Development Error Report ---------------------------------------- */

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitObdIumprData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdIumprData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    Dem_Cfg_ObdRatioIdIterType     lRatioIter;

    /* ----- Implementation ------------------------------------------------ */
    /* initialize general data */
    Dem_Mem_SetGeneralDenominator(0);
    Dem_Mem_SetGeneralDenominatorStatus(0);
    Dem_Mem_SetGlobalIumprHybridStatus(0);
    Dem_Mem_SetGlobalNumeratorsLocked(0);

    /* initialize all ratios */
    for (Dem_Cfg_ObdRatioIdIterInit(&lRatioIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_ObdRatioIdIterExists(&lRatioIter) == TRUE;                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_ObdRatioIdIterNext(&lRatioIter))                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Mem_SetDenominator(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), 0);                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Mem_SetNumerator(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), 0);                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Mem_SetIumprStatus(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), 0);                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitDtrData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDtrData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    DTRIdType lDtrId;
    /* Initialize all Dtrs */
    for (lDtrId = 0; lDtrId < DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS; lDtrId++)
    {
      Dem_DtrIF_SetDtrValues(lDtrId, 0, 0, 0);
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif /* (DEM_CFG_SUPPORT_DTR == STD_ON) */

#if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
/* ****************************************************************************
 % Dem_NvM_InitAgingData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAgingData(
  void
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
    /* Set all aging counter array entries to invalid */
    Dem_MemSet((Dem_DataPtrType)&(Dem_Cfg_GetAgingData().AgingCounter[0]),                                                       /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_AGINGDATA_AGINGCOUNTER */
      0xFF,
      DEM_CFG_MAX_NUMBER_AGING_DTCS * sizeof(Dem_Cfg_GetAgingData().AgingCounter[0]));
# endif

# if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    /* Set all aged counter array entries to the initial value */
    Dem_MemSet((Dem_DataPtrType)&(Dem_Cfg_GetAgingData().AgedCounter[0]),                                                       /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_AGINGDATA_AGEDCOUNTER */
      DEM_DTC_AGED_COUNTER_INIT_VALUE,
      DEM_CFG_MAX_NUMBER_AGED_DTCS * sizeof(Dem_Cfg_GetAgingData().AgedCounter[0]));
# endif
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_NVMINIT_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  /* The DEM expects that the NVM by itself marks the NVRAM block as dirty */
  return E_OK;
}
#endif

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 % Dem_NvM_JobFinished
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_JobFinished(
  uint8  ServiceId,                                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  NvM_RequestResultType  JobResult                                                                                               /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_ARGUMENT(ServiceId)                                                                                          /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
  Dem_Nvm_ChangeNVWriteState(JobResult);
  return E_OK;
}
#endif /* ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF)) */



FUNC(void, DEM_CODE)
Dem_MementryInitFromApp(
		Dem_Cfg_MemoryIndexType index
  )
  {

	Dem_MemoryEntry_Init(index);

  }
/*
FUNC(void, DEM_CODE)
Dem_Dem_Cfg_AdminDataInitFromApp(void)
{

    Dem_Cfg_AdminData.ImplementationVersion = Dem_Make16Bit(DEM_SW_MAJOR_VERSION, DEM_SW_MINOR_VERSION);
    Dem_Cfg_AdminData.ConfigurationId = Dem_Cfg_GlobalConfigurationId();

}
*/
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_API_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_API.h
 *********************************************************************************************************************/
