################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/Key/KeysystemIdConfig.c" \
"../Sources/app/Key/KeysystemPing.c" \
"../Sources/app/Key/KeysystemPowerTrans.c" \
"../Sources/app/Key/KeysystemSafe.c" \
"../Sources/app/Key/KeysystemSelection.c" \
"../Sources/app/Key/KeysystemStatus.c" \
"../Sources/app/Key/KeysystemTerminate.c" \

C_SRCS += \
../Sources/app/Key/KeysystemIdConfig.c \
../Sources/app/Key/KeysystemPing.c \
../Sources/app/Key/KeysystemPowerTrans.c \
../Sources/app/Key/KeysystemSafe.c \
../Sources/app/Key/KeysystemSelection.c \
../Sources/app/Key/KeysystemStatus.c \
../Sources/app/Key/KeysystemTerminate.c \

C_DEPS_QUOTED += \
"./Sources/app/Key/KeysystemIdConfig.d" \
"./Sources/app/Key/KeysystemPing.d" \
"./Sources/app/Key/KeysystemPowerTrans.d" \
"./Sources/app/Key/KeysystemSafe.d" \
"./Sources/app/Key/KeysystemSelection.d" \
"./Sources/app/Key/KeysystemStatus.d" \
"./Sources/app/Key/KeysystemTerminate.d" \

OBJS_QUOTED += \
"./Sources/app/Key/KeysystemIdConfig.o" \
"./Sources/app/Key/KeysystemPing.o" \
"./Sources/app/Key/KeysystemPowerTrans.o" \
"./Sources/app/Key/KeysystemSafe.o" \
"./Sources/app/Key/KeysystemSelection.o" \
"./Sources/app/Key/KeysystemStatus.o" \
"./Sources/app/Key/KeysystemTerminate.o" \

C_DEPS += \
./Sources/app/Key/KeysystemIdConfig.d \
./Sources/app/Key/KeysystemPing.d \
./Sources/app/Key/KeysystemPowerTrans.d \
./Sources/app/Key/KeysystemSafe.d \
./Sources/app/Key/KeysystemSelection.d \
./Sources/app/Key/KeysystemStatus.d \
./Sources/app/Key/KeysystemTerminate.d \

OBJS_OS_FORMAT += \
./Sources/app/Key/KeysystemIdConfig.o \
./Sources/app/Key/KeysystemPing.o \
./Sources/app/Key/KeysystemPowerTrans.o \
./Sources/app/Key/KeysystemSafe.o \
./Sources/app/Key/KeysystemSelection.o \
./Sources/app/Key/KeysystemStatus.o \
./Sources/app/Key/KeysystemTerminate.o \

OBJS += \
./Sources/app/Key/KeysystemIdConfig.o \
./Sources/app/Key/KeysystemPing.o \
./Sources/app/Key/KeysystemPowerTrans.o \
./Sources/app/Key/KeysystemSafe.o \
./Sources/app/Key/KeysystemSelection.o \
./Sources/app/Key/KeysystemStatus.o \
./Sources/app/Key/KeysystemTerminate.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/Key/KeysystemIdConfig.o: ../Sources/app/Key/KeysystemIdConfig.c
	@echo 'Building file: $<'
	@echo 'Executing target #227 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemIdConfig.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemIdConfig.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Key/KeysystemPing.o: ../Sources/app/Key/KeysystemPing.c
	@echo 'Building file: $<'
	@echo 'Executing target #228 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemPing.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemPing.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Key/KeysystemPowerTrans.o: ../Sources/app/Key/KeysystemPowerTrans.c
	@echo 'Building file: $<'
	@echo 'Executing target #229 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemPowerTrans.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemPowerTrans.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Key/KeysystemSafe.o: ../Sources/app/Key/KeysystemSafe.c
	@echo 'Building file: $<'
	@echo 'Executing target #230 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemSafe.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemSafe.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Key/KeysystemSelection.o: ../Sources/app/Key/KeysystemSelection.c
	@echo 'Building file: $<'
	@echo 'Executing target #231 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemSelection.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemSelection.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Key/KeysystemStatus.o: ../Sources/app/Key/KeysystemStatus.c
	@echo 'Building file: $<'
	@echo 'Executing target #232 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemStatus.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemStatus.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/Key/KeysystemTerminate.o: ../Sources/app/Key/KeysystemTerminate.c
	@echo 'Building file: $<'
	@echo 'Executing target #233 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/Key/KeysystemTerminate.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/Key/KeysystemTerminate.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


