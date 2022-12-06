################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FilteringFunctions/FilteringFunctions.c \
C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FilteringFunctions/FilteringFunctionsF16.c 

OBJS += \
./Source/FilteringFunctions/FilteringFunctions.o \
./Source/FilteringFunctions/FilteringFunctionsF16.o 

C_DEPS += \
./Source/FilteringFunctions/FilteringFunctions.d \
./Source/FilteringFunctions/FilteringFunctionsF16.d 


# Each subdirectory must supply rules for building sources it contributes
Source/FilteringFunctions/FilteringFunctions.o: C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FilteringFunctions/FilteringFunctions.c Source/FilteringFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/Include" -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/PrivateInclude" -I../USB_Device/App -I../USB_Device/Target -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Source/FilteringFunctions/FilteringFunctionsF16.o: C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FilteringFunctions/FilteringFunctionsF16.c Source/FilteringFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/Include" -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/PrivateInclude" -I../USB_Device/App -I../USB_Device/Target -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-FilteringFunctions

clean-Source-2f-FilteringFunctions:
	-$(RM) ./Source/FilteringFunctions/FilteringFunctions.d ./Source/FilteringFunctions/FilteringFunctions.o ./Source/FilteringFunctions/FilteringFunctions.su ./Source/FilteringFunctions/FilteringFunctionsF16.d ./Source/FilteringFunctions/FilteringFunctionsF16.o ./Source/FilteringFunctions/FilteringFunctionsF16.su

.PHONY: clean-Source-2f-FilteringFunctions

