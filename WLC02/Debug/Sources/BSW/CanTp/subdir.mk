################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/CanTp/CanTp.c" \

C_SRCS += \
../Sources/BSW/CanTp/CanTp.c \

C_DEPS_QUOTED += \
"./Sources/BSW/CanTp/CanTp.d" \

OBJS_QUOTED += \
"./Sources/BSW/CanTp/CanTp.o" \

C_DEPS += \
./Sources/BSW/CanTp/CanTp.d \

OBJS_OS_FORMAT += \
./Sources/BSW/CanTp/CanTp.o \

OBJS += \
./Sources/BSW/CanTp/CanTp.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/CanTp/CanTp.o: ../Sources/BSW/CanTp/CanTp.c
	@echo 'Building file: $<'
	@echo 'Executing target #57 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CanTp/CanTp.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CanTp/CanTp.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


