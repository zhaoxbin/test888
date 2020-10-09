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
/*! \addtogroup Dem_Queue
 *  \{
 *  \file       Dem_Queue_Implementation.h
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

#if !defined (DEM_QUEUE_IMPLEMENTATION_H)
#define DEM_QUEUE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Queue_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Esm_Implementation.h"
#include "Dem_DataStorageIF_Implementation.h"
#include "Dem_Indicator_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

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

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/*! DCY qualification flag */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)           Dem_Queue_DcyCycleFlag;
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Normal rate time-series update request flag */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)           Dem_Queue_FetchTimeSeriesNormalRate;
# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/*! Fast rate time-series update request flag */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)           Dem_Queue_FetchTimeSeriesFastRate;
# endif
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_PID4D == STD_ON) || (DEM_CFG_SUPPORT_PID4E == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/*! Engine run-time update poll timer */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)            Dem_Timer_PollRateEngineRunTime;
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Normal rate time-series snapshot record update poll timer */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)            Dem_Timer_TimeSeriesNormalRate;
# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/*! Fast rate time-series snapshot record update poll timer */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)            Dem_Timer_TimeSeriesFastRate;
# endif
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/*! Pending updates of readiness groups */
DEM_LOCAL volatile VAR(uint16, DEM_VAR_INIT)     Dem_Queue_Pid01UpdateFlag;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_PID4D == STD_ON) || (DEM_CFG_SUPPORT_PID4E == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/*! Last received engine run-time */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)            Dem_Timer_LastEngineRunTime;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Queue_Properties
 * \{
 */

#if (DEM_FEATURE_NEED_PID01_CALCULATION  == STD_ON)
/* ****************************************************************************
 % Dem_Queue_SetPid01UpdateFlag
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Queue_SetPid01UpdateFlag(
  CONST(uint16, AUTOMATIC)  UpdateFlag
  )
{
  Dem_Queue_Pid01UpdateFlag = UpdateFlag;
}
#endif

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
 * \addtogroup Dem_Queue_Private
 * \{
 */

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
 * \addtogroup Dem_Queue_Public
 * \{
 */

                                                                    /* Timer */
/* ------------------------------------------------------------------------- */
/* ****************************************************************************
 % Dem_Timer_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Timer_Init(
  void
  )
{
#if (DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON)
  Dem_Timer_PollRateEngineRunTime = Dem_Cfg_TimerEngineRunTimePollRate();
  Dem_Timer_LastEngineRunTime = DEM_MEM_SET_ENGRUNTIME_INVALID(Dem_Timer_LastEngineRunTime);
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_TMC == STD_ON)
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_Timer_TimeSeriesNormalRate = Dem_Cfg_TimeSeriesNormalRate();
#  if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  Dem_Timer_TimeSeriesFastRate = Dem_Cfg_TimeSeriesFastRate();
#  endif
# endif
#endif /* DEM_FEATURE_NEED_OEM_EXTENSIONS_TMC */
}

/* ****************************************************************************
 % Dem_Timer_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Timer_MainFunction(
  void
  )
{

#if (DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON)
  --Dem_Timer_PollRateEngineRunTime;

  if (Dem_Timer_PollRateEngineRunTime == 0)
  {
    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_EngineRuntime);

    Dem_Timer_PollRateEngineRunTime = Dem_Cfg_TimerEngineRunTimePollRate();
  }
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_TMC == STD_ON)
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  --Dem_Timer_TimeSeriesNormalRate;

  if (Dem_Timer_TimeSeriesNormalRate == 0)
  {
    Dem_Queue_FetchTimeSeriesNormalRate = TRUE;
    Dem_Timer_TimeSeriesNormalRate = Dem_Cfg_TimeSeriesNormalRate();
  }

#  if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  --Dem_Timer_TimeSeriesFastRate;

  if (Dem_Timer_TimeSeriesFastRate == 0)
  {
    Dem_Queue_FetchTimeSeriesFastRate = TRUE;
    Dem_Timer_TimeSeriesFastRate = Dem_Cfg_TimeSeriesFastRate();
  }
#  endif
# endif
#endif
}

                                                                    /* Queue */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 % Dem_Queue_PreInit
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
Dem_Queue_PreInit(
  void
  )
{
}

/* ****************************************************************************
 % Dem_Queue_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_Init(
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_TimeSeries);
#endif
#if (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON)
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_Odometer);
#endif
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
  /* set flag for all readiness group supported by engine type to recalculate monitor state -> not supported groups will be set to N/A = completed*/
  if ((Dem_Cfg_GlobalPid01SupportedMask() & DEM_READINESS_SUPPORT_COMPRESSION) != 0)
  {
    Dem_Queue_SetPid01UpdateFlag(DEM_READINESS_INITIALIZE_UPDATE_COMPRESSION);
  }
  else
  {
    Dem_Queue_SetPid01UpdateFlag(DEM_READINESS_INITIALIZE_UPDATE_SPARK);
  }
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_PID01);
#endif
}

