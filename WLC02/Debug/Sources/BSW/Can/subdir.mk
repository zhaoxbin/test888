################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Can/Can.c" \
"../Sources/BSW/Can/Can_Irq.c" \

C_SRCS += \
../Sources/BSW/Can/Can.c \
../Sources/BSW/Can/Can_Irq.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Can/Can.d" \
"./Sources/BSW/Can/Can_Irq.d" \

OBJS_QUOTED += \
"./Sources/BSW/Can/Can.o" \
"./Sources/BSW/Can/Can_Irq.o" \

C_DEPS += \
./Sources/BSW/Can/Can.d \
./Sources/BSW/Can/Can_Irq.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Can/Can.o \
./Sources/BSW/Can/Can_Irq.o \

OBJS += \
./Sources/BSW/Can/Can.o \
./Sources/BSW/Can/Can_Irq.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Can/Can.o: ../Sources/BSW/Can/Can.c
	@echo 'Building file: $<'
	@echo 'Executing target #52 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Can/Can.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Can/Can.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Can/Can_Irq.o: ../Sources/BSW/Can/Can_Irq.c
	@echo 'Building file: $<'
	@echo 'Executing target #53 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Can/Can_Irq.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Can/Can_Irq.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


