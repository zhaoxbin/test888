################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/AutosarApp/Source/APP_Callout_Stubs.c" \
"../Sources/app/AutosarApp/Source/BswM_Callout_Stubs.c" \
"../Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.c" \
"../Sources/app/AutosarApp/Source/Communication_Read_APP.c" \
"../Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.c" \
"../Sources/app/AutosarApp/Source/Os_Callout_Stubs.c" \
"../Sources/app/AutosarApp/Source/SWC_APP.c" \
"../Sources/app/AutosarApp/Source/SWC_WLCAPP.c" \

C_SRCS += \
../Sources/app/AutosarApp/Source/APP_Callout_Stubs.c \
../Sources/app/AutosarApp/Source/BswM_Callout_Stubs.c \
../Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.c \
../Sources/app/AutosarApp/Source/Communication_Read_APP.c \
../Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.c \
../Sources/app/AutosarApp/Source/Os_Callout_Stubs.c \
../Sources/app/AutosarApp/Source/SWC_APP.c \
../Sources/app/AutosarApp/Source/SWC_WLCAPP.c \

C_DEPS_QUOTED += \
"./Sources/app/AutosarApp/Source/APP_Callout_Stubs.d" \
"./Sources/app/AutosarApp/Source/BswM_Callout_Stubs.d" \
"./Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.d" \
"./Sources/app/AutosarApp/Source/Communication_Read_APP.d" \
"./Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.d" \
"./Sources/app/AutosarApp/Source/Os_Callout_Stubs.d" \
"./Sources/app/AutosarApp/Source/SWC_APP.d" \
"./Sources/app/AutosarApp/Source/SWC_WLCAPP.d" \

OBJS_QUOTED += \
"./Sources/app/AutosarApp/Source/APP_Callout_Stubs.o" \
"./Sources/app/AutosarApp/Source/BswM_Callout_Stubs.o" \
"./Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.o" \
"./Sources/app/AutosarApp/Source/Communication_Read_APP.o" \
"./Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.o" \
"./Sources/app/AutosarApp/Source/Os_Callout_Stubs.o" \
"./Sources/app/AutosarApp/Source/SWC_APP.o" \
"./Sources/app/AutosarApp/Source/SWC_WLCAPP.o" \

C_DEPS += \
./Sources/app/AutosarApp/Source/APP_Callout_Stubs.d \
./Sources/app/AutosarApp/Source/BswM_Callout_Stubs.d \
./Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.d \
./Sources/app/AutosarApp/Source/Communication_Read_APP.d \
./Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.d \
./Sources/app/AutosarApp/Source/Os_Callout_Stubs.d \
./Sources/app/AutosarApp/Source/SWC_APP.d \
./Sources/app/AutosarApp/Source/SWC_WLCAPP.d \

OBJS_OS_FORMAT += \
./Sources/app/AutosarApp/Source/APP_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/BswM_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/Communication_Read_APP.o \
./Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/Os_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/SWC_APP.o \
./Sources/app/AutosarApp/Source/SWC_WLCAPP.o \

OBJS += \
./Sources/app/AutosarApp/Source/APP_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/BswM_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/Communication_Read_APP.o \
./Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/Os_Callout_Stubs.o \
./Sources/app/AutosarApp/Source/SWC_APP.o \
./Sources/app/AutosarApp/Source/SWC_WLCAPP.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/AutosarApp/Source/APP_Callout_Stubs.o: ../Sources/app/AutosarApp/Source/APP_Callout_Stubs.c
	@echo 'Building file: $<'
	@echo 'Executing target #219 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/APP_Callout_Stubs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/APP_Callout_Stubs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/BswM_Callout_Stubs.o: ../Sources/app/AutosarApp/Source/BswM_Callout_Stubs.c
	@echo 'Building file: $<'
	@echo 'Executing target #220 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/BswM_Callout_Stubs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/BswM_Callout_Stubs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.o: ../Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.c
	@echo 'Building file: $<'
	@echo 'Executing target #221 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/CDDTP_Callout_Stubs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/Communication_Read_APP.o: ../Sources/app/AutosarApp/Source/Communication_Read_APP.c
	@echo 'Building file: $<'
	@echo 'Executing target #222 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/Communication_Read_APP.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/Communication_Read_APP.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.o: ../Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.c
	@echo 'Building file: $<'
	@echo 'Executing target #223 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/EcuM_Callout_Stubs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/Os_Callout_Stubs.o: ../Sources/app/AutosarApp/Source/Os_Callout_Stubs.c
	@echo 'Building file: $<'
	@echo 'Executing target #224 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/Os_Callout_Stubs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/Os_Callout_Stubs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/SWC_APP.o: ../Sources/app/AutosarApp/Source/SWC_APP.c
	@echo 'Building file: $<'
	@echo 'Executing target #225 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/SWC_APP.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/SWC_APP.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/AutosarApp/Source/SWC_WLCAPP.o: ../Sources/app/AutosarApp/Source/SWC_WLCAPP.c
	@echo 'Building file: $<'
	@echo 'Executing target #226 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/app/AutosarApp/Source/SWC_WLCAPP.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/app/AutosarApp/Source/SWC_WLCAPP.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