/* ****************************************************************************
 % Dem_Queue_ProcessIumpr
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessIumpr(
  void
  )
{
#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
  Dem_Cfg_ObdRatioIdIterType    lRatioIter;
  Dem_RatioIdIndexType          lRatioIndex;

  /* are general conditions available (i.e.: no input faults have been reported in this DCY)? */
  if (DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_FAILED(Dem_Mem_GetGeneralDenominatorStatus()) == FALSE)
  {
    /* check each ratio */
    for (Dem_Cfg_ObdRatioIdIterInit(&lRatioIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_ObdRatioIdIterExists(&lRatioIter) == TRUE;                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_ObdRatioIdIterNext(&lRatioIter))                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lRatioIndex = Dem_Cfg_ObdRatioIdIterGet(&lRatioIter);                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      /* check if update for this ratio is pending */
      if (Dem_Mem_IumprGetUpdatePending(lRatioIndex) == TRUE)
      {
        uint8           lRatioStatus;
        uint16          lDenominatorValue;
        uint16          lNumeratorValue;
        boolean         lUpdateNvM;
        boolean         lFaultPending;

        /* reset pending status of this ratio before checking the flags */
        Dem_Mem_IumprSetUpdatePending(lRatioIndex, FALSE);

        lRatioStatus      = Dem_Mem_GetIumprStatus(lRatioIndex);
        lDenominatorValue = Dem_Mem_GetDenominator(lRatioIndex);
        lNumeratorValue   = Dem_Mem_GetNumerator(lRatioIndex);
        lUpdateNvM        = FALSE;
        lFaultPending     = TRUE;

# if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
        if (DEM_ESM_TEST_IUMPR_DISCONNECTED(lRatioStatus) == FALSE)
# endif
        {
          /* check if ratio is not inhibited by FiM */
          if (DEM_ESM_TEST_IUMPR_FID_PENDING(lRatioStatus) == FALSE)
          {
            Dem_Cfg_ObdFimFidIterType lFIDIter;
            Std_ReturnType            lFiMStatus;

            /* until now, the FiM did not report a pending fault for this ratio; check again */
            for (Dem_Cfg_ObdFimFidIterInit(lRatioIndex, &lFIDIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
                 Dem_Cfg_ObdFimFidIterExists(&lFIDIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
                 Dem_Cfg_ObdFimFidIterNext(&lFIDIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
            {
              lFiMStatus = FiM_GetFunctionPendingStatus(Dem_Cfg_ObdFimFidIterGet(&lFIDIter), &lFaultPending);                    /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* SBSW_DEM_POINTER_FORWARD_STACK */

              /* if any FID inhibits the ratio, stop checking the FIDs and do not modify the ratio */
              if ((lFiMStatus == E_OK) && (lFaultPending == TRUE))
              {
                /* remember this FID status */
                /* Note: no interrupt lock needed; when FID is pending, the other status bits */
                /* become irrelevant as the ratio is blocked at least until the end of this cycle */
                lRatioStatus = DEM_ESM_SET_IUMPR_FID_PENDING(lRatioStatus);
                Dem_Mem_SetIumprStatus(lRatioIndex, lRatioStatus);
                Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                            DEM_NVM_BLOCKSTATE_DIRTY);
                break;
              }
            }
          }

          if (lFaultPending == FALSE)
          {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
            Dem_EnterCritical_DiagMonitor();                                                                                     /* PRQA S 3109 */ /* MD_MSR_14.3 */

            lRatioStatus = Dem_Mem_GetIumprStatus(lRatioIndex);

            /* --- Denominator --- */
            /* is denominator not yet incremented in this DCY and are the general and specific denominator conditions fulfilled? */
            if ( (DEM_ESM_TEST_IUMPR_DEN_INCREMENTED(lRatioStatus) == FALSE) &&                                    /* not yet incremented AND */
                 (DEM_ESM_TEST_IUMPR_DEN_LOCKED(lRatioStatus) == FALSE) &&                                         /* not locked AND */
                 (DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_REACHED(Dem_Mem_GetGeneralDenominatorStatus()) == TRUE) &&  /* general conditions fulfilled AND*/
                 (DEM_ESM_TEST_IUMPR_DEN_CONDITIONS_REACHED(lRatioStatus) == TRUE) )                               /* additional conditions fulfilled */
            {
              ++lDenominatorValue;
              lRatioStatus = DEM_ESM_SET_IUMPR_DEN_INCREMENTED(lRatioStatus);
              lUpdateNvM = TRUE;
            }

            /* --- Numerator --- */
            /* is numerator not yet incremented in this DCY and are the numerator conditions fulfilled? */
            if ( (DEM_ESM_TEST_IUMPR_NUM_INCREMENTED(lRatioStatus) == FALSE) &&                                 /* not yet incremented AND */
                 (DEM_ESM_TEST_IUMPR_NUM_FAULTDETECT(lRatioStatus) == TRUE) &&                                  /* conditions fulfilled AND */
                 (DEM_ESM_TEST_IUMPR_NUMERATORS_LOCKED(Dem_Mem_GetGlobalNumeratorsLocked()) == FALSE) )         /* numerators not locked for the current DCY */
            {
              ++lNumeratorValue;
              lRatioStatus = DEM_ESM_SET_IUMPR_NUM_INCREMENTED(lRatioStatus);
              lUpdateNvM = TRUE;
            }

            /* --- overflow check --- */
            /* divide by two if max value has been reached   [CCR1968.2 (g)(5.2.1)(C)] */
            if ( (lDenominatorValue == DEM_ESM_IUMPR_MAX_VALUE) ||
              (lNumeratorValue == DEM_ESM_IUMPR_MAX_VALUE) )
            {
              lDenominatorValue >>= 1;
              lNumeratorValue >>= 1;
            }

            /* --- update NvM --- */
            if (lUpdateNvM == TRUE)
            {
              Dem_Mem_SetIumprStatus(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), lRatioStatus);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
              Dem_Mem_SetDenominator(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), lDenominatorValue);                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
              Dem_Mem_SetNumerator(Dem_Cfg_ObdRatioIdIterGet(&lRatioIter), lNumeratorValue);                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */

              Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                          DEM_NVM_BLOCKSTATE_DIRTY);
            }

            Dem_LeaveCritical_DiagMonitor();                                                                                     /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
          }
          /* else: monitor function is inhibited by pending fault */
        }
        /* else: event is suppressed */
      }
      /* else: no update pending for this ratio */
    }
  }
  /* else: general conditions not yet reached; noting to do */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Queue_ProcessOdometer
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessOdometer(
  void
  )
{
#if (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON)
  boolean lFetchOdometer;

# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
  /* Check if the Odometer must be fetched from application */
  if (DEM_MEM_TEST_ODOMETER_ISINVALID(Dem_Mem_GetOdometerMilOn()) == TRUE)
  {
    lFetchOdometer = TRUE;
  }
  else
# endif
# if (DEM_CFG_SUPPORT_PID31 == STD_ON)
  /* Check if the Odometer must be fetched from application */
  if (DEM_MEM_TEST_ODOMETER_ISINVALID(Dem_Mem_GetOdometerAtClear()) == TRUE)
  {
    lFetchOdometer = TRUE;
  }
  else
# endif
# if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
  /* Check if the Odometer must be fetched from application */
  if (Dem_Mem_GetPermanentActivationState() == FALSE)
  {
    lFetchOdometer = TRUE;
  }
  else
# endif
  {
    lFetchOdometer = FALSE;
  }

  if (lFetchOdometer == TRUE)
  {
    uint32 lCurrentOdometer;

    if (Dem_Data_GetObdOdometer(&lCurrentOdometer) == E_OK)                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */
    { /* valid odometer, proceed */
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
      if (DEM_MEM_TEST_ODOMETER_ISINVALID(Dem_Mem_GetOdometerMilOn()) == TRUE)
      { /* dependent on the current MIL state the absolute odometer or the difference between current and stored odometer must be stored here */
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
        Dem_EnterCritical_NonAtomic32bit();                                                                                      /* PRQA S 3109 */ /* MD_MSR_14.3 */

        if (Dem_Indicator_TestMilReportedActive() == TRUE)
        { /* MIL is considered active, so the absolute value must be stored here */
          Dem_Mem_SetOdometerMilOn(lCurrentOdometer);
        }
        else
        { /* MIL is considered inactive, store difference */
          Dem_Mem_SetOdometerMilOn(lCurrentOdometer - DEM_MEM_RESET_ODOMETER_INVALID(Dem_Mem_GetOdometerMilOn()));
        }

        Dem_LeaveCritical_NonAtomic32bit();                                                                                      /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
      }
# endif
# if (DEM_CFG_SUPPORT_PID31 == STD_ON)
      if (DEM_MEM_TEST_ODOMETER_ISINVALID(Dem_Mem_GetOdometerAtClear()) == TRUE)
      { /* no valid odometer received until yet or Clear event occured, store current odometer */

/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
        Dem_EnterCritical_NonAtomic32bit();                                                                                      /* PRQA S 3109 */ /* MD_MSR_14.3 */
        Dem_Mem_SetOdometerAtClear(lCurrentOdometer);
        Dem_LeaveCritical_NonAtomic32bit();                                                                                      /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
      }
# endif
# if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
      if (Dem_Mem_GetPermanentActivationState() == FALSE)
      {
        uint32 lPermanentActivationDistance;

        lPermanentActivationDistance = Dem_Mem_GetPermanentActivationDistance();

        if (DEM_MEM_TEST_ODOMETER_ISINVALID(lPermanentActivationDistance) == FALSE)
        { /* target odometer value set, check if distance is reached */
          if (lCurrentOdometer > lPermanentActivationDistance)
          {
            (void)Dem_EnablePermanentStorage();
          } /* else: activation distance not yet reached */
        }
        else
        { /* no target odometer set, calculate and store now */
          lPermanentActivationDistance = (uint32)(lCurrentOdometer + Dem_Cfg_GlobalPermanentDtcRelActivationDist());
          Dem_Mem_SetPermanentActivationDistance(lPermanentActivationDistance);
        }
      }
# endif
    }
  }
#endif
}                                                                                                                                /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/* ****************************************************************************
% Dem_Queue_CalculatePid01
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
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculatePid01(
void
)
{
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
  /* If a flag of a readiness group is set  */
  if (Dem_Queue_Pid01UpdateFlag != 0)
  {
    Dem_EventIdType lEventId;
    uint8 lGroupIter;
    uint16 lPid01UpdateFlag;

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* set flag for all readiness group to recalculate monitor state -> not supported groups will be set to N/A = completed*/
    lPid01UpdateFlag = Dem_Queue_Pid01UpdateFlag;
    Dem_Queue_SetPid01UpdateFlag(0);

    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    /* Iterate over all primary events */
    for (lEventId = Dem_Cfg_GlobalPrimaryFirst(); lEventId <= Dem_Cfg_GlobalPrimaryLast(); lEventId++)
    {
      uint8 lReadinessGroup;

      /* If all flags are reset stop iterating events */
      if (lPid01UpdateFlag == 0)
      {
        break;
      }

      lReadinessGroup = Dem_Cfg_EventReadinessGroup(lEventId);

      /*comprehensive monitors are always reported as complete according to J1979DA)*/
      if ((lReadinessGroup == DEM_CFG_READINESS_FLSYS) || (lReadinessGroup == DEM_CFG_READINESS_CMPRCMPT))
      {
        continue;                                                                                                                /* PRQA S 0770 */ /* MD_DEM_14.5 */
      }

      /* If flag for event' readiness group is set */
      if (Dem_Esm_TestPid01ReadinessState(lPid01UpdateFlag, lReadinessGroup) == TRUE)
      {
        /* If event readiness group is already completed  */
        if (Dem_Data_TestReadinessGroupCompleted(lReadinessGroup, Dem_Mem_GetPid01CompletedMask()) == TRUE)
        {
          /* Reset flag for this group and continue with next event  */
          lPid01UpdateFlag = Dem_Esm_ResetPid01ReadinessState(lPid01UpdateFlag, lReadinessGroup);
          continue;                                                                                                              /* PRQA S 0770 */ /* MD_DEM_14.5 */
        }

        /* If event is available */
        if (Dem_Event_TestEventUnavailable(lEventId) == FALSE)
        {
          uint8 lDtcStatus;
          Dem_DTC_ExtendedStatusType lExtStatus;
          lDtcStatus = Dem_DTC_GetDTCStatus(lEventId);
          lExtStatus = Dem_Event_GetExtendedStatus(lEventId);

          /* If event is pending or event was not tested passed since last clear */
          if ( (Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(lExtStatus) == FALSE)                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
            || (Dem_UDSStatus_Test_PDTC(lDtcStatus) == TRUE))
          {
            /* Reset flag of this readiness group  */
            lPid01UpdateFlag = Dem_Esm_ResetPid01ReadinessState(lPid01UpdateFlag, lReadinessGroup);
          }
        }
      }
    }

    /* Start with first OBD readiness group */
    lGroupIter = 0U;

    /* For all flags that are still set change the related readiness group state to completed */
    while (lPid01UpdateFlag != 0)
    {
      if ((lGroupIter != DEM_CFG_READINESS_CMPRCMPT)                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (lGroupIter != DEM_CFG_READINESS_FLSYS)
          && (Dem_Esm_TestPid01ReadinessState(lPid01UpdateFlag, lGroupIter) == TRUE))
      {
        Dem_Util_SetReadinessGroupCompleted(TRUE, lGroupIter, &Dem_Mem_GetPid01CompletedMask());                                 /* SBSW_DEM_POINTER_FORWARD_GLOBAL */

        /* Reset flag of this readiness group  */
        lPid01UpdateFlag = Dem_Esm_ResetPid01ReadinessState(lPid01UpdateFlag, lGroupIter);                                       /* PRQA S 0290 */ /* MD_DEM_21.1_Always_Negative */
      }

      lGroupIter++;
    }
  }
