################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../SDK/platform/drivers/src/ftm/ftm_common.c" \
"../SDK/platform/drivers/src/ftm/ftm_hw_access.c" \
"../SDK/platform/drivers/src/ftm/ftm_mc_driver.c" \
"../SDK/platform/drivers/src/ftm/ftm_pwm_driver.c" \

C_SRCS += \
../SDK/platform/drivers/src/ftm/ftm_common.c \
../SDK/platform/drivers/src/ftm/ftm_hw_access.c \
../SDK/platform/drivers/src/ftm/ftm_mc_driver.c \
../SDK/platform/drivers/src/ftm/ftm_pwm_driver.c \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/ftm/ftm_common.d" \
"./SDK/platform/drivers/src/ftm/ftm_hw_access.d" \
"./SDK/platform/drivers/src/ftm/ftm_mc_driver.d" \
"./SDK/platform/drivers/src/ftm/ftm_pwm_driver.d" \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/ftm/ftm_common.o" \
"./SDK/platform/drivers/src/ftm/ftm_hw_access.o" \
"./SDK/platform/drivers/src/ftm/ftm_mc_driver.o" \
"./SDK/platform/drivers/src/ftm/ftm_pwm_driver.o" \

C_DEPS += \
./SDK/platform/drivers/src/ftm/ftm_common.d \
./SDK/platform/drivers/src/ftm/ftm_hw_access.d \
./SDK/platform/drivers/src/ftm/ftm_mc_driver.d \
./SDK/platform/drivers/src/ftm/ftm_pwm_driver.d \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/ftm/ftm_common.o \
./SDK/platform/drivers/src/ftm/ftm_hw_access.o \
./SDK/platform/drivers/src/ftm/ftm_mc_driver.o \
./SDK/platform/drivers/src/ftm/ftm_pwm_driver.o \

OBJS += \
./SDK/platform/drivers/src/ftm/ftm_common.o \
./SDK/platform/drivers/src/ftm/ftm_hw_access.o \
./SDK/platform/drivers/src/ftm/ftm_mc_driver.o \
./SDK/platform/drivers/src/ftm/ftm_pwm_driver.o \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/ftm/ftm_common.o: ../SDK/platform/drivers/src/ftm/ftm_common.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_common.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_common.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/ftm/ftm_hw_access.o: ../SDK/platform/drivers/src/ftm/ftm_hw_access.c
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_hw_access.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_hw_access.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/ftm/ftm_mc_driver.o: ../SDK/platform/drivers/src/ftm/ftm_mc_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_mc_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_mc_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/ftm/ftm_pwm_driver.o: ../SDK/platform/drivers/src/ftm/ftm_pwm_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_pwm_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_pwm_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


