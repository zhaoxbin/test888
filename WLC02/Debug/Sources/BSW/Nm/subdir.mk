################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Nm/Nm.c" \

C_SRCS += \
../Sources/BSW/Nm/Nm.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Nm/Nm.d" \

OBJS_QUOTED += \
"./Sources/BSW/Nm/Nm.o" \

C_DEPS += \
./Sources/BSW/Nm/Nm.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Nm/Nm.o \

OBJS += \
./Sources/BSW/Nm/Nm.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Nm/Nm.o: ../Sources/BSW/Nm/Nm.c
	@echo 'Building file: $<'
	@echo 'Executing target #87 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Nm/Nm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Nm/Nm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


