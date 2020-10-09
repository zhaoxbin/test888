################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/CanNm/CanNm.c" \

C_SRCS += \
../Sources/BSW/CanNm/CanNm.c \

C_DEPS_QUOTED += \
"./Sources/BSW/CanNm/CanNm.d" \

OBJS_QUOTED += \
"./Sources/BSW/CanNm/CanNm.o" \

C_DEPS += \
./Sources/BSW/CanNm/CanNm.d \

OBJS_OS_FORMAT += \
./Sources/BSW/CanNm/CanNm.o \

OBJS += \
./Sources/BSW/CanNm/CanNm.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/CanNm/CanNm.o: ../Sources/BSW/CanNm/CanNm.c
	@echo 'Building file: $<'
	@echo 'Executing target #55 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CanNm/CanNm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CanNm/CanNm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


