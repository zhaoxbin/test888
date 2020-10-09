###############################################################################
# File Name  : Os_rules.mak
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
# 1.00.00   2016-03-24  Dfe     Initial Version
# 1.01.00   2016-05-10  Asl     Adaption for Rh850
# 1.02.00   2016-05-10  Asl     Adaption for Rh850
# 1.03.00   2017-07-12  Ces     Added Os_Hal_INTC.c
# 1.04.00   2018-01-18  To      added Os_Hal_Context.c
# 2.00.00   2019-02-06  vircbl  Added support of component-based SIP structure
# 2.00.01   2019-02-11  Rework  to match the template
# 2.00.02   2019-02-11  Rework  to match the template
# 2.00.03   2019-02-18  virsmn  ESCAN00102140
# 2.00.04   2019-03-08  virrlu  ESCAN00102357
#------------------------------------------------------------------------------
# TemplateVersion = 1.02
###############################################################################

# Include of OS Core makefile

include $(ROOT)\$(GLOBAL_COMP_DIR)\Os\$(if $(BSW_MAKE_DIR),$(BSW_MAKE_DIR),mak)\Os_Core.mak


# Component Files

CC_FILES_TO_BUILD          +=  Os$(BSW_SRC_DIR)\Os_Hal_Context.c             \
                               Os$(BSW_SRC_DIR)\Os_Hal_Core.c                \
                               Os$(BSW_SRC_DIR)\Os_Hal_MemoryProtection.c    \
                               Os$(BSW_SRC_DIR)\Os_Hal_INTC.c

ASM_FILES_TO_BUILD         +=  Os$(BSW_SRC_DIR)\Os_Hal_Entry.asm             \
                               Os$(BSW_SRC_DIR)\Os_Hal_Trap.asm

GENERATED_SOURCE_FILES     +=  $(GENDATA_DIR)\Os_Hal_Context_Lcfg.c          \
                               $(GENDATA_DIR)\Os_Hal_Core_Lcfg.c             \
                               $(GENDATA_DIR)\Os_Hal_Entry_Lcfg.c            \
                               $(GENDATA_DIR)\Os_Hal_Interrupt_Lcfg.c        \
                               $(GENDATA_DIR)\Os_Hal_Kernel_Lcfg.c           \
                               $(GENDATA_DIR)\Os_Hal_MemoryProtection_Lcfg.c \
                               $(GENDATA_DIR)\Os_Hal_Timer_Lcfg.c

ASM_GENERATED_SOURCE_FILES += $(GENDATA_DIR)\Os_Hal_EntryAsm_Lcfg.asm

# Library Settings
# Library not supported
