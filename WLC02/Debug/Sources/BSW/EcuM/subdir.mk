################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/EcuM/EcuM.c" \

C_SRCS += \
../Sources/BSW/EcuM/EcuM.c \

C_DEPS_QUOTED += \
"./Sources/BSW/EcuM/EcuM.d" \

OBJS_QUOTED += \
"./Sources/BSW/EcuM/EcuM.o" \

C_DEPS += \
./Sources/BSW/EcuM/EcuM.d \

OBJS_OS_FORMAT += \
./Sources/BSW/EcuM/EcuM.o \

OBJS += \
./Sources/BSW/EcuM/EcuM.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/EcuM/EcuM.o: ../Sources/BSW/EcuM/EcuM.c
	@echo 'Building file: $<'
	@echo 'Executing target #66 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/EcuM/EcuM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/EcuM/EcuM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


