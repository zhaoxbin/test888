################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/interrupt.c" \
"../Sources/main.c" \
"../Sources/nfc_task.c" \

C_SRCS += \
../Sources/interrupt.c \
../Sources/main.c \
../Sources/nfc_task.c \

C_DEPS_QUOTED += \
"./Sources/interrupt.d" \
"./Sources/main.d" \
"./Sources/nfc_task.d" \

OBJS_QUOTED += \
"./Sources/interrupt.o" \
"./Sources/main.o" \
"./Sources/nfc_task.o" \

C_DEPS += \
./Sources/interrupt.d \
./Sources/main.d \
./Sources/nfc_task.d \

OBJS_OS_FORMAT += \
./Sources/interrupt.o \
./Sources/main.o \
./Sources/nfc_task.o \

OBJS += \
./Sources/interrupt.o \
./Sources/main.o \
./Sources/nfc_task.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/interrupt.o: ../Sources/interrupt.c
	@echo 'Building file: $<'
	@echo 'Executing target #252 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/interrupt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/interrupt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #253 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/nfc_task.o: ../Sources/nfc_task.c
	@echo 'Building file: $<'
	@echo 'Executing target #254 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/nfc_task.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/nfc_task.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


