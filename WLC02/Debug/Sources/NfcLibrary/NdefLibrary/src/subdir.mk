################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.c" \
"../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.c" \
"../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.c" \
"../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.c" \
"../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.c" \
"../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.c" \
"../Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.c" \
"../Sources/NfcLibrary/NdefLibrary/src/ndef_helper.c" \

C_SRCS += \
../Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.c \
../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.c \
../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.c \
../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.c \
../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.c \
../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.c \
../Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.c \
../Sources/NfcLibrary/NdefLibrary/src/ndef_helper.c \

C_DEPS_QUOTED += \
"./Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.d" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.d" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.d" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.d" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.d" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.d" \
"./Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.d" \
"./Sources/NfcLibrary/NdefLibrary/src/ndef_helper.d" \

OBJS_QUOTED += \
"./Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.o" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.o" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.o" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.o" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.o" \
"./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.o" \
"./Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.o" \
"./Sources/NfcLibrary/NdefLibrary/src/ndef_helper.o" \

C_DEPS += \
./Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.d \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.d \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.d \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.d \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.d \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.d \
./Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.d \
./Sources/NfcLibrary/NdefLibrary/src/ndef_helper.d \

OBJS_OS_FORMAT += \
./Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.o \
./Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.o \
./Sources/NfcLibrary/NdefLibrary/src/ndef_helper.o \

OBJS += \
./Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.o \
./Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.o \
./Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.o \
./Sources/NfcLibrary/NdefLibrary/src/ndef_helper.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.o: ../Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.c
	@echo 'Building file: $<'
	@echo 'Executing target #149 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/P2P_NDEF.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.o: ../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.c
	@echo 'Building file: $<'
	@echo 'Executing target #150 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/RW_NDEF.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.o: ../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.c
	@echo 'Building file: $<'
	@echo 'Executing target #151 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.o: ../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.c
	@echo 'Building file: $<'
	@echo 'Executing target #152 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.o: ../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.c
	@echo 'Building file: $<'
	@echo 'Executing target #153 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.o: ../Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.c
	@echo 'Building file: $<'
	@echo 'Executing target #154 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.o: ../Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.c
	@echo 'Building file: $<'
	@echo 'Executing target #155 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/NfcLibrary/NdefLibrary/src/ndef_helper.o: ../Sources/NfcLibrary/NdefLibrary/src/ndef_helper.c
	@echo 'Building file: $<'
	@echo 'Executing target #156 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/NfcLibrary/NdefLibrary/src/ndef_helper.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/NfcLibrary/NdefLibrary/src/ndef_helper.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


