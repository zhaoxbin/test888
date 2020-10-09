/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \ingroup    Os_Hal
 *  \defgroup   Os_Hal_MemoryProtection  HAL Memory Protection
 *  \brief      Internal functions and data types related to memory protection.
 *  \details
 *
 *  \note Consider Memory barriers and sync instructions.
 *
 *  \{
 *
 *  \file       Os_Hal_MemoryProtectionInt.h
 *  \brief
 *
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
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_MEMORYPROTECTIONINT_H
# define OS_HAL_MEMORYPROTECTIONINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_MemoryProtection_Types.h"

/* Os kernel module dependencies */
# include "Os_CommonInt.h"

/* Os HAL dependencies */
# include "Os_Hal_CompilerInt.h"
# include "Os_Hal_MemoryProtection_Cfg.h"


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Platform specific configuration type of a single MPU region. */
typedef struct
{
  uint32 RegionStart;       /*!< Start address of the MPU region. */
  uint32 RegionEnd;         /*!< End address of the MPU region. */
  uint32 RegionAttribute;   /*!< Access rights of the MPU region. */
} Os_Hal_MpuRegionType;

/*! \brief    System wide memory protection configuration.
 *  \details
 *  The kernel uses this data type to initialize access rights for different bus masters (cores, DMAs, etc.).
 *  These are typically MPU, MMU or PPU settings such as region descriptors.
 */
struct Os_Hal_MpSystemConfigType_Tag
{
  uint32 MpuRegionCount; /*!< Number of system MPU regions */
};


/*! \brief    Memory protection configuration of a core.
 *  \details  The kernel uses this data type to initialize access rights of a core.
 *            These are typically MPU, MMU or PPU settings such as region descriptors.
 */
struct Os_Hal_MpCoreConfigType_Tag
{
  uint32 MpuRegionCount;              /*!< Number of core local MPU regions. */
  uint32 MpuRegionID;

  Os_Hal_MpuRegionType MpuRegion0;    /*!< Configuration information of MPU region 0. */
  Os_Hal_MpuRegionType MpuRegion1;    /*!< Configuration information of MPU region 1. */
  Os_Hal_MpuRegionType MpuRegion2;    /*!< Configuration information of MPU region 2. */
  Os_Hal_MpuRegionType MpuRegion3;    /*!< Configuration information of MPU region 3. */

  Os_Hal_MpuRegionType MpuRegion4;    /*!< Configuration information of MPU region 4. */
  Os_Hal_MpuRegionType MpuRegion5;    /*!< Configuration information of MPU region 5. */
  Os_Hal_MpuRegionType MpuRegion6;    /*!< Configuration information of MPU region 6. */
  Os_Hal_MpuRegionType MpuRegion7;    /*!< Configuration information of MPU region 7. */

  Os_Hal_MpuRegionType MpuRegion8;    /*!< Configuration information of MPU region 8. */
  Os_Hal_MpuRegionType MpuRegion9;    /*!< Configuration information of MPU region 9. */
  Os_Hal_MpuRegionType MpuRegion10;   /*!< Configuration information of MPU region 10. */
  Os_Hal_MpuRegionType MpuRegion11;   /*!< Configuration information of MPU region 11. */

  Os_Hal_MpuRegionType MpuRegion12;   /*!< Configuration information of MPU region 12. */
  Os_Hal_MpuRegionType MpuRegion13;   /*!< Configuration information of MPU region 13. */
  Os_Hal_MpuRegionType MpuRegion14;   /*!< Configuration information of MPU region 14. */
  Os_Hal_MpuRegionType MpuRegion15;   /*!< Configuration information of MPU region 15. */

  Os_Hal_MpuRegionType MpuRegion16;   /*!< Configuration information of MPU region 16. */
  Os_Hal_MpuRegionType MpuRegion17;   /*!< Configuration information of MPU region 17. */
  Os_Hal_MpuRegionType MpuRegion18;   /*!< Configuration information of MPU region 18. */
  Os_Hal_MpuRegionType MpuRegion19;   /*!< Configuration information of MPU region 19. */

  Os_Hal_MpuRegionType MpuRegion20;   /*!< Configuration information of MPU region 20. */
  Os_Hal_MpuRegionType MpuRegion21;   /*!< Configuration information of MPU region 21. */
  Os_Hal_MpuRegionType MpuRegion22;   /*!< Configuration information of MPU region 22. */
  Os_Hal_MpuRegionType MpuRegion23;   /*!< Configuration information of MPU region 23. */

  Os_Hal_MpuRegionType MpuRegion24;   /*!< Configuration information of MPU region 24. */
  Os_Hal_MpuRegionType MpuRegion25;   /*!< Configuration information of MPU region 25. */
  Os_Hal_MpuRegionType MpuRegion26;   /*!< Configuration information of MPU region 26. */
  Os_Hal_MpuRegionType MpuRegion27;   /*!< Configuration information of MPU region 27. */

  Os_Hal_MpuRegionType MpuRegion28;   /*!< Configuration information of MPU region 28. */
  Os_Hal_MpuRegionType MpuRegion29;   /*!< Configuration information of MPU region 29. */
  Os_Hal_MpuRegionType MpuRegion30;   /*!< Configuration information of MPU region 30. */
  Os_Hal_MpuRegionType MpuRegion31;   /*!< Configuration information of MPU region 31. */
};


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if 0
/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  Os_Hal_MpSystemInit()
 **********************************************************************************************************************/
/*! \brief          Initialize the system memory protection.
 *  \details        Initializes system's memory protection mechanism and set the passed memory protection settings for
 *                  the system. This function is called once on the master core during OS initialization.
 *                  It typically initializes and enables any system related protection mechanism (system MPU/MMU/PPU).
 *
 *  \param[in]      SystemConfig  Configuration for system's memory protection mechanism.
 *                                Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            Supervisor mode.
 *  \pre            Executed on master core.
 **********************************************************************************************************************/
FUNC(void, OS_CODE) Os_Hal_MpSystemInit(P2CONST(Os_Hal_MpSystemConfigType, TYPEDEF, OS_CONST) SystemConfig);


/***********************************************************************************************************************
 *  Os_Hal_MpCoreInit()
 **********************************************************************************************************************/
/*! \brief          Initialize the core memory protection.
 *  \details        Initializes the core's memory protection mechanism and set the passed memory protection settings
 *                  for the core. This function is called once on each core during OS initialization.
 *                  It typically initializes and enables any core related protection mechanism (system MPU/MMU/PPU).
 *
 *  \param[in]      CoreConfig          Core configuration for memory protection mechanism. Parameter must not be NULL.
 *
 *  \param[in]      InitialStackRegion  Stack configuration for memory protection mechanism. Used to set the initially
 *                                      open stack window. Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            Supervisor mode.
 **********************************************************************************************************************/
FUNC(void, OS_CODE) Os_Hal_MpCoreInit
(
  P2CONST(Os_Hal_MpCoreConfigType, TYPEDEF, OS_CONST) CoreConfig,
  P2CONST(Os_Hal_ContextStackConfigType, AUTOMATIC, OS_VAR_NOINIT) InitialStackRegion
);


/***********************************************************************************************************************
 *  Os_Hal_MpAppSwitch()
 **********************************************************************************************************************/
/*! \brief          Switches application related access rights.
 *  \details        Switches the current memory protection settings to the passed ones.
 *
 *  \param[in]      AppConfig   Configuration for application's memory protection mechanism.
 *                              Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *  \pre            Supervisor mode.
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_MpAppSwitch,
(
  P2CONST(Os_Hal_MpAppConfigType, TYPEDEF, OS_CONST) AppConfig
));


/***********************************************************************************************************************
 *  Os_Hal_MpThreadSwitch()
 **********************************************************************************************************************/
/*! \brief          Switches thread related access rights.
 *  \details        Switches the current memory protection settings to the passed ones.
 *
 *  \param[in]      ThreadConfig   Configuration for thread's memory protection mechanism.
 *                                 Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *  \pre            Supervisor mode.
 *  \pre            Application rights are switched (see \ref Os_Hal_MpAppSwitch()).
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_MpThreadSwitch,
(
  P2CONST(Os_Hal_MpThreadConfigType, TYPEDEF, OS_CONST) ThreadConfig
));


/***********************************************************************************************************************
 *  Os_Hal_MpuConfigSwitch()
 **********************************************************************************************************************/
/*! \brief          Reconfigures all MPU regions.
 *  \details        --no details--
 *
 *  \param[in]      MpuConfig      Configuration for memory protection mechanism.
 *                                 Parameter must not be NULL.
 *
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts disabled.
 *  \pre            Supervisor mode.
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_MpuConfigSwitch,
(
  P2CONST(Os_Hal_MpCoreConfigType, TYPEDEF, OS_CONST) MpuConfig
));


/***********************************************************************************************************************
 *   Os_Hal_Set_MemRegionID()
 **********************************************************************************************************************/
/*! \brief          Sets memory region ID register to given value (ASID for G3X cores, SPID for G4X cores).
 *  \details        --no details--
 *
 *  \param[in]      value          Value to be set to memory region ID register.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts disabled.
 *  \pre            Supervisor mode.
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_Set_MemRegionID,
(
  VAR(uint32, OS_VAR_NOINIT) value
));


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_MEMORYPROTECTIONINT_H */

#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_MemoryProtectionInt.h
 **********************************************************************************************************************/

