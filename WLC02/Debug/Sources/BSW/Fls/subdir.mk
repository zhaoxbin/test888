################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Fls/Fls.c" \
"../Sources/BSW/Fls/Fls_Internal.c" \
"../Sources/BSW/Fls/Fls_Irq.c" \
"../Sources/BSW/Fls/Fls_Private_Fcu.c" \
"../Sources/BSW/Fls/Fls_Ram.c" \
"../Sources/BSW/Fls/Fls_Version.c" \

C_SRCS += \
../Sources/BSW/Fls/Fls.c \
../Sources/BSW/Fls/Fls_Internal.c \
../Sources/BSW/Fls/Fls_Irq.c \
../Sources/BSW/Fls/Fls_Private_Fcu.c \
../Sources/BSW/Fls/Fls_Ram.c \
../Sources/BSW/Fls/Fls_Version.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Fls/Fls.d" \
"./Sources/BSW/Fls/Fls_Internal.d" \
"./Sources/BSW/Fls/Fls_Irq.d" \
"./Sources/BSW/Fls/Fls_Private_Fcu.d" \
"./Sources/BSW/Fls/Fls_Ram.d" \
"./Sources/BSW/Fls/Fls_Version.d" \

OBJS_QUOTED += \
"./Sources/BSW/Fls/Fls.o" \
"./Sources/BSW/Fls/Fls_Internal.o" \
"./Sources/BSW/Fls/Fls_Irq.o" \
"./Sources/BSW/Fls/Fls_Private_Fcu.o" \
"./Sources/BSW/Fls/Fls_Ram.o" \
"./Sources/BSW/Fls/Fls_Version.o" \

C_DEPS += \
./Sources/BSW/Fls/Fls.d \
./Sources/BSW/Fls/Fls_Internal.d \
./Sources/BSW/Fls/Fls_Irq.d \
./Sources/BSW/Fls/Fls_Private_Fcu.d \
./Sources/BSW/Fls/Fls_Ram.d \
./Sources/BSW/Fls/Fls_Version.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Fls/Fls.o \
./Sources/BSW/Fls/Fls_Internal.o \
./Sources/BSW/Fls/Fls_Irq.o \
./Sources/BSW/Fls/Fls_Private_Fcu.o \
./Sources/BSW/Fls/Fls_Ram.o \
./Sources/BSW/Fls/Fls_Version.o \

OBJS += \
./Sources/BSW/Fls/Fls.o \
./Sources/BSW/Fls/Fls_Internal.o \
./Sources/BSW/Fls/Fls_Irq.o \
./Sources/BSW/Fls/Fls_Private_Fcu.o \
./Sources/BSW/Fls/Fls_Ram.o \
./Sources/BSW/Fls/Fls_Version.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Fls/Fls.o: ../Sources/BSW/Fls/Fls.c
	@echo 'Building file: $<'
	@echo 'Executing target #80 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Fls/Fls.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Fls/Fls.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Fls/Fls_Internal.o: ../Sources/BSW/Fls/Fls_Internal.c
	@echo 'Building file: $<'
	@echo 'Executing target #81 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Fls/Fls_Internal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Fls/Fls_Internal.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Fls/Fls_Irq.o: ../Sources/BSW/Fls/Fls_Irq.c
	@echo 'Building file: $<'
	@echo 'Executing target #82 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Fls/Fls_Irq.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Fls/Fls_Irq.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Fls/Fls_Private_Fcu.o: ../Sources/BSW/Fls/Fls_Private_Fcu.c
	@echo 'Building file: $<'
	@echo 'Executing target #83 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Fls/Fls_Private_Fcu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Fls/Fls_Private_Fcu.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Fls/Fls_Ram.o: ../Sources/BSW/Fls/Fls_Ram.c
	@echo 'Building file: $<'
	@echo 'Executing target #84 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Fls/Fls_Ram.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Fls/Fls_Ram.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Fls/Fls_Version.o: ../Sources/BSW/Fls/Fls_Version.c
	@echo 'Building file: $<'
	@echo 'Executing target #85 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Fls/Fls_Version.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Fls/Fls_Version.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


