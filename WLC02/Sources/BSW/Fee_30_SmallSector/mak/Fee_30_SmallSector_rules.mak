############################################################################### 
# File Name  : Fee_30_SmallSector_rules.mak 
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
# 1.00.00   2016-06-21  Gmi     Initial Version
# 1.01.00   2019-02-06  vircbl  Added support of component-based SIP structure
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################


###############################################################
# REGISTRY
#

#e.g.: LIBRARIES_TO_BUILD      +=    $(LIB_OUPUT_PATH)\vendorx_canlib1.$(LIB_FILE_SUFFIX)
LIBRARIES_TO_BUILD      += Fee_30_SmallSector
Fee_30_SmallSector_FILES = Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_PartitionHandler.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_BlockHandler.c \
Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_DatasetHandler.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_InstanceHandler.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_TaskManager.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_FlsCoordinator.c \
Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer1_Read.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer1_Write.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer2_WriteInstance.c  \
Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer2_DatasetEraser.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer2_InstanceFinder.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer3_ReadManagementBytes.c 




# e.g.: CC_FILES_TO_BUILD       += drv\can_drv.c
CC_FILES_TO_BUILD       += Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_PartitionHandler.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_BlockHandler.c \
Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_DatasetHandler.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_InstanceHandler.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_TaskManager.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_FlsCoordinator.c \
Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer1_Read.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer1_Write.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer2_WriteInstance.c \
Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer2_DatasetEraser.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer2_InstanceFinder.c Fee_30_SmallSector$(BSW_SRC_DIR)\Fee_30_SmallSector_Layer3_ReadManagementBytes.c
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

#LIBRARIES_LINK_ONLY     += (not yet supported)
#OBJECTS_LINK_ONLY       += (not yet supported)

#-------------------------------------------------------------------------------------------------
#only define new dirs, OBJ, LIB, LOG were created automatically
#-------------------------------------------------------------------------------------------------
DIRECTORIES_TO_CREATE   +=

#DEPEND_GCC_OPTS         += (not yet supported)

# e.g.:  GENERATED_SOURCE_FILES += $(GENDATA_DIR)\drv_par.c
GENERATED_SOURCE_FILES  +=  $(GENDATA_DIR)\Fee_30_SmallSector_Cfg.c


#e.g.: COMMON_SOURCE_FILES     += $(GENDATA_DIR)\v_par.c
COMMON_SOURCE_FILES     +=

#-------------------------------------------------------------------------------------------------
# <project>.dep & <projekt>.lnk & <project>.bin and.....
# all in err\ & obj\ & lst\ & lib\ & log\ will be deleted by clean-rule automatically
# so in this clean-rule it is only necessary to define additional files which
# were not delete automatically.
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


