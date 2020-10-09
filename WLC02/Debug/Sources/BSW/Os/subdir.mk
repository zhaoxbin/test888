################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BSW/Os/Os_AccessCheck.c" \
"../Sources/BSW/Os/Os_Alarm.c" \
"../Sources/BSW/Os/Os_Application.c" \
"../Sources/BSW/Os/Os_Barrier.c" \
"../Sources/BSW/Os/Os_Bit.c" \
"../Sources/BSW/Os/Os_BitArray.c" \
"../Sources/BSW/Os/Os_Core.c" \
"../Sources/BSW/Os/Os_Counter.c" \
"../Sources/BSW/Os/Os_Deque.c" \
"../Sources/BSW/Os/Os_Error.c" \
"../Sources/BSW/Os/Os_Event.c" \
"../Sources/BSW/Os/Os_Fifo.c" \
"../Sources/BSW/Os/Os_Fifo08.c" \
"../Sources/BSW/Os/Os_Fifo16.c" \
"../Sources/BSW/Os/Os_Fifo32.c" \
"../Sources/BSW/Os/Os_FifoRef.c" \
"../Sources/BSW/Os/Os_Hal_Context.c" \
"../Sources/BSW/Os/Os_Hal_Core.c" \
"../Sources/BSW/Os/Os_Hal_INTC.c" \
"../Sources/BSW/Os/Os_Hal_MemoryProtection.c" \
"../Sources/BSW/Os/Os_Hook.c" \
"../Sources/BSW/Os/Os_Interrupt.c" \
"../Sources/BSW/Os/Os_Ioc.c" \
"../Sources/BSW/Os/Os_Isr.c" \
"../Sources/BSW/Os/Os_Job.c" \
"../Sources/BSW/Os/Os_Lock.c" \
"../Sources/BSW/Os/Os_MemoryProtection.c" \
"../Sources/BSW/Os/Os_Peripheral.c" \
"../Sources/BSW/Os/Os_PriorityQueue.c" \
"../Sources/BSW/Os/Os_Resource.c" \
"../Sources/BSW/Os/Os_ScheduleTable.c" \
"../Sources/BSW/Os/Os_Scheduler.c" \
"../Sources/BSW/Os/Os_ServiceFunction.c" \
"../Sources/BSW/Os/Os_Spinlock.c" \
"../Sources/BSW/Os/Os_Stack.c" \
"../Sources/BSW/Os/Os_Task.c" \
"../Sources/BSW/Os/Os_Thread.c" \
"../Sources/BSW/Os/Os_Timer.c" \
"../Sources/BSW/Os/Os_TimingProtection.c" \
"../Sources/BSW/Os/Os_Trace.c" \
"../Sources/BSW/Os/Os_Trap.c" \
"../Sources/BSW/Os/Os_XSignal.c" \

ASM_SRCS += \
../Sources/BSW/Os/Os_Hal_Entry.asm \
../Sources/BSW/Os/Os_Hal_Trap.asm \

ASM_SRCS_QUOTED += \
"../Sources/BSW/Os/Os_Hal_Entry.asm" \
"../Sources/BSW/Os/Os_Hal_Trap.asm" \

C_SRCS += \
../Sources/BSW/Os/Os_AccessCheck.c \
../Sources/BSW/Os/Os_Alarm.c \
../Sources/BSW/Os/Os_Application.c \
../Sources/BSW/Os/Os_Barrier.c \
../Sources/BSW/Os/Os_Bit.c \
../Sources/BSW/Os/Os_BitArray.c \
../Sources/BSW/Os/Os_Core.c \
../Sources/BSW/Os/Os_Counter.c \
../Sources/BSW/Os/Os_Deque.c \
../Sources/BSW/Os/Os_Error.c \
../Sources/BSW/Os/Os_Event.c \
../Sources/BSW/Os/Os_Fifo.c \
../Sources/BSW/Os/Os_Fifo08.c \
../Sources/BSW/Os/Os_Fifo16.c \
../Sources/BSW/Os/Os_Fifo32.c \
../Sources/BSW/Os/Os_FifoRef.c \
../Sources/BSW/Os/Os_Hal_Context.c \
../Sources/BSW/Os/Os_Hal_Core.c \
../Sources/BSW/Os/Os_Hal_INTC.c \
../Sources/BSW/Os/Os_Hal_MemoryProtection.c \
../Sources/BSW/Os/Os_Hook.c \
../Sources/BSW/Os/Os_Interrupt.c \
../Sources/BSW/Os/Os_Ioc.c \
../Sources/BSW/Os/Os_Isr.c \
../Sources/BSW/Os/Os_Job.c \
../Sources/BSW/Os/Os_Lock.c \
../Sources/BSW/Os/Os_MemoryProtection.c \
../Sources/BSW/Os/Os_Peripheral.c \
../Sources/BSW/Os/Os_PriorityQueue.c \
../Sources/BSW/Os/Os_Resource.c \
../Sources/BSW/Os/Os_ScheduleTable.c \
../Sources/BSW/Os/Os_Scheduler.c \
../Sources/BSW/Os/Os_ServiceFunction.c \
../Sources/BSW/Os/Os_Spinlock.c \
../Sources/BSW/Os/Os_Stack.c \
../Sources/BSW/Os/Os_Task.c \
../Sources/BSW/Os/Os_Thread.c \
../Sources/BSW/Os/Os_Timer.c \
../Sources/BSW/Os/Os_TimingProtection.c \
../Sources/BSW/Os/Os_Trace.c \
../Sources/BSW/Os/Os_Trap.c \
../Sources/BSW/Os/Os_XSignal.c \

