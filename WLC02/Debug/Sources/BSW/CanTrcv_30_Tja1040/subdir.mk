################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.c" \

C_SRCS += \
../Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.c \

C_DEPS_QUOTED += \
"./Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.d" \

OBJS_QUOTED += \
"./Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.o" \

C_DEPS += \
./Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.d \

OBJS_OS_FORMAT += \
./Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.o \

OBJS += \
./Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.o: ../Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.c
	@echo 'Building file: $<'
	@echo 'Executing target #58 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/CanTrcv_30_Tja1040/CanTrcv_30_Tja1040.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


