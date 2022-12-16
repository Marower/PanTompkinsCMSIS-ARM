################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FastMathFunctions/FastMathFunctions.c \
C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FastMathFunctions/FastMathFunctionsF16.c 

OBJS += \
./Source/FastMathFunctions/FastMathFunctions.o \
./Source/FastMathFunctions/FastMathFunctionsF16.o 

C_DEPS += \
./Source/FastMathFunctions/FastMathFunctions.d \
./Source/FastMathFunctions/FastMathFunctionsF16.d 


# Each subdirectory must supply rules for building sources it contributes
Source/FastMathFunctions/FastMathFunctions.o: C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FastMathFunctions/FastMathFunctions.c Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/Include" -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/PrivateInclude" -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Source/FastMathFunctions/FastMathFunctionsF16.o: C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code\ -\ example/CMSIS-DSP\ Library/Source/FastMathFunctions/FastMathFunctionsF16.c Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/Include" -I"C:/Users/mzylinsk/STM32CubeIDE/workspace_1.10.1/PanTompkins/Code - example/CMSIS-DSP Library/PrivateInclude" -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-FastMathFunctions

clean-Source-2f-FastMathFunctions:
	-$(RM) ./Source/FastMathFunctions/FastMathFunctions.d ./Source/FastMathFunctions/FastMathFunctions.o ./Source/FastMathFunctions/FastMathFunctions.su ./Source/FastMathFunctions/FastMathFunctionsF16.d ./Source/FastMathFunctions/FastMathFunctionsF16.o ./Source/FastMathFunctions/FastMathFunctionsF16.su

.PHONY: clean-Source-2f-FastMathFunctions