C_DEPS_QUOTED += \
"./Sources/BSW/Os/Os_AccessCheck.d" \
"./Sources/BSW/Os/Os_Alarm.d" \
"./Sources/BSW/Os/Os_Application.d" \
"./Sources/BSW/Os/Os_Barrier.d" \
"./Sources/BSW/Os/Os_Bit.d" \
"./Sources/BSW/Os/Os_BitArray.d" \
"./Sources/BSW/Os/Os_Core.d" \
"./Sources/BSW/Os/Os_Counter.d" \
"./Sources/BSW/Os/Os_Deque.d" \
"./Sources/BSW/Os/Os_Error.d" \
"./Sources/BSW/Os/Os_Event.d" \
"./Sources/BSW/Os/Os_Fifo.d" \
"./Sources/BSW/Os/Os_Fifo08.d" \
"./Sources/BSW/Os/Os_Fifo16.d" \
"./Sources/BSW/Os/Os_Fifo32.d" \
"./Sources/BSW/Os/Os_FifoRef.d" \
"./Sources/BSW/Os/Os_Hal_Context.d" \
"./Sources/BSW/Os/Os_Hal_Core.d" \
"./Sources/BSW/Os/Os_Hal_INTC.d" \
"./Sources/BSW/Os/Os_Hal_MemoryProtection.d" \
"./Sources/BSW/Os/Os_Hook.d" \
"./Sources/BSW/Os/Os_Interrupt.d" \
"./Sources/BSW/Os/Os_Ioc.d" \
"./Sources/BSW/Os/Os_Isr.d" \
"./Sources/BSW/Os/Os_Job.d" \
"./Sources/BSW/Os/Os_Lock.d" \
"./Sources/BSW/Os/Os_MemoryProtection.d" \
"./Sources/BSW/Os/Os_Peripheral.d" \
"./Sources/BSW/Os/Os_PriorityQueue.d" \
"./Sources/BSW/Os/Os_Resource.d" \
"./Sources/BSW/Os/Os_ScheduleTable.d" \
"./Sources/BSW/Os/Os_Scheduler.d" \
"./Sources/BSW/Os/Os_ServiceFunction.d" \
"./Sources/BSW/Os/Os_Spinlock.d" \
"./Sources/BSW/Os/Os_Stack.d" \
"./Sources/BSW/Os/Os_Task.d" \
"./Sources/BSW/Os/Os_Thread.d" \
"./Sources/BSW/Os/Os_Timer.d" \
"./Sources/BSW/Os/Os_TimingProtection.d" \
"./Sources/BSW/Os/Os_Trace.d" \
"./Sources/BSW/Os/Os_Trap.d" \
"./Sources/BSW/Os/Os_XSignal.d" \

