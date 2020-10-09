################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/BswM/BswM.c" \

C_SRCS += \
../Sources/BSW/BswM/BswM.c \

C_DEPS_QUOTED += \
"./Sources/BSW/BswM/BswM.d" \

OBJS_QUOTED += \
"./Sources/BSW/BswM/BswM.o" \

C_DEPS += \
./Sources/BSW/BswM/BswM.d \

OBJS_OS_FORMAT += \
./Sources/BSW/BswM/BswM.o \

OBJS += \
./Sources/BSW/BswM/BswM.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/BswM/BswM.o: ../Sources/BSW/BswM/BswM.c
	@echo 'Building file: $<'
	@echo 'Executing target #49 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/BswM/BswM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/BswM/BswM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


