################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/CDDNIO/CDDNIO.c" \
"../Sources/BSW/CDDNIO/CDDNO_Lcfg.c" \

C_SRCS += \
../Sources/BSW/CDDNIO/CDDNIO.c \
../Sources/BSW/CDDNIO/CDDNO_Lcfg.c \

C_DEPS_QUOTED += \
"./Sources/BSW/CDDNIO/CDDNIO.d" \
"./Sources/BSW/CDDNIO/CDDNO_Lcfg.d" \

OBJS_QUOTED += \
"./Sources/BSW/CDDNIO/CDDNIO.o" \
"./Sources/BSW/CDDNIO/CDDNO_Lcfg.o" \

C_DEPS += \
./Sources/BSW/CDDNIO/CDDNIO.d \
./Sources/BSW/CDDNIO/CDDNO_Lcfg.d \

OBJS_OS_FORMAT += \
./Sources/BSW/CDDNIO/CDDNIO.o \
./Sources/BSW/CDDNIO/CDDNO_Lcfg.o \

OBJS += \
./Sources/BSW/CDDNIO/CDDNIO.o \
./Sources/BSW/CDDNIO/CDDNO_Lcfg.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/CDDNIO/CDDNIO.o: ../Sources/BSW/CDDNIO/CDDNIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #50 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CDDNIO/CDDNIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CDDNIO/CDDNIO.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/CDDNIO/CDDNO_Lcfg.o: ../Sources/BSW/CDDNIO/CDDNO_Lcfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #51 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CDDNIO/CDDNO_Lcfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CDDNIO/CDDNO_Lcfg.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


