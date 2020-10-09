################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/ComM/ComM.c" \

C_SRCS += \
../Sources/BSW/ComM/ComM.c \

C_DEPS_QUOTED += \
"./Sources/BSW/ComM/ComM.d" \

OBJS_QUOTED += \
"./Sources/BSW/ComM/ComM.o" \

C_DEPS += \
./Sources/BSW/ComM/ComM.d \

OBJS_OS_FORMAT += \
./Sources/BSW/ComM/ComM.o \

OBJS += \
./Sources/BSW/ComM/ComM.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/ComM/ComM.o: ../Sources/BSW/ComM/ComM.c
	@echo 'Building file: $<'
	@echo 'Executing target #60 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/ComM/ComM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/ComM/ComM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