#endif
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_PID4D == STD_ON)
/* ****************************************************************************
 % Dem_Queue_CalculatePid4D
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculatePid4D(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  )
{
  if (Dem_Indicator_TestMilReportedActive() == TRUE)
  { /* Always increment if MIL is on and latch/ don't count if MIL is off */
    uint32 lPid4D;  /* intentionally uint32 to avoid an overflow */

    lPid4D = Dem_Mem_GetEngineTimeMilOn();

    if (lPid4D < 0xffffU)
    {
      lPid4D = lPid4D + EngineRunTimeTicks;

      if (lPid4D > 0xffffU)
      { /* latch at 0xffff */
        lPid4D = 0xffffU;
      }

      Dem_Mem_SetEngineTimeMilOn((uint16)lPid4D);
    }
  }
}
#endif

#if (DEM_CFG_SUPPORT_PID4E == STD_ON)
/* ****************************************************************************
 % Dem_Queue_CalculatePid4E
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculatePid4E(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  )
{
  uint32 lPid4E; /* intentionally uint32 to avoid an overflow */

  lPid4E = Dem_Mem_GetEngineTimeSinceClear();

  if (lPid4E < 0xffffU)
  {
    lPid4E = lPid4E + EngineRunTimeTicks;

    if (lPid4E > 0xffffU)
    { /* latch at 0xffff */
      lPid4E = 0xffffU;
    }

    Dem_Mem_SetEngineTimeSinceClear((uint16)lPid4E);
  }
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Queue_CalculateB1Counter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculateB1Counter(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  )
{
  uint32 lB1Counter;

  lB1Counter = Dem_Mem_GetB1Counter();

  /* increment B1Counter if at least one B1 event is confirmed and failed */
  if (Dem_Indicator_GetQualifiedActiveEventCount(DEM_ESM_WWHOBD_DTCCLASS_B1) != 0)
  {
    if (lB1Counter < DEM_DATA_B1COUNTER_LATCHED)
    { /* Latch B1Counter if >= 255h (15300min) */
      lB1Counter = lB1Counter + EngineRunTimeTicks;

      if (lB1Counter > DEM_DATA_B1COUNTER_LATCHED)
      { /* latch at 255h */
        lB1Counter = DEM_DATA_B1COUNTER_LATCHED;
      }

      Dem_Mem_SetB1Counter((uint16)lB1Counter);
    }
  }
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Queue_ProcessContinuousMiCounter
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessContinuousMiCounter(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  )
{
  uint32 lContinuousMiCounter;

  lContinuousMiCounter = Dem_Mem_GetContinuousMiCounter();

  /* increment continuous MI counter as long as activation mode 4 is active */
  if (Dem_Indicator_GlobalIndicatorActivationMode() == DEM_INDICATOR_CONTINUOUS)
  {
    if ( (Dem_Mem_GetContinuousMiHealingCounter() < DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED)
      || (Dem_Mem_GetContinuousMiHealingCounter() == DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_LOCKED) )
    { /* Healing is active or in preparation: Reset/leave healing */
      Dem_Mem_SetContinuousMiHealingCounter(DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_INVALID);
    }
    else
    if ( (Dem_Mem_GetContinuousMiAgingCounter() < DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED)
      || (Dem_Mem_GetContinuousMiAgingTimer() < DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED) )
    { /* Aging is active: Reset/leave aging and reset continuous MI counter*/
      Dem_Mem_SetContinuousMiAgingCounter(DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_INVALID);
      Dem_Mem_SetContinuousMiAgingTimer(DEM_DATA_CONTINUOUS_MI_AGING_TIMER_INVALID);
      Dem_Mem_SetContinuousMiHealingCounter(DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_INVALID);
      lContinuousMiCounter = 0;
    }
    else
    { /* Not Healing and not Aging: reset all states if continuous MI counter is currently stopped */
      if (Dem_Mem_GetContinuousMiHealingCounter() == DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED)
      {
        Dem_Mem_SetContinuousMiAgingCounter(DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_INVALID);
        Dem_Mem_SetContinuousMiAgingTimer(DEM_DATA_CONTINUOUS_MI_AGING_TIMER_INVALID);
        Dem_Mem_SetContinuousMiHealingCounter(DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_INVALID);
      }
    }

    if (lContinuousMiCounter < DEM_DATA_CONTINUOUS_MI_LATCHED)
    { /* Latch ContinuousMiCounter if >= 255h (15300min) */
      lContinuousMiCounter = lContinuousMiCounter + EngineRunTimeTicks;

      if (lContinuousMiCounter > DEM_DATA_CONTINUOUS_MI_LATCHED)
      { /* latch at 255h */
        lContinuousMiCounter = DEM_DATA_CONTINUOUS_MI_LATCHED;
      }

      Dem_Mem_SetContinuousMiCounter((uint16)lContinuousMiCounter);
    }
  }
  else
  {
    uint32 lContinuousMiCounterAgingTime;

    lContinuousMiCounterAgingTime = Dem_Mem_GetContinuousMiAgingTimer();

    if (lContinuousMiCounterAgingTime < DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED)
    {/* Aging is active: process aging timer */
      lContinuousMiCounterAgingTime = lContinuousMiCounterAgingTime + EngineRunTimeTicks;

      if (lContinuousMiCounterAgingTime >= DEM_DATA_CONTINUOUS_MI_200H)
      { /* Aging time exceeded, reset Continuous MI counter */
        lContinuousMiCounterAgingTime = DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED;
        Dem_Mem_SetContinuousMiAgingCounter(DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED);
        Dem_Mem_SetContinuousMiCounter(0);
      }
      Dem_Mem_SetContinuousMiAgingTimer((uint16)lContinuousMiCounterAgingTime);
    }
  }
}                                                                                                                                /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Queue_ProcessAgingTimer
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
Dem_Queue_ProcessAgingTimer(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  )
{
  uint32 lCumulativeEngineRuntime;
  Dem_Memory_MemEntryIterType MemEntryIter;

  lCumulativeEngineRuntime = Dem_Mem_GetCumulativeEngRuntime();
  lCumulativeEngineRuntime = lCumulativeEngineRuntime + EngineRunTimeTicks;
  Dem_Mem_SetCumulativeEngRuntime(lCumulativeEngineRuntime);

  /* Check for all OBD events in primary memory if they are currently in aging process and if aging time has exceeded */

  for (Dem_Memory_MemEntry_IterInit(DEM_CFG_MEMORYID_PRIMARY, &MemEntryIter);                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&MemEntryIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&MemEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
      if ( (Dem_Cfg_EventObdRelated(lEventId) == TRUE)                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_Cfg_EventSupportAging(lEventId) == TRUE) )
      {
        if (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId)) == Dem_DTCInternalStatus_StoredStatus_Aging)
        { /* Event is currently aging */
          if (lCumulativeEngineRuntime >= Dem_MemoryEntry_GetAgingTimer(lMemoryEntryId))
          { /* Aging time reached, so this event has aged */
            Dem_DTC_Aged(lEventId, lMemoryIndex);
          }
        }
      }
    }
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

