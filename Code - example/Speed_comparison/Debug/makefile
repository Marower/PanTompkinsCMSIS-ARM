################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_Device/Target/subdir.mk
-include USB_Device/App/subdir.mk
-include Source/TransformFunctions/subdir.mk
-include Source/SupportFunctions/subdir.mk
-include Source/StatisticsFunctions/subdir.mk
-include Source/SVMFunctions/subdir.mk
-include Source/QuaternionMathFunctions/subdir.mk
-include Source/MatrixFunctions/subdir.mk
-include Source/InterpolationFunctions/subdir.mk
-include Source/FilteringFunctions/subdir.mk
-include Source/FastMathFunctions/subdir.mk
-include Source/DistanceFunctions/subdir.mk
-include Source/ControllerFunctions/subdir.mk
-include Source/ComplexMathFunctions/subdir.mk
-include Source/CommonTables/subdir.mk
-include Source/BayesFunctions/subdir.mk
-include Source/BasicMathFunctions/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32WBxx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := PanTompkins-speedComparison
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
PanTompkins-speedComparison.elf \

MAP_FILES += \
PanTompkins-speedComparison.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PanTompkins-speedComparison.list \


# All Target
all: main-build

# Main-build Target
main-build: PanTompkins-speedComparison.elf secondary-outputs

# Tool invocations
PanTompkins-speedComparison.elf PanTompkins-speedComparison.map: $(OBJS) $(USER_OBJS) C:\Users\mzylinsk\STM32CubeIDE\workspace_1.10.1\PanTompkins\Code\ -\ example\speed_comparison\STM32WB55CGUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "PanTompkins-speedComparison.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\mzylinsk\STM32CubeIDE\workspace_1.10.1\PanTompkins\Code - example\speed_comparison\STM32WB55CGUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="PanTompkins-speedComparison.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PanTompkins-speedComparison.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PanTompkins-speedComparison.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) PanTompkins-speedComparison.elf PanTompkins-speedComparison.list PanTompkins-speedComparison.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
