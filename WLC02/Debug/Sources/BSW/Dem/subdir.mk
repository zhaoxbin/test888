################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Dem/Dem.c" \

C_SRCS += \
../Sources/BSW/Dem/Dem.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Dem/Dem.d" \

OBJS_QUOTED += \
"./Sources/BSW/Dem/Dem.o" \

C_DEPS += \
./Sources/BSW/Dem/Dem.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Dem/Dem.o \

OBJS += \
./Sources/BSW/Dem/Dem.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Dem/Dem.o: ../Sources/BSW/Dem/Dem.c
	@echo 'Building file: $<'
	@echo 'Executing target #64 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Dem/Dem.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Dem/Dem.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


