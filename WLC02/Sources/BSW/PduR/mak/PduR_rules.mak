############################################################################### 
# File Name  : PduR_rules.mak 
# Description: Rules makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Version   Date        Author  Description
#------------------------------------------------------------------------------
# 1.00.00   2011-11-30  ms      initial CFG5 version derived from Gw_AsrPduR Version 1.00.02
# 2.00.00   2018-01-31  visfrm  TASK-62823: Add new Buffer Manager C-File to Make File Rules
# 3.00.00   2018-03-02  visspt  STORYC-3238: Analyze Core Specific RMW Variable Usage Step2
# 4.00.00   2018-05-09  visfrm  STORYC-3241: Implement Multicore Support
# 5.00.00   2018-12-21  visfrm  STORYC-6442: Implement & Test simple IF FIFO
# 5.01.00   2019-02-06  vircbl  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################


###############################################################
# REGISTRY
#

#e.g.: LIBRARIES_TO_BUILD      +=    $(LIB_OUPUT_PATH)\vendorx_canlib1.$(LIB_FILE_SUFFIX)
LIBRARIES_TO_BUILD      += PduR
PduR_FILES               = PduR$(BSW_SRC_DIR)\PduR.c 
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_Sm.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_Bm.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_Fm.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_RmTp.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_RmIf.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_RmTp_TxInst.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_Lock.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_McQ.c
PduR_FILES              += PduR$(BSW_SRC_DIR)\PduR_IFQ.c

# e.g.: CC_FILES_TO_BUILD       += drv\can_drv.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR.c 
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_Sm.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_Bm.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_Fm.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_RmTp.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_RmIf.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_RmTp_TxInst.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_Lock.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_McQ.c
CC_FILES_TO_BUILD       += PduR$(BSW_SRC_DIR)\PduR_IFQ.c
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

#LIBRARIES_LINK_ONLY     += (not yet supported)
#OBJECTS_LINK_ONLY       += (not yet supported)

#-------------------------------------------------------------------------------------------------
#only define new dirs, OBJ, LIB, LOG were created automaticly 
#-------------------------------------------------------------------------------------------------
DIRECTORIES_TO_CREATE   +=

#DEPEND_GCC_OPTS         += (not yet supported)

# e.g.:  GENERATED_SOURCE_FILES += $(GENDATA_DIR)\drv_par.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\PduR_PBcfg.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\PduR_Lcfg.c
#Future use: $(GENDATA_DIR)\PduR_Cfg.c

#e.g.: COMMON_SOURCE_FILES     += $(GENDATA_DIR)\v_par.c
COMMON_SOURCE_FILES     += 

#-------------------------------------------------------------------------------------------------
# <project>.dep & <projekt>.lnk & <project>.bin and.....
# all in err\ & obj\ & lst\ & lib\ & log\ will be deleted by clean-rule automaticly
# so in this clean-rule it is only necessary to define additional files which
# were not delete automaticly.
# e.g.: $(<PATH>)\can_test.c
#-------------------------------------------------------------------------------------------------
MAKE_CLEAN_RULES        +=
#MAKE_GENERATE_RULES     +=
#MAKE_COMPILER_RULES     +=
#MAKE_DEBUG_RULES        +=
#MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES          +=


###############################################################
# REQUIRED   (defined in BaseMake (global.Makefile.target.make...))
#
# SSC_ROOT		(required)
# PROJECT_ROOT	(required)
#
# LIB_OUTPUT_PATH	(optional)
# OBJ_OUTPUT_PATH	(optional)
#
# OBJ_FILE_SUFFIX	
# LIB_FILE_SUFFIX
#
###############################################################


###############################################################
# PROVIDE   this Section can be used to define own additional rules
#
# In vendorx_can_cfg.mak:
# Please configure the project file:
#CAN_CONFIG_FILE = $(PROJECT_ROOT)\source\network\can\my_can_config.cfg

#In vendorx_can_config :
#generate_can_config:
#$(SSC_ROOT)\core\com\can\tools\canconfiggen.exe -o $(CAN_CONFIG_FILE)


###############################################################
# SPECIFIC
#
# There are no rules defined for the Specific part of the 
# Rules-Makefile. Each author is free to create temporary 
# variables or to use other resources of GNU-MAKE
#
###############################################################


