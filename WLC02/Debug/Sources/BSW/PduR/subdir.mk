################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/PduR/PduR.c" \
"../Sources/BSW/PduR/PduR_Bm.c" \
"../Sources/BSW/PduR/PduR_Fm.c" \
"../Sources/BSW/PduR/PduR_IFQ.c" \
"../Sources/BSW/PduR/PduR_Lock.c" \
"../Sources/BSW/PduR/PduR_McQ.c" \
"../Sources/BSW/PduR/PduR_RmIf.c" \
"../Sources/BSW/PduR/PduR_RmTp.c" \
"../Sources/BSW/PduR/PduR_RmTp_TxInst.c" \
"../Sources/BSW/PduR/PduR_Sm.c" \

C_SRCS += \
../Sources/BSW/PduR/PduR.c \
../Sources/BSW/PduR/PduR_Bm.c \
../Sources/BSW/PduR/PduR_Fm.c \
../Sources/BSW/PduR/PduR_IFQ.c \
../Sources/BSW/PduR/PduR_Lock.c \
../Sources/BSW/PduR/PduR_McQ.c \
../Sources/BSW/PduR/PduR_RmIf.c \
../Sources/BSW/PduR/PduR_RmTp.c \
../Sources/BSW/PduR/PduR_RmTp_TxInst.c \
../Sources/BSW/PduR/PduR_Sm.c \

C_DEPS_QUOTED += \
"./Sources/BSW/PduR/PduR.d" \
"./Sources/BSW/PduR/PduR_Bm.d" \
"./Sources/BSW/PduR/PduR_Fm.d" \
"./Sources/BSW/PduR/PduR_IFQ.d" \
"./Sources/BSW/PduR/PduR_Lock.d" \
"./Sources/BSW/PduR/PduR_McQ.d" \
"./Sources/BSW/PduR/PduR_RmIf.d" \
"./Sources/BSW/PduR/PduR_RmTp.d" \
"./Sources/BSW/PduR/PduR_RmTp_TxInst.d" \
"./Sources/BSW/PduR/PduR_Sm.d" \

OBJS_QUOTED += \
"./Sources/BSW/PduR/PduR.o" \
"./Sources/BSW/PduR/PduR_Bm.o" \
"./Sources/BSW/PduR/PduR_Fm.o" \
"./Sources/BSW/PduR/PduR_IFQ.o" \
"./Sources/BSW/PduR/PduR_Lock.o" \
"./Sources/BSW/PduR/PduR_McQ.o" \
"./Sources/BSW/PduR/PduR_RmIf.o" \
"./Sources/BSW/PduR/PduR_RmTp.o" \
"./Sources/BSW/PduR/PduR_RmTp_TxInst.o" \
"./Sources/BSW/PduR/PduR_Sm.o" \

C_DEPS += \
./Sources/BSW/PduR/PduR.d \
./Sources/BSW/PduR/PduR_Bm.d \
./Sources/BSW/PduR/PduR_Fm.d \
./Sources/BSW/PduR/PduR_IFQ.d \
./Sources/BSW/PduR/PduR_Lock.d \
./Sources/BSW/PduR/PduR_McQ.d \
./Sources/BSW/PduR/PduR_RmIf.d \
./Sources/BSW/PduR/PduR_RmTp.d \
./Sources/BSW/PduR/PduR_RmTp_TxInst.d \
./Sources/BSW/PduR/PduR_Sm.d \

OBJS_OS_FORMAT += \
./Sources/BSW/PduR/PduR.o \
./Sources/BSW/PduR/PduR_Bm.o \
./Sources/BSW/PduR/PduR_Fm.o \
./Sources/BSW/PduR/PduR_IFQ.o \
./Sources/BSW/PduR/PduR_Lock.o \
./Sources/BSW/PduR/PduR_McQ.o \
./Sources/BSW/PduR/PduR_RmIf.o \
./Sources/BSW/PduR/PduR_RmTp.o \
./Sources/BSW/PduR/PduR_RmTp_TxInst.o \
./Sources/BSW/PduR/PduR_Sm.o \

OBJS += \
./Sources/BSW/PduR/PduR.o \
./Sources/BSW/PduR/PduR_Bm.o \
./Sources/BSW/PduR/PduR_Fm.o \
./Sources/BSW/PduR/PduR_IFQ.o \
./Sources/BSW/PduR/PduR_Lock.o \
./Sources/BSW/PduR/PduR_McQ.o \
./Sources/BSW/PduR/PduR_RmIf.o \
./Sources/BSW/PduR/PduR_RmTp.o \
./Sources/BSW/PduR/PduR_RmTp_TxInst.o \
./Sources/BSW/PduR/PduR_Sm.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/PduR/PduR.o: ../Sources/BSW/PduR/PduR.c
	@echo 'Building file: $<'
	@echo 'Executing target #138 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_Bm.o: ../Sources/BSW/PduR/PduR_Bm.c
	@echo 'Building file: $<'
	@echo 'Executing target #139 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_Bm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_Bm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_Fm.o: ../Sources/BSW/PduR/PduR_Fm.c
	@echo 'Building file: $<'
	@echo 'Executing target #140 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_Fm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_Fm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_IFQ.o: ../Sources/BSW/PduR/PduR_IFQ.c
	@echo 'Building file: $<'
	@echo 'Executing target #141 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_IFQ.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_IFQ.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_Lock.o: ../Sources/BSW/PduR/PduR_Lock.c
	@echo 'Building file: $<'
	@echo 'Executing target #142 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_Lock.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_Lock.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_McQ.o: ../Sources/BSW/PduR/PduR_McQ.c
	@echo 'Building file: $<'
	@echo 'Executing target #143 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_McQ.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_McQ.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_RmIf.o: ../Sources/BSW/PduR/PduR_RmIf.c
	@echo 'Building file: $<'
	@echo 'Executing target #144 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_RmIf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_RmIf.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_RmTp.o: ../Sources/BSW/PduR/PduR_RmTp.c
	@echo 'Building file: $<'
	@echo 'Executing target #145 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_RmTp.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_RmTp.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_RmTp_TxInst.o: ../Sources/BSW/PduR/PduR_RmTp_TxInst.c
	@echo 'Building file: $<'
	@echo 'Executing target #146 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_RmTp_TxInst.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_RmTp_TxInst.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/PduR/PduR_Sm.o: ../Sources/BSW/PduR/PduR_Sm.c
	@echo 'Building file: $<'
	@echo 'Executing target #147 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/PduR/PduR_Sm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/PduR/PduR_Sm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


