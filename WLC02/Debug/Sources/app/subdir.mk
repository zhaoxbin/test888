################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/systemStatusCharge.c" \
"../Sources/app/systemStatusFault.c" \
"../Sources/app/systemStatusNfc.c" \
"../Sources/app/systemStatusOff.c" \
"../Sources/app/systemStatusPause.c" \
"../Sources/app/systemStatusStandby.c" \
"../Sources/app/systemTask.c" \
"../Sources/app/systemTimers.c" \

C_SRCS += \
../Sources/app/systemStatusCharge.c \
../Sources/app/systemStatusFault.c \
../Sources/app/systemStatusNfc.c \
../Sources/app/systemStatusOff.c \
../Sources/app/systemStatusPause.c \
../Sources/app/systemStatusStandby.c \
../Sources/app/systemTask.c \
../Sources/app/systemTimers.c \

C_DEPS_QUOTED += \
"./Sources/app/systemStatusCharge.d" \
"./Sources/app/systemStatusFault.d" \
"./Sources/app/systemStatusNfc.d" \
"./Sources/app/systemStatusOff.d" \
"./Sources/app/systemStatusPause.d" \
"./Sources/app/systemStatusStandby.d" \
"./Sources/app/systemTask.d" \
"./Sources/app/systemTimers.d" \

OBJS_QUOTED += \
"./Sources/app/systemStatusCharge.o" \
"./Sources/app/systemStatusFault.o" \
"./Sources/app/systemStatusNfc.o" \
"./Sources/app/systemStatusOff.o" \
"./Sources/app/systemStatusPause.o" \
"./Sources/app/systemStatusStandby.o" \
"./Sources/app/systemTask.o" \
"./Sources/app/systemTimers.o" \

C_DEPS += \
./Sources/app/systemStatusCharge.d \
./Sources/app/systemStatusFault.d \
./Sources/app/systemStatusNfc.d \
./Sources/app/systemStatusOff.d \
./Sources/app/systemStatusPause.d \
./Sources/app/systemStatusStandby.d \
./Sources/app/systemTask.d \
./Sources/app/systemTimers.d \

OBJS_OS_FORMAT += \
./Sources/app/systemStatusCharge.o \
./Sources/app/systemStatusFault.o \
./Sources/app/systemStatusNfc.o \
./Sources/app/systemStatusOff.o \
./Sources/app/systemStatusPause.o \
./Sources/app/systemStatusStandby.o \
./Sources/app/systemTask.o \
./Sources/app/systemTimers.o \

OBJS += \
./Sources/app/systemStatusCharge.o \
./Sources/app/systemStatusFault.o \
./Sources/app/systemStatusNfc.o \
./Sources/app/systemStatusOff.o \
./Sources/app/systemStatusPause.o \
./Sources/app/systemStatusStandby.o \
./Sources/app/systemTask.o \
./Sources/app/systemTimers.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/systemStatusCharge.o: ../Sources/app/systemStatusCharge.c
	@echo 'Building file: $<'
	@echo 'Executing target #234 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemStatusCharge.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemStatusCharge.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemStatusFault.o: ../Sources/app/systemStatusFault.c
	@echo 'Building file: $<'
	@echo 'Executing target #235 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemStatusFault.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemStatusFault.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemStatusNfc.o: ../Sources/app/systemStatusNfc.c
	@echo 'Building file: $<'
	@echo 'Executing target #236 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemStatusNfc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemStatusNfc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemStatusOff.o: ../Sources/app/systemStatusOff.c
	@echo 'Building file: $<'
	@echo 'Executing target #237 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemStatusOff.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemStatusOff.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemStatusPause.o: ../Sources/app/systemStatusPause.c
	@echo 'Building file: $<'
	@echo 'Executing target #238 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemStatusPause.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemStatusPause.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemStatusStandby.o: ../Sources/app/systemStatusStandby.c
	@echo 'Building file: $<'
	@echo 'Executing target #239 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemStatusStandby.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemStatusStandby.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemTask.o: ../Sources/app/systemTask.c
	@echo 'Building file: $<'
	@echo 'Executing target #240 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemTask.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemTask.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/systemTimers.o: ../Sources/app/systemTimers.c
	@echo 'Building file: $<'
	@echo 'Executing target #241 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/systemTimers.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/systemTimers.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


