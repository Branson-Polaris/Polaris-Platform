################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/arch/subdir.mk
-include lwip/src/api/subdir.mk
-include freertos/src/subdir.mk
-include chip/src/subdir.mk
-include board_Eval/src/subdir.mk
-include App/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: P1_AC_freertos.axf

dependents:
	-cd C:/Users/E1356301/Documents/MCUXpressoIDE_11.3.1_5262/workspace/P1_AC_freertos/Release && $(MAKE) all

# Tool invocations
P1_AC_freertos.axf: $(OBJS) $(USER_OBJS) C:/Users/E1356301/Documents/MCUXpressoIDE_11.3.1_5262/workspace/P1_AC_freertos/Release/P1_AC_freertos.axf
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="P1_AC_freertos.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "P1_AC_freertos_Debug.ld" -o "P1_AC_freertos.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) P1_AC_freertos.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "P1_AC_freertos.axf"; # arm-none-eabi-objcopy -v -O binary "P1_AC_freertos.axf" "P1_AC_freertos.bin" ; # checksum -p LPC1788 -d "P1_AC_freertos.bin";
	-@echo ' '

.PHONY: all clean dependents post-build
C:/Users/E1356301/Documents/MCUXpressoIDE_11.3.1_5262/workspace/P1_AC_freertos/Release/P1_AC_freertos.axf:

-include ../makefile.targets
