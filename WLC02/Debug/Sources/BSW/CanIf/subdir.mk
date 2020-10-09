################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/CanIf/CanIf.c" \

C_SRCS += \
../Sources/BSW/CanIf/CanIf.c \

C_DEPS_QUOTED += \
"./Sources/BSW/CanIf/CanIf.d" \

OBJS_QUOTED += \
"./Sources/BSW/CanIf/CanIf.o" \

C_DEPS += \
./Sources/BSW/CanIf/CanIf.d \

OBJS_OS_FORMAT += \
./Sources/BSW/CanIf/CanIf.o \

OBJS += \
./Sources/BSW/CanIf/CanIf.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/CanIf/CanIf.o: ../Sources/BSW/CanIf/CanIf.c
	@echo 'Building file: $<'
	@echo 'Executing target #54 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CanIf/CanIf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CanIf/CanIf.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


