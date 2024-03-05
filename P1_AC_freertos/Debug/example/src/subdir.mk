################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/QuickCRC32Algorithm.c \
../example/src/cr_redlib_heap_fix.c \
../example/src/cr_startup_lpc177x_8x.c \
../example/src/lwip_tcpecho_freertos.c \
../example/src/sysinit.c \
../example/src/tcpecho.c 

OBJS += \
./example/src/QuickCRC32Algorithm.o \
./example/src/cr_redlib_heap_fix.o \
./example/src/cr_startup_lpc177x_8x.o \
./example/src/lwip_tcpecho_freertos.o \
./example/src/sysinit.o \
./example/src/tcpecho.o 

C_DEPS += \
./example/src/QuickCRC32Algorithm.d \
./example/src/cr_redlib_heap_fix.d \
./example/src/cr_startup_lpc177x_8x.d \
./example/src/lwip_tcpecho_freertos.d \
./example/src/sysinit.d \
./example/src/tcpecho.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\lpc_chip_177x_8x\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\lpc_board_ea_devkit_1788\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freeetos\example\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freeetos\lwip\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freeetos\lwip\inc\ipv4" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freeetos\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


