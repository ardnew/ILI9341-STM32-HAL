################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USBPD/App/subdir.mk
-include USBPD/subdir.mk
-include Middlewares/USBPD/subdir.mk
-include Middlewares/FreeRTOS/subdir.mk
-include Drivers/STM32G4xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/ILI9341/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
upd-data.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
upd-data.list \

OBJCOPY_BIN += \
upd-data.bin \


# All Target
all: upd-data.elf secondary-outputs

# Tool invocations
upd-data.elf: $(OBJS) $(USER_OBJS) /Users/andrew/Development/STM32CubeIDE/git/upd-data/STM32G431KBTX_FLASH.ld
	arm-none-eabi-gcc -o "upd-data.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/andrew/Development/STM32CubeIDE/git/upd-data/STM32G431KBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="upd-data.map" -Wl,--gc-sections -static -L"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/lib" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

upd-data.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "upd-data.list"
	@echo 'Finished building: $@'
	@echo ' '

upd-data.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "upd-data.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
