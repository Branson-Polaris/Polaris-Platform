################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/ControlTask.c \
../App/src/Main.c \
../App/src/QuickCRC32Algorithm.c \
../App/src/SocketReceiver.c \
../App/src/TcpClient.c \
../App/src/adc.c \
../App/src/alarm.c \
../App/src/cr_redlib_heap_fix.c \
../App/src/cr_startup_lpc177x_8x.c \
../App/src/downstroke.c \
../App/src/driveon.c \
../App/src/eeprom.c \
../App/src/global.c \
../App/src/inputs.c \
../App/src/ioinit.c \
../App/src/qei.c \
../App/src/ready.c \
../App/src/returnstroke.c \
../App/src/setoutputs.c \
../App/src/statemachine.c \
../App/src/sysinit.c 

OBJS += \
./App/src/ControlTask.o \
./App/src/Main.o \
./App/src/QuickCRC32Algorithm.o \
./App/src/SocketReceiver.o \
./App/src/TcpClient.o \
./App/src/adc.o \
./App/src/alarm.o \
./App/src/cr_redlib_heap_fix.o \
./App/src/cr_startup_lpc177x_8x.o \
./App/src/downstroke.o \
./App/src/driveon.o \
./App/src/eeprom.o \
./App/src/global.o \
./App/src/inputs.o \
./App/src/ioinit.o \
./App/src/qei.o \
./App/src/ready.o \
./App/src/returnstroke.o \
./App/src/setoutputs.o \
./App/src/statemachine.o \
./App/src/sysinit.o 

C_DEPS += \
./App/src/ControlTask.d \
./App/src/Main.d \
./App/src/QuickCRC32Algorithm.d \
./App/src/SocketReceiver.d \
./App/src/TcpClient.d \
./App/src/adc.d \
./App/src/alarm.d \
./App/src/cr_redlib_heap_fix.d \
./App/src/cr_startup_lpc177x_8x.d \
./App/src/downstroke.d \
./App/src/driveon.d \
./App/src/eeprom.d \
./App/src/global.d \
./App/src/inputs.d \
./App/src/ioinit.d \
./App/src/qei.d \
./App/src/ready.d \
./App/src/returnstroke.d \
./App/src/setoutputs.d \
./App/src/statemachine.d \
./App/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o: ../App/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\App\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\lwip\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\lwip\inc\ipv4" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


