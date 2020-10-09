################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 254
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Generated_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include SDK/platform/devices/S32K144/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/platform/drivers/src/adc/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/clock/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/flash/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/ftm/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/lpi2c/subdir.mk
-include SDK/platform/drivers/src/lpit/subdir.mk
-include SDK/platform/drivers/src/lpuart/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/power/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/power/subdir.mk
-include SDK/platform/drivers/src/wdog/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include Sources/BSW/BswM/subdir.mk
-include Sources/BSW/CDDNIO/subdir.mk
-include Sources/BSW/Can/subdir.mk
-include Sources/BSW/CanIf/subdir.mk
-include Sources/BSW/CanNm/subdir.mk
-include Sources/BSW/CanSM/subdir.mk
-include Sources/BSW/CanTp/subdir.mk
-include Sources/BSW/CanTrcv_30_Tja1040/subdir.mk
-include Sources/BSW/Com/subdir.mk
-include Sources/BSW/ComM/subdir.mk
-include Sources/BSW/Crc/subdir.mk
-include Sources/BSW/Dcm/subdir.mk
-include Sources/BSW/Dem/subdir.mk
-include Sources/BSW/Det/subdir.mk
-include Sources/BSW/EcuM/subdir.mk
-include Sources/BSW/Fee_30_SmallSector/subdir.mk
-include Sources/BSW/Fls/subdir.mk
-include Sources/BSW/MemIf/subdir.mk
-include Sources/BSW/Nm/subdir.mk
-include Sources/BSW/NvM/subdir.mk
-include Sources/BSW/Os/subdir.mk
-include Sources/BSW/PduR/subdir.mk
-include Sources/BSW/VStdLib/subdir.mk
-include Sources/NfcLibrary/NdefLibrary/src/subdir.mk
-include Sources/NfcLibrary/NxpNci/src/subdir.mk
-include Sources/NfcNio/subdir.mk
-include Sources/app/AutosarApp/GenData/subdir.mk
-include Sources/app/AutosarApp/Source/subdir.mk
-include Sources/app/Key/subdir.mk
-include Sources/app/subdir.mk
-include Sources/hal/subdir.mk
-include Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
WLC02.elf \

EXECUTABLES_QUOTED += \
"WLC02.elf" \

EXECUTABLES_OS_FORMAT += \
WLC02.elf \

SECONDARY_FLASH += \
WLC02.srec \

SECONDARY_FLASH_QUOTED += \
"WLC02.srec" \

SECONDARY_FLASH_OS_FORMAT += \
WLC02.srec \

SECONDARY_SIZE += \
WLC02.siz \

SECONDARY_SIZE_QUOTED += \
"WLC02.siz" \

SECONDARY_SIZE_OS_FORMAT += \
WLC02.siz \


# All Target
all: warning-messages explicit-dependencies WLC02.elf secondary-outputs

# Tool invocations
WLC02.elf: $(OBJS) E:/JXL/NIO_WLC_V02_1008/WLC02/Project_Settings/Linker_Files/S32K144_64_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #255 $@'
	@echo 'Invoking: Standard S32DS C++ Linker'
	arm-none-eabi-g++ -o "WLC02.elf" "@WLC02.args"  $(USER_OBJS_QUOTED) 
	@echo 'Finished building target: $@'
	@echo ' '

WLC02.srec: $(EXECUTABLES)
	@echo 'Executing target #256 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O srec $(EXECUTABLES)  "WLC02.srec"
	@echo 'Finished building: $@'
	@echo ' '

WLC02.siz: $(EXECUTABLES)
	@echo 'Executing target #257 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH_QUOTED) $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(SECONDARY_SIZE_QUOTED) $(C++_DEPS_QUOTED) ./*/*.d ./*/*/*.d ./*/*/*/*.d ./*/*/*/*/*.d ./*/*/*/*/*/*.d ./*/*/*/*/*/*/*.d  ./*/*.o ./*/*/*.o ./*/*/*/*.o ./*/*/*/*/*.o ./*/*/*/*/*/*.o ./*/*/*/*/*/*/*.o  $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

