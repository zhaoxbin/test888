################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/NvM/NvM.c" \
"../Sources/BSW/NvM/NvM_Act.c" \
"../Sources/BSW/NvM/NvM_Crc.c" \
"../Sources/BSW/NvM/NvM_JobProc.c" \
"../Sources/BSW/NvM/NvM_Qry.c" \
"../Sources/BSW/NvM/NvM_Queue.c" \

C_SRCS += \
../Sources/BSW/NvM/NvM.c \
../Sources/BSW/NvM/NvM_Act.c \
../Sources/BSW/NvM/NvM_Crc.c \
../Sources/BSW/NvM/NvM_JobProc.c \
../Sources/BSW/NvM/NvM_Qry.c \
../Sources/BSW/NvM/NvM_Queue.c \

C_DEPS_QUOTED += \
"./Sources/BSW/NvM/NvM.d" \
"./Sources/BSW/NvM/NvM_Act.d" \
"./Sources/BSW/NvM/NvM_Crc.d" \
"./Sources/BSW/NvM/NvM_JobProc.d" \
"./Sources/BSW/NvM/NvM_Qry.d" \
"./Sources/BSW/NvM/NvM_Queue.d" \

OBJS_QUOTED += \
"./Sources/BSW/NvM/NvM.o" \
"./Sources/BSW/NvM/NvM_Act.o" \
"./Sources/BSW/NvM/NvM_Crc.o" \
"./Sources/BSW/NvM/NvM_JobProc.o" \
"./Sources/BSW/NvM/NvM_Qry.o" \
"./Sources/BSW/NvM/NvM_Queue.o" \

C_DEPS += \
./Sources/BSW/NvM/NvM.d \
./Sources/BSW/NvM/NvM_Act.d \
./Sources/BSW/NvM/NvM_Crc.d \
./Sources/BSW/NvM/NvM_JobProc.d \
./Sources/BSW/NvM/NvM_Qry.d \
./Sources/BSW/NvM/NvM_Queue.d \

OBJS_OS_FORMAT += \
./Sources/BSW/NvM/NvM.o \
./Sources/BSW/NvM/NvM_Act.o \
./Sources/BSW/NvM/NvM_Crc.o \
./Sources/BSW/NvM/NvM_JobProc.o \
./Sources/BSW/NvM/NvM_Qry.o \
./Sources/BSW/NvM/NvM_Queue.o \

OBJS += \
./Sources/BSW/NvM/NvM.o \
./Sources/BSW/NvM/NvM_Act.o \
./Sources/BSW/NvM/NvM_Crc.o \
./Sources/BSW/NvM/NvM_JobProc.o \
./Sources/BSW/NvM/NvM_Qry.o \
./Sources/BSW/NvM/NvM_Queue.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/NvM/NvM.o: ../Sources/BSW/NvM/NvM.c
	@echo 'Building file: $<'
	@echo 'Executing target #88 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/NvM/NvM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/NvM/NvM.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/NvM/NvM_Act.o: ../Sources/BSW/NvM/NvM_Act.c
	@echo 'Building file: $<'
	@echo 'Executing target #89 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/NvM/NvM_Act.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/NvM/NvM_Act.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/NvM/NvM_Crc.o: ../Sources/BSW/NvM/NvM_Crc.c
	@echo 'Building file: $<'
	@echo 'Executing target #90 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/NvM/NvM_Crc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/NvM/NvM_Crc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/NvM/NvM_JobProc.o: ../Sources/BSW/NvM/NvM_JobProc.c
	@echo 'Building file: $<'
	@echo 'Executing target #91 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/NvM/NvM_JobProc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/NvM/NvM_JobProc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/NvM/NvM_Qry.o: ../Sources/BSW/NvM/NvM_Qry.c
	@echo 'Building file: $<'
	@echo 'Executing target #92 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/NvM/NvM_Qry.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/NvM/NvM_Qry.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/NvM/NvM_Queue.o: ../Sources/BSW/NvM/NvM_Queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #93 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/NvM/NvM_Queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/NvM/NvM_Queue.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


