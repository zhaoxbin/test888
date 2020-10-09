############################################################################### 
# File Name  : Crc_defs.mak 
# Description: Public makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Refer to the Crc_rules.mak file.
############################################################################### 

###############################################################
# INTERNAL REQUIRED CONFIGURATION (in can_cfg.mak)
#
# CRC_MODULES 	    (required)  (not necessary for Vector)
# CRC_DRIVER_MODE   (required)  (not necessary for Vector)
# CRC_PROJECT_PATH  (optional)
# CRC_BUILD_LIBRARY (required)


###############################################################
# REQUIRED (defined in base_make)
#
# PROJECT_ROOT
# SSC_ROOT
###############################################################


###############################################################
# SPECIFIC
# Specific variables which were defined here are only for local use in this Makefile
# if for example additional includes are necessary, these vars can be defined and used in the REGISTRY-Part.
# e.g.: $(CAN_CORE_PATH) = $(SSC_ROOT)\Can  could be used for CPP_INCLUDE_PATH    +=  $(CAN_CORE_PATH)\CPP_FILES\...


CRC_CORE_PATH       =   $(SSC_ROOT)\Crc

CRC_OUTPUT_PATH     =   $(GENDATA_DIR)


#CRC_TOOL_PATH       = $(PROJECT_ROOT)\core\com\can\gentool



###############################################################
# REGISTRY
#
# $(SSC_PLUGINS) is a list of the components. Here can is added (not necessary for Vector, whole component-list also exists in Global.makefile.target.make...)
#
SSC_PLUGINS        +=
CRC_DEPENDENT_PLUGINS =

#-----------------------------------------------------------------------------------------
# MakeSupport usually includes all header-files which were in the same
# directory as the source-files automatically, but to ensure that the
# Asr-Makefiles will also work with other Basic-Make-Packages,
# it is necessary to define all include directories for this Module
# e.g.: CC_INCLUDE_PATH     += $(CAN_CORE_PATH)
#------------------------------------------------------------------------------------------
CC_INCLUDE_PATH     +=  $(CRC_CORE_PATH)  $(CRC_OUTPUT_PATH)
CPP_INCLUDE_PATH    +=
ASM_INCLUDE_PATH    +=


###############################################################
# PROVIDE
#
# A Public Makefile does not provide resources for other basic
# software bundles or the base_make package.
###############################################################