/* ****************************************************************************
 % Dem_Queue_ProcessEngineRuntime
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessEngineRuntime(
  void
  )
{
#if (DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (Dem_Cfg_ObdEngineRunTime() >= Dem_Cfg_GlobalDataElementCount())                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataIsStoredInNV(Dem_Cfg_ObdEngineRunTime()) == FALSE)
    || (Dem_Cfg_DataCallbackType(Dem_Cfg_ObdEngineRunTime()) != DEM_CFG_DATA_FROM_CBK)
    || (Dem_Cfg_DataSize(Dem_Cfg_ObdEngineRunTime()) != 4) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint8 lBuffer[4];
    if ((*((Dem_ReadDataStandardFPtrType)Dem_Cfg_DataCbkRead(Dem_Cfg_ObdEngineRunTime())))(&lBuffer[0]) == E_OK)                 /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_LOCAL_DESTINATIONBUFFER */
    { /* calculate passed engine run time (resolution 1min/bit)*/
      uint32 lTotalEngineRunTime;
      uint32 lEngineRunTimeDelta;

      lTotalEngineRunTime = Dem_Make32Bit(lBuffer[0], lBuffer[1], lBuffer[2], lBuffer[3]);

      if (DEM_MEM_TEST_ENGRUNTIME_ISINVALID(Dem_Timer_LastEngineRunTime) == TRUE)
      { /* initial reception of the engine runtime signal in this power cycle */
        lEngineRunTimeDelta = 0;
      }
      else
      if (Dem_Timer_LastEngineRunTime <= lTotalEngineRunTime)
      { /* same engine run, delta is [Dem_Timer_LastEngineRunTime, lNewEngineRunTime] */
        lEngineRunTimeDelta = lTotalEngineRunTime - Dem_Timer_LastEngineRunTime;
      }
      else
      { /* else: engine restart, delta is [0, lNewEngineRunTime] */
        lEngineRunTimeDelta = lTotalEngineRunTime;
      }

      if (lEngineRunTimeDelta != 0)
      { /* one or more engine run time minutes have passed, process dependent active timers */
# if (DEM_CFG_SUPPORT_PID4D == STD_ON)
        Dem_Queue_CalculatePid4D(lEngineRunTimeDelta);
# endif
# if (DEM_CFG_SUPPORT_PID4E == STD_ON)
        Dem_Queue_CalculatePid4E(lEngineRunTimeDelta);
# endif
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
        Dem_Queue_CalculateB1Counter(lEngineRunTimeDelta);
        Dem_Queue_ProcessContinuousMiCounter(lEngineRunTimeDelta);
        Dem_Queue_ProcessAgingTimer(lEngineRunTimeDelta);
# endif
      }
      Dem_Timer_LastEngineRunTime = lTotalEngineRunTime;
    }
    else
    {
      /* Could not read the Enginge Run Time from the application - Try again next cycle */
      Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_EngineRuntime);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Queue_ProcessTimeSeries
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessTimeSeries(
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
# if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
  uint8 lSampleUpdate;

  lSampleUpdate = DEM_DATA_NO_SAMPLE_UPDATE;
# endif

  if (Dem_Queue_FetchTimeSeriesNormalRate == TRUE)
  {
    Dem_Queue_FetchTimeSeriesNormalRate = FALSE;
# if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
    lSampleUpdate = DEM_DATA_SET_NORMAL_SAMPLE_UPDATE(lSampleUpdate);
# endif

    Dem_DataStorageIF_CollectTimeSeriesNormalSamples();
  }

# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  if (Dem_Queue_FetchTimeSeriesFastRate == TRUE)
  {
    Dem_Queue_FetchTimeSeriesFastRate = FALSE;
# if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
    lSampleUpdate = DEM_DATA_SET_FAST_SAMPLE_UPDATE(lSampleUpdate);
# endif

    Dem_DataStorageIF_CollectTimeSeriesFastSamples();
  }
# endif

# if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
  if (lSampleUpdate != DEM_DATA_NO_SAMPLE_UPDATE)
  {
    Dem_Data_StoreTimeSeriesFutureSamples(lSampleUpdate);
  }
# endif
#endif
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_QUEUE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Queue_Implementation.h
 *********************************************************************************************************************/
