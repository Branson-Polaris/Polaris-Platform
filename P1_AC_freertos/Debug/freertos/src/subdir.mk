################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/src/FreeRTOSCommonHooks.c \
../freertos/src/heap_3.c \
../freertos/src/list.c \
../freertos/src/port.c \
../freertos/src/queue.c \
../freertos/src/tasks.c 

OBJS += \
./freertos/src/FreeRTOSCommonHooks.o \
./freertos/src/heap_3.o \
./freertos/src/list.o \
./freertos/src/port.o \
./freertos/src/queue.o \
./freertos/src/tasks.o 

C_DEPS += \
./freertos/src/FreeRTOSCommonHooks.d \
./freertos/src/heap_3.d \
./freertos/src/list.d \
./freertos/src/port.d \
./freertos/src/queue.d \
./freertos/src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/src/%.o: ../freertos/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\board_Eval\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\chip\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\lwip\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\lwip\inc\ipv4" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


