############################################################################### 
# File Name  : Crc_cfg.mak 
# Description: Configuration makefile 
#------------------------------------------------------------------------------
# COPYRIGHT
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Vector Informatik GmbH.  All rights reserved.
#------------------------------------------------------------------------------
# REVISION HISTORY
#------------------------------------------------------------------------------
# Refer to the Crc_rules.mak file.
############################################################################### 

##############################################################
# CRC_CONFIG_PATH: (not used for Vector)
# The Variable CRC_CONFIG_PATH is optional. It allows the
# configuration of the directory, where you can also find the
# generated source files. Generally they should be in the
# directory $(PROJECT_ROOT)\source\networks.
# But if the application should run on several hardware
# targets, then different CRC configurations of different
# directories will be necessary. Therefor the variable
# CRC_CONFIG_PATH should be used.
#
# For example:
# CRC_CONFIG_PATH = $(PROJECT_ROOT)\source\network\v850
# CRC_CONFIG_PATH = $(PROJECT_ROOT)\source\network\st10
# CRC_CONFIG_PATH = $(PROJECT_ROOT)\source\network\v850
#

#CRC_CONFIG_PATH =


##############################################################
# CRC_DRIVER_MODE:  (not used for Vector)
# Not relevant for module CRC, leave it as it is.
#
# For example:
# CRC_DRIVER_MODE = singlechannel/multichannel
#

#CRC_DRIVER_MODE = singlechannel


###############################################################
# REQUIRED
#
# No Other resources are required to write a Configuration
# Makefile.
#
###############################################################


###############################################################
# PROVIDE
#
# A Configuration Makefile does not provide resources for other
# basic software bundles or the base_make package
#
###############################################################


###############################################################
# REGISTRY
#
# Like the Provide-Section this block is empty.
#
###############################################################


###############################################################
# SPECIFIC
#
# All variables in the _cfg makefile are "Specific" variables,
# because they should only be used in the *_check.mak,
# *_defs.mak and *_rules.mak Makefiles of the same basic
# software bundle.
###############################################################