OBJS_QUOTED += \
"./Sources/BSW/Os/Os_AccessCheck.o" \
"./Sources/BSW/Os/Os_Alarm.o" \
"./Sources/BSW/Os/Os_Application.o" \
"./Sources/BSW/Os/Os_Barrier.o" \
"./Sources/BSW/Os/Os_Bit.o" \
"./Sources/BSW/Os/Os_BitArray.o" \
"./Sources/BSW/Os/Os_Core.o" \
"./Sources/BSW/Os/Os_Counter.o" \
"./Sources/BSW/Os/Os_Deque.o" \
"./Sources/BSW/Os/Os_Error.o" \
"./Sources/BSW/Os/Os_Event.o" \
"./Sources/BSW/Os/Os_Fifo.o" \
"./Sources/BSW/Os/Os_Fifo08.o" \
"./Sources/BSW/Os/Os_Fifo16.o" \
"./Sources/BSW/Os/Os_Fifo32.o" \
"./Sources/BSW/Os/Os_FifoRef.o" \
"./Sources/BSW/Os/Os_Hal_Context.o" \
"./Sources/BSW/Os/Os_Hal_Core.o" \
"./Sources/BSW/Os/Os_Hal_Entry.o" \
"./Sources/BSW/Os/Os_Hal_INTC.o" \
"./Sources/BSW/Os/Os_Hal_MemoryProtection.o" \
"./Sources/BSW/Os/Os_Hal_Trap.o" \
"./Sources/BSW/Os/Os_Hook.o" \
"./Sources/BSW/Os/Os_Interrupt.o" \
"./Sources/BSW/Os/Os_Ioc.o" \
"./Sources/BSW/Os/Os_Isr.o" \
"./Sources/BSW/Os/Os_Job.o" \
"./Sources/BSW/Os/Os_Lock.o" \
"./Sources/BSW/Os/Os_MemoryProtection.o" \
"./Sources/BSW/Os/Os_Peripheral.o" \
"./Sources/BSW/Os/Os_PriorityQueue.o" \
"./Sources/BSW/Os/Os_Resource.o" \
"./Sources/BSW/Os/Os_ScheduleTable.o" \
"./Sources/BSW/Os/Os_Scheduler.o" \
"./Sources/BSW/Os/Os_ServiceFunction.o" \
"./Sources/BSW/Os/Os_Spinlock.o" \
"./Sources/BSW/Os/Os_Stack.o" \
"./Sources/BSW/Os/Os_Task.o" \
"./Sources/BSW/Os/Os_Thread.o" \
"./Sources/BSW/Os/Os_Timer.o" \
"./Sources/BSW/Os/Os_TimingProtection.o" \
"./Sources/BSW/Os/Os_Trace.o" \
"./Sources/BSW/Os/Os_Trap.o" \
"./Sources/BSW/Os/Os_XSignal.o" \

C_DEPS += \
./Sources/BSW/Os/Os_AccessCheck.d \
./Sources/BSW/Os/Os_Alarm.d \
./Sources/BSW/Os/Os_Application.d \
./Sources/BSW/Os/Os_Barrier.d \
./Sources/BSW/Os/Os_Bit.d \
./Sources/BSW/Os/Os_BitArray.d \
./Sources/BSW/Os/Os_Core.d \
./Sources/BSW/Os/Os_Counter.d \
./Sources/BSW/Os/Os_Deque.d \
./Sources/BSW/Os/Os_Error.d \
./Sources/BSW/Os/Os_Event.d \
./Sources/BSW/Os/Os_Fifo.d \
./Sources/BSW/Os/Os_Fifo08.d \
./Sources/BSW/Os/Os_Fifo16.d \
./Sources/BSW/Os/Os_Fifo32.d \
./Sources/BSW/Os/Os_FifoRef.d \
./Sources/BSW/Os/Os_Hal_Context.d \
./Sources/BSW/Os/Os_Hal_Core.d \
./Sources/BSW/Os/Os_Hal_INTC.d \
./Sources/BSW/Os/Os_Hal_MemoryProtection.d \
./Sources/BSW/Os/Os_Hook.d \
./Sources/BSW/Os/Os_Interrupt.d \
./Sources/BSW/Os/Os_Ioc.d \
./Sources/BSW/Os/Os_Isr.d \
./Sources/BSW/Os/Os_Job.d \
./Sources/BSW/Os/Os_Lock.d \
./Sources/BSW/Os/Os_MemoryProtection.d \
./Sources/BSW/Os/Os_Peripheral.d \
./Sources/BSW/Os/Os_PriorityQueue.d \
./Sources/BSW/Os/Os_Resource.d \
./Sources/BSW/Os/Os_ScheduleTable.d \
./Sources/BSW/Os/Os_Scheduler.d \
./Sources/BSW/Os/Os_ServiceFunction.d \
./Sources/BSW/Os/Os_Spinlock.d \
./Sources/BSW/Os/Os_Stack.d \
./Sources/BSW/Os/Os_Task.d \
./Sources/BSW/Os/Os_Thread.d \
./Sources/BSW/Os/Os_Timer.d \
./Sources/BSW/Os/Os_TimingProtection.d \
./Sources/BSW/Os/Os_Trace.d \
./Sources/BSW/Os/Os_Trap.d \
./Sources/BSW/Os/Os_XSignal.d \

