################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/VStdLib/vstdlib.c" \

C_SRCS += \
../Sources/BSW/VStdLib/vstdlib.c \

C_DEPS_QUOTED += \
"./Sources/BSW/VStdLib/vstdlib.d" \

OBJS_QUOTED += \
"./Sources/BSW/VStdLib/vstdlib.o" \

C_DEPS += \
./Sources/BSW/VStdLib/vstdlib.d \

OBJS_OS_FORMAT += \
./Sources/BSW/VStdLib/vstdlib.o \

OBJS += \
./Sources/BSW/VStdLib/vstdlib.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/VStdLib/vstdlib.o: ../Sources/BSW/VStdLib/vstdlib.c
	@echo 'Building file: $<'
	@echo 'Executing target #148 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/VStdLib/vstdlib.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/VStdLib/vstdlib.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


