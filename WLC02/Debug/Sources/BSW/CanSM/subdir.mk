################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/CanSM/CanSM.c" \

C_SRCS += \
../Sources/BSW/CanSM/CanSM.c \

C_DEPS_QUOTED += \
"./Sources/BSW/CanSM/CanSM.d" \

OBJS_QUOTED += \
"./Sources/BSW/CanSM/CanSM.o" \

C_DEPS += \
./Sources/BSW/CanSM/CanSM.d \

OBJS_OS_FORMAT += \
./Sources/BSW/CanSM/CanSM.o \

OBJS += \
./Sources/BSW/CanSM/CanSM.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/CanSM/CanSM.o: ../Sources/BSW/CanSM/CanSM.c
	@echo 'Building file: $<'
	@echo 'Executing target #56 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CanSM/CanSM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CanSM/CanSM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


