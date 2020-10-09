################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../SDK/platform/pal/i2c/src/i2c_pal.c" \

C_SRCS += \
../SDK/platform/pal/i2c/src/i2c_pal.c \

C_DEPS_QUOTED += \
"./SDK/platform/pal/i2c/src/i2c_pal.d" \

OBJS_QUOTED += \
"./SDK/platform/pal/i2c/src/i2c_pal.o" \

C_DEPS += \
./SDK/platform/pal/i2c/src/i2c_pal.d \

OBJS_OS_FORMAT += \
./SDK/platform/pal/i2c/src/i2c_pal.o \

OBJS += \
./SDK/platform/pal/i2c/src/i2c_pal.o \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/pal/i2c/src/i2c_pal.o: ../SDK/platform/pal/i2c/src/i2c_pal.c
	@echo 'Building file: $<'
	@echo 'Executing target #38 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/pal/i2c/src/i2c_pal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/pal/i2c/src/i2c_pal.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


