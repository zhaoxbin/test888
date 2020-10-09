################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../SDK/platform/drivers/src/clock/clock_manager.c" \

C_SRCS += \
../SDK/platform/drivers/src/clock/clock_manager.c \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/clock/clock_manager.d" \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/clock/clock_manager.o" \

C_DEPS += \
./SDK/platform/drivers/src/clock/clock_manager.d \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/clock/clock_manager.o \

OBJS += \
./SDK/platform/drivers/src/clock/clock_manager.o \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/clock/clock_manager.o: ../SDK/platform/drivers/src/clock/clock_manager.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/clock/clock_manager.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/clock/clock_manager.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


