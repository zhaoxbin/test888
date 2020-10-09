################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/hal/CommDec.c" \
"../Sources/hal/EEEPROM_data_def.c" \
"../Sources/hal/EEEProm_io_ctl.c" \
"../Sources/hal/ObjectDetection.c" \
"../Sources/hal/Packet.c" \
"../Sources/hal/hal.c" \
"../Sources/hal/measure.c" \
"../Sources/hal/pid.c" \
"../Sources/hal/safety.c" \
"../Sources/hal/uart.c" \

C_SRCS += \
../Sources/hal/CommDec.c \
../Sources/hal/EEEPROM_data_def.c \
../Sources/hal/EEEProm_io_ctl.c \
../Sources/hal/ObjectDetection.c \
../Sources/hal/Packet.c \
../Sources/hal/hal.c \
../Sources/hal/measure.c \
../Sources/hal/pid.c \
../Sources/hal/safety.c \
../Sources/hal/uart.c \

C_DEPS_QUOTED += \
"./Sources/hal/CommDec.d" \
"./Sources/hal/EEEPROM_data_def.d" \
"./Sources/hal/EEEProm_io_ctl.d" \
"./Sources/hal/ObjectDetection.d" \
"./Sources/hal/Packet.d" \
"./Sources/hal/hal.d" \
"./Sources/hal/measure.d" \
"./Sources/hal/pid.d" \
"./Sources/hal/safety.d" \
"./Sources/hal/uart.d" \

OBJS_QUOTED += \
"./Sources/hal/CommDec.o" \
"./Sources/hal/EEEPROM_data_def.o" \
"./Sources/hal/EEEProm_io_ctl.o" \
"./Sources/hal/ObjectDetection.o" \
"./Sources/hal/Packet.o" \
"./Sources/hal/hal.o" \
"./Sources/hal/measure.o" \
"./Sources/hal/pid.o" \
"./Sources/hal/safety.o" \
"./Sources/hal/uart.o" \

C_DEPS += \
./Sources/hal/CommDec.d \
./Sources/hal/EEEPROM_data_def.d \
./Sources/hal/EEEProm_io_ctl.d \
./Sources/hal/ObjectDetection.d \
./Sources/hal/Packet.d \
./Sources/hal/hal.d \
./Sources/hal/measure.d \
./Sources/hal/pid.d \
./Sources/hal/safety.d \
./Sources/hal/uart.d \

OBJS_OS_FORMAT += \
./Sources/hal/CommDec.o \
./Sources/hal/EEEPROM_data_def.o \
./Sources/hal/EEEProm_io_ctl.o \
./Sources/hal/ObjectDetection.o \
./Sources/hal/Packet.o \
./Sources/hal/hal.o \
./Sources/hal/measure.o \
./Sources/hal/pid.o \
./Sources/hal/safety.o \
./Sources/hal/uart.o \

OBJS += \
./Sources/hal/CommDec.o \
./Sources/hal/EEEPROM_data_def.o \
./Sources/hal/EEEProm_io_ctl.o \
./Sources/hal/ObjectDetection.o \
./Sources/hal/Packet.o \
./Sources/hal/hal.o \
./Sources/hal/measure.o \
./Sources/hal/pid.o \
./Sources/hal/safety.o \
./Sources/hal/uart.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/hal/CommDec.o: ../Sources/hal/CommDec.c
	@echo 'Building file: $<'
	@echo 'Executing target #242 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/CommDec.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/CommDec.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/EEEPROM_data_def.o: ../Sources/hal/EEEPROM_data_def.c
	@echo 'Building file: $<'
	@echo 'Executing target #243 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/EEEPROM_data_def.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/EEEPROM_data_def.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/EEEProm_io_ctl.o: ../Sources/hal/EEEProm_io_ctl.c
	@echo 'Building file: $<'
	@echo 'Executing target #244 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/EEEProm_io_ctl.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/EEEProm_io_ctl.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/ObjectDetection.o: ../Sources/hal/ObjectDetection.c
	@echo 'Building file: $<'
	@echo 'Executing target #245 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/ObjectDetection.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/ObjectDetection.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/Packet.o: ../Sources/hal/Packet.c
	@echo 'Building file: $<'
	@echo 'Executing target #246 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/Packet.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/Packet.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/hal.o: ../Sources/hal/hal.c
	@echo 'Building file: $<'
	@echo 'Executing target #247 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/hal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/hal.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/measure.o: ../Sources/hal/measure.c
	@echo 'Building file: $<'
	@echo 'Executing target #248 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/measure.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/measure.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/pid.o: ../Sources/hal/pid.c
	@echo 'Building file: $<'
	@echo 'Executing target #249 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/pid.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/pid.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/safety.o: ../Sources/hal/safety.c
	@echo 'Building file: $<'
	@echo 'Executing target #250 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/safety.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/safety.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal/uart.o: ../Sources/hal/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #251 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/hal/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/hal/uart.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


