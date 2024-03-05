################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/arch/lpc17xx_40xx_emac.c \
../lwip/src/arch/lpc_debug.c \
../lwip/src/arch/sys_arch_freertos.c 

OBJS += \
./lwip/src/arch/lpc17xx_40xx_emac.o \
./lwip/src/arch/lpc_debug.o \
./lwip/src/arch/sys_arch_freertos.o 

C_DEPS += \
./lwip/src/arch/lpc17xx_40xx_emac.d \
./lwip/src/arch/lpc_debug.d \
./lwip/src/arch/sys_arch_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/arch/%.o: ../lwip/src/arch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M3 -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\board_Eval\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\chip\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\lwip\inc" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\lwip\inc\ipv4" -I"C:\Users\E1356301\Documents\MCUXpressoIDE_11.3.1_5262\workspace\P1_AC_freertos\freertos\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


