################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Dcm/Dcm.c" \
"../Sources/BSW/Dcm/Dcm_Ext.c" \

C_SRCS += \
../Sources/BSW/Dcm/Dcm.c \
../Sources/BSW/Dcm/Dcm_Ext.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Dcm/Dcm.d" \
"./Sources/BSW/Dcm/Dcm_Ext.d" \

OBJS_QUOTED += \
"./Sources/BSW/Dcm/Dcm.o" \
"./Sources/BSW/Dcm/Dcm_Ext.o" \

C_DEPS += \
./Sources/BSW/Dcm/Dcm.d \
./Sources/BSW/Dcm/Dcm_Ext.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Dcm/Dcm.o \
./Sources/BSW/Dcm/Dcm_Ext.o \

OBJS += \
./Sources/BSW/Dcm/Dcm.o \
./Sources/BSW/Dcm/Dcm_Ext.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Dcm/Dcm.o: ../Sources/BSW/Dcm/Dcm.c
	@echo 'Building file: $<'
	@echo 'Executing target #62 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Dcm/Dcm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Dcm/Dcm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Dcm/Dcm_Ext.o: ../Sources/BSW/Dcm/Dcm_Ext.c
	@echo 'Building file: $<'
	@echo 'Executing target #63 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Dcm/Dcm_Ext.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Dcm/Dcm_Ext.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


