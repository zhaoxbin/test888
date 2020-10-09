################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Com/Com.c" \

C_SRCS += \
../Sources/BSW/Com/Com.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Com/Com.d" \

OBJS_QUOTED += \
"./Sources/BSW/Com/Com.o" \

C_DEPS += \
./Sources/BSW/Com/Com.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Com/Com.o \

OBJS += \
./Sources/BSW/Com/Com.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Com/Com.o: ../Sources/BSW/Com/Com.c
	@echo 'Building file: $<'
	@echo 'Executing target #59 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Com/Com.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Com/Com.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


