################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/startup_S32K144.S" \

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup_S32K144.S \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/startup_S32K144.o" \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/startup_S32K144.o \

OBJS += \
./Project_Settings/Startup_Code/startup_S32K144.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/startup_S32K144.o: ../Project_Settings/Startup_Code/startup_S32K144.S
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@Project_Settings/Startup_Code/startup_S32K144.args" -o "Project_Settings/Startup_Code/startup_S32K144.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


