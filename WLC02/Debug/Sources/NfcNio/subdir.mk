################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/NfcNio/ndef_bt_wifi.c" \
"../Sources/NfcNio/raw_p2p.c" \

C_SRCS += \
../Sources/NfcNio/ndef_bt_wifi.c \
../Sources/NfcNio/raw_p2p.c \

C_DEPS_QUOTED += \
"./Sources/NfcNio/ndef_bt_wifi.d" \
"./Sources/NfcNio/raw_p2p.d" \

OBJS_QUOTED += \
"./Sources/NfcNio/ndef_bt_wifi.o" \
"./Sources/NfcNio/raw_p2p.o" \

C_DEPS += \
./Sources/NfcNio/ndef_bt_wifi.d \
./Sources/NfcNio/raw_p2p.d \

OBJS_OS_FORMAT += \
./Sources/NfcNio/ndef_bt_wifi.o \
./Sources/NfcNio/raw_p2p.o \

OBJS += \
./Sources/NfcNio/ndef_bt_wifi.o \
./Sources/NfcNio/raw_p2p.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/NfcNio/ndef_bt_wifi.o: ../Sources/NfcNio/ndef_bt_wifi.c
	@echo 'Building file: $<'
	@echo 'Executing target #158 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcNio/ndef_bt_wifi.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcNio/ndef_bt_wifi.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcNio/raw_p2p.o: ../Sources/NfcNio/raw_p2p.c
	@echo 'Building file: $<'
	@echo 'Executing target #159 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcNio/raw_p2p.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcNio/raw_p2p.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


