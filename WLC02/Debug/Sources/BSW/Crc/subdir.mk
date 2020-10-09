################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Crc/Crc.c" \

C_SRCS += \
../Sources/BSW/Crc/Crc.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Crc/Crc.d" \

OBJS_QUOTED += \
"./Sources/BSW/Crc/Crc.o" \

C_DEPS += \
./Sources/BSW/Crc/Crc.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Crc/Crc.o \

OBJS += \
./Sources/BSW/Crc/Crc.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Crc/Crc.o: ../Sources/BSW/Crc/Crc.c
	@echo 'Building file: $<'
	@echo 'Executing target #61 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Crc/Crc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Crc/Crc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


