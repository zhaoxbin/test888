################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/NfcLibrary/NxpNci/src/NxpNci.c" \

C_SRCS += \
../Sources/NfcLibrary/NxpNci/src/NxpNci.c \

C_DEPS_QUOTED += \
"./Sources/NfcLibrary/NxpNci/src/NxpNci.d" \

OBJS_QUOTED += \
"./Sources/NfcLibrary/NxpNci/src/NxpNci.o" \

C_DEPS += \
./Sources/NfcLibrary/NxpNci/src/NxpNci.d \

OBJS_OS_FORMAT += \
./Sources/NfcLibrary/NxpNci/src/NxpNci.o \

OBJS += \
./Sources/NfcLibrary/NxpNci/src/NxpNci.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/NfcLibrary/NxpNci/src/NxpNci.o: ../Sources/NfcLibrary/NxpNci/src/NxpNci.c
	@echo 'Building file: $<'
	@echo 'Executing target #157 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NxpNci/src/NxpNci.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NxpNci/src/NxpNci.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


