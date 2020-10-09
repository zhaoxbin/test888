
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsMainStartup.h
      Project:  Vector Basic Runtime System
       Module:  BrsMain

  \brief Description:  Vector Basic Runtime System module header for startup routines.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

#ifndef _BRSMAINSTARTUP_H_
#define _BRSMAINSTARTUP_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/*
 * Description: The BrsCfg header provides all the necessary configuration switches of the BRS.
 *              It is either a template file or generated out of Configurator 5.
 */
#include "vBrsCfg.h"

/**********************************************************************************************************************
  MODULE VERSION
**********************************************************************************************************************/
/*
 * Description: This is the BrsHw main and bug fix version. The version numbers are BCD coded. 
 *              E.g. a main version of 1.23 is coded with 0x0123, a bug fix version of 9 is coded 0x09.
 */
#define BRSMAINSTARTUP_VERSION        0x0103u
#define BRSMAINSTARTUP_BUGFIX_VERSION 0x00u

/**********************************************************************************************************************
  GLOBAL TYPE DEFINITIONS
**********************************************************************************************************************/

typedef struct {
  uint32 start; /*start address of the zero ram area */
  uint32 end;   /*end address of the zero ram area */
  uint8  core;  /*the core that shall execute the init */
} brsZeroRamArea;

typedef struct {
  uint32 start;    /* start address of the ram area */
  uint32 end;      /* end address of the ram area */
  uint32 romstart; /* start address of the init data in rom */
  uint32 romend;   /* end address of the init data in rom */
  uint8  core;     /* the core that shall execute the init */
} brsInitRamArea;

typedef struct {
  uint8 num;             /* number of areas */
  const brsZeroRamArea *areas;  /* pointer to the first area */
} brsZeroRamAreaSet;

typedef struct {
  uint8 num;             /* number of areas */
  const brsInitRamArea *areas;  /* pointer to the first area */
} brsInitRamAreaSet;

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
void Brs_PreMainStartup(void);
void Brs_RamZeroInit (const brsZeroRamAreaSet *memAreaSet, uint32 coreId);
void Brs_RomToRamInit (const brsInitRamAreaSet *memAreasSet, uint32 coreId);

#endif /*_BRSMAINSTARTUP_H_*/