OBJS_OS_FORMAT += \
./Sources/BSW/Os/Os_AccessCheck.o \
./Sources/BSW/Os/Os_Alarm.o \
./Sources/BSW/Os/Os_Application.o \
./Sources/BSW/Os/Os_Barrier.o \
./Sources/BSW/Os/Os_Bit.o \
./Sources/BSW/Os/Os_BitArray.o \
./Sources/BSW/Os/Os_Core.o \
./Sources/BSW/Os/Os_Counter.o \
./Sources/BSW/Os/Os_Deque.o \
./Sources/BSW/Os/Os_Error.o \
./Sources/BSW/Os/Os_Event.o \
./Sources/BSW/Os/Os_Fifo.o \
./Sources/BSW/Os/Os_Fifo08.o \
./Sources/BSW/Os/Os_Fifo16.o \
./Sources/BSW/Os/Os_Fifo32.o \
./Sources/BSW/Os/Os_FifoRef.o \
./Sources/BSW/Os/Os_Hal_Context.o \
./Sources/BSW/Os/Os_Hal_Core.o \
./Sources/BSW/Os/Os_Hal_Entry.o \
./Sources/BSW/Os/Os_Hal_INTC.o \
./Sources/BSW/Os/Os_Hal_MemoryProtection.o \
./Sources/BSW/Os/Os_Hal_Trap.o \
./Sources/BSW/Os/Os_Hook.o \
./Sources/BSW/Os/Os_Interrupt.o \
./Sources/BSW/Os/Os_Ioc.o \
./Sources/BSW/Os/Os_Isr.o \
./Sources/BSW/Os/Os_Job.o \
./Sources/BSW/Os/Os_Lock.o \
./Sources/BSW/Os/Os_MemoryProtection.o \
./Sources/BSW/Os/Os_Peripheral.o \
./Sources/BSW/Os/Os_PriorityQueue.o \
./Sources/BSW/Os/Os_Resource.o \
./Sources/BSW/Os/Os_ScheduleTable.o \
./Sources/BSW/Os/Os_Scheduler.o \
./Sources/BSW/Os/Os_ServiceFunction.o \
./Sources/BSW/Os/Os_Spinlock.o \
./Sources/BSW/Os/Os_Stack.o \
./Sources/BSW/Os/Os_Task.o \
./Sources/BSW/Os/Os_Thread.o \
./Sources/BSW/Os/Os_Timer.o \
./Sources/BSW/Os/Os_TimingProtection.o \
./Sources/BSW/Os/Os_Trace.o \
./Sources/BSW/Os/Os_Trap.o \
./Sources/BSW/Os/Os_XSignal.o \

