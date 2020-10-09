################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Det/Det.c" \

C_SRCS += \
../Sources/BSW/Det/Det.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Det/Det.d" \

OBJS_QUOTED += \
"./Sources/BSW/Det/Det.o" \

C_DEPS += \
./Sources/BSW/Det/Det.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Det/Det.o \

OBJS += \
./Sources/BSW/Det/Det.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Det/Det.o: ../Sources/BSW/Det/Det.c
	@echo 'Building file: $<'
	@echo 'Executing target #65 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Det/Det.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Det/Det.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


