################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/MemIf/MemIf.c" \

C_SRCS += \
../Sources/BSW/MemIf/MemIf.c \

C_DEPS_QUOTED += \
"./Sources/BSW/MemIf/MemIf.d" \

OBJS_QUOTED += \
"./Sources/BSW/MemIf/MemIf.o" \

C_DEPS += \
./Sources/BSW/MemIf/MemIf.d \

OBJS_OS_FORMAT += \
./Sources/BSW/MemIf/MemIf.o \

OBJS += \
./Sources/BSW/MemIf/MemIf.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/MemIf/MemIf.o: ../Sources/BSW/MemIf/MemIf.c
	@echo 'Building file: $<'
	@echo 'Executing target #86 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/MemIf/MemIf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/MemIf/MemIf.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