OBJS += \
./Sources/BSW/Os/Os_AccessCheck.o \
./Sources/BSW/Os/Os_Alarm.o \
./Sources/BSW/Os/Os_Application.o \
./Sources/BSW/Os/Os_Barrier.o \
./Sources/BSW/Os/Os_Bit.o \
./Sources/BSW/Os/Os_BitArray.o \
./Sources/BSW/Os/Os_Core.o \
./Sources/BSW/Os/Os_Counter.o \
./Sources/BSW/Os/Os_Deque.o \
./Sources/BSW/Os/Os_Error.o \
./Sources/BSW/Os/Os_Event.o \
./Sources/BSW/Os/Os_Fifo.o \
./Sources/BSW/Os/Os_Fifo08.o \
./Sources/BSW/Os/Os_Fifo16.o \
./Sources/BSW/Os/Os_Fifo32.o \
./Sources/BSW/Os/Os_FifoRef.o \
./Sources/BSW/Os/Os_Hal_Context.o \
./Sources/BSW/Os/Os_Hal_Core.o \
./Sources/BSW/Os/Os_Hal_Entry.o \
./Sources/BSW/Os/Os_Hal_INTC.o \
./Sources/BSW/Os/Os_Hal_MemoryProtection.o \
./Sources/BSW/Os/Os_Hal_Trap.o \
./Sources/BSW/Os/Os_Hook.o \
./Sources/BSW/Os/Os_Interrupt.o \
./Sources/BSW/Os/Os_Ioc.o \
./Sources/BSW/Os/Os_Isr.o \
./Sources/BSW/Os/Os_Job.o \
./Sources/BSW/Os/Os_Lock.o \
./Sources/BSW/Os/Os_MemoryProtection.o \
./Sources/BSW/Os/Os_Peripheral.o \
./Sources/BSW/Os/Os_PriorityQueue.o \
./Sources/BSW/Os/Os_Resource.o \
./Sources/BSW/Os/Os_ScheduleTable.o \
./Sources/BSW/Os/Os_Scheduler.o \
./Sources/BSW/Os/Os_ServiceFunction.o \
./Sources/BSW/Os/Os_Spinlock.o \
./Sources/BSW/Os/Os_Stack.o \
./Sources/BSW/Os/Os_Task.o \
./Sources/BSW/Os/Os_Thread.o \
./Sources/BSW/Os/Os_Timer.o \
./Sources/BSW/Os/Os_TimingProtection.o \
./Sources/BSW/Os/Os_Trace.o \
./Sources/BSW/Os/Os_Trap.o \
./Sources/BSW/Os/Os_XSignal.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BSW/Os/Os_AccessCheck.o: ../Sources/BSW/Os/Os_AccessCheck.c
	@echo 'Building file: $<'
	@echo 'Executing target #94 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_AccessCheck.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_AccessCheck.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Alarm.o: ../Sources/BSW/Os/Os_Alarm.c
	@echo 'Building file: $<'
	@echo 'Executing target #95 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Alarm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Alarm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Application.o: ../Sources/BSW/Os/Os_Application.c
	@echo 'Building file: $<'
	@echo 'Executing target #96 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Application.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Application.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Barrier.o: ../Sources/BSW/Os/Os_Barrier.c
	@echo 'Building file: $<'
	@echo 'Executing target #97 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Barrier.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Barrier.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Bit.o: ../Sources/BSW/Os/Os_Bit.c
	@echo 'Building file: $<'
	@echo 'Executing target #98 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Bit.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Bit.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_BitArray.o: ../Sources/BSW/Os/Os_BitArray.c
	@echo 'Building file: $<'
	@echo 'Executing target #99 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_BitArray.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_BitArray.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Core.o: ../Sources/BSW/Os/Os_Core.c
	@echo 'Building file: $<'
	@echo 'Executing target #100 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Core.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Core.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Counter.o: ../Sources/BSW/Os/Os_Counter.c
	@echo 'Building file: $<'
	@echo 'Executing target #101 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Counter.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Counter.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Deque.o: ../Sources/BSW/Os/Os_Deque.c
	@echo 'Building file: $<'
	@echo 'Executing target #102 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Deque.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Deque.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Error.o: ../Sources/BSW/Os/Os_Error.c
	@echo 'Building file: $<'
	@echo 'Executing target #103 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Error.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Error.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Event.o: ../Sources/BSW/Os/Os_Event.c
	@echo 'Building file: $<'
	@echo 'Executing target #104 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Event.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Event.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Fifo.o: ../Sources/BSW/Os/Os_Fifo.c
	@echo 'Building file: $<'
	@echo 'Executing target #105 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Fifo.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Fifo.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Fifo08.o: ../Sources/BSW/Os/Os_Fifo08.c
	@echo 'Building file: $<'
	@echo 'Executing target #106 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Fifo08.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Fifo08.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Fifo16.o: ../Sources/BSW/Os/Os_Fifo16.c
	@echo 'Building file: $<'
	@echo 'Executing target #107 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Fifo16.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Fifo16.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Fifo32.o: ../Sources/BSW/Os/Os_Fifo32.c
	@echo 'Building file: $<'
	@echo 'Executing target #108 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Fifo32.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Fifo32.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_FifoRef.o: ../Sources/BSW/Os/Os_FifoRef.c
	@echo 'Building file: $<'
	@echo 'Executing target #109 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_FifoRef.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_FifoRef.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hal_Context.o: ../Sources/BSW/Os/Os_Hal_Context.c
	@echo 'Building file: $<'
	@echo 'Executing target #110 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hal_Context.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Hal_Context.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hal_Core.o: ../Sources/BSW/Os/Os_Hal_Core.c
	@echo 'Building file: $<'
	@echo 'Executing target #111 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hal_Core.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Hal_Core.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hal_Entry.o: ../Sources/BSW/Os/Os_Hal_Entry.asm
	@echo 'Building file: $<'
	@echo 'Executing target #112 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hal_Entry.args" -o "Sources/BSW/Os/Os_Hal_Entry.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hal_INTC.o: ../Sources/BSW/Os/Os_Hal_INTC.c
	@echo 'Building file: $<'
	@echo 'Executing target #113 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hal_INTC.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Hal_INTC.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hal_MemoryProtection.o: ../Sources/BSW/Os/Os_Hal_MemoryProtection.c
	@echo 'Building file: $<'
	@echo 'Executing target #114 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hal_MemoryProtection.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Hal_MemoryProtection.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hal_Trap.o: ../Sources/BSW/Os/Os_Hal_Trap.asm
	@echo 'Building file: $<'
	@echo 'Executing target #115 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hal_Trap.args" -o "Sources/BSW/Os/Os_Hal_Trap.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Hook.o: ../Sources/BSW/Os/Os_Hook.c
	@echo 'Building file: $<'
	@echo 'Executing target #116 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Hook.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Hook.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Interrupt.o: ../Sources/BSW/Os/Os_Interrupt.c
	@echo 'Building file: $<'
	@echo 'Executing target #117 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Interrupt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Interrupt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Ioc.o: ../Sources/BSW/Os/Os_Ioc.c
	@echo 'Building file: $<'
	@echo 'Executing target #118 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Ioc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Ioc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Isr.o: ../Sources/BSW/Os/Os_Isr.c
	@echo 'Building file: $<'
	@echo 'Executing target #119 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Isr.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Isr.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Job.o: ../Sources/BSW/Os/Os_Job.c
	@echo 'Building file: $<'
	@echo 'Executing target #120 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Job.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Job.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Lock.o: ../Sources/BSW/Os/Os_Lock.c
	@echo 'Building file: $<'
	@echo 'Executing target #121 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Lock.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Lock.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_MemoryProtection.o: ../Sources/BSW/Os/Os_MemoryProtection.c
	@echo 'Building file: $<'
	@echo 'Executing target #122 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_MemoryProtection.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_MemoryProtection.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Peripheral.o: ../Sources/BSW/Os/Os_Peripheral.c
	@echo 'Building file: $<'
	@echo 'Executing target #123 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Peripheral.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Peripheral.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_PriorityQueue.o: ../Sources/BSW/Os/Os_PriorityQueue.c
	@echo 'Building file: $<'
	@echo 'Executing target #124 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_PriorityQueue.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_PriorityQueue.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Resource.o: ../Sources/BSW/Os/Os_Resource.c
	@echo 'Building file: $<'
	@echo 'Executing target #125 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Resource.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Resource.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_ScheduleTable.o: ../Sources/BSW/Os/Os_ScheduleTable.c
	@echo 'Building file: $<'
	@echo 'Executing target #126 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_ScheduleTable.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_ScheduleTable.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Scheduler.o: ../Sources/BSW/Os/Os_Scheduler.c
	@echo 'Building file: $<'
	@echo 'Executing target #127 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Scheduler.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Scheduler.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_ServiceFunction.o: ../Sources/BSW/Os/Os_ServiceFunction.c
	@echo 'Building file: $<'
	@echo 'Executing target #128 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_ServiceFunction.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_ServiceFunction.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Spinlock.o: ../Sources/BSW/Os/Os_Spinlock.c
	@echo 'Building file: $<'
	@echo 'Executing target #129 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Spinlock.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Spinlock.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Stack.o: ../Sources/BSW/Os/Os_Stack.c
	@echo 'Building file: $<'
	@echo 'Executing target #130 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Stack.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Stack.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Task.o: ../Sources/BSW/Os/Os_Task.c
	@echo 'Building file: $<'
	@echo 'Executing target #131 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Task.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Task.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Thread.o: ../Sources/BSW/Os/Os_Thread.c
	@echo 'Building file: $<'
	@echo 'Executing target #132 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Thread.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Thread.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Timer.o: ../Sources/BSW/Os/Os_Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #133 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Timer.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Timer.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_TimingProtection.o: ../Sources/BSW/Os/Os_TimingProtection.c
	@echo 'Building file: $<'
	@echo 'Executing target #134 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_TimingProtection.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_TimingProtection.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Trace.o: ../Sources/BSW/Os/Os_Trace.c
	@echo 'Building file: $<'
	@echo 'Executing target #135 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Trace.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Trace.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_Trap.o: ../Sources/BSW/Os/Os_Trap.c
	@echo 'Building file: $<'
	@echo 'Executing target #136 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_Trap.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_Trap.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/BSW/Os/Os_XSignal.o: ../Sources/BSW/Os/Os_XSignal.c
	@echo 'Building file: $<'
	@echo 'Executing target #137 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/BSW/Os/Os_XSignal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/BSW/Os/Os_XSignal.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


