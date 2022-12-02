################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS-DSP/Source/TransformFunctions/TransformFunctions.c \
../CMSIS-DSP/Source/TransformFunctions/TransformFunctionsF16.c 

OBJS += \
./CMSIS-DSP/Source/TransformFunctions/TransformFunctions.o \
./CMSIS-DSP/Source/TransformFunctions/TransformFunctionsF16.o 

C_DEPS += \
./CMSIS-DSP/Source/TransformFunctions/TransformFunctions.d \
./CMSIS-DSP/Source/TransformFunctions/TransformFunctionsF16.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS-DSP/Source/TransformFunctions/%.o CMSIS-DSP/Source/TransformFunctions/%.su: ../CMSIS-DSP/Source/TransformFunctions/%.c CMSIS-DSP/Source/TransformFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../USB_Device/App -I../USB_Device/Target -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2d-DSP-2f-Source-2f-TransformFunctions

clean-CMSIS-2d-DSP-2f-Source-2f-TransformFunctions:
	-$(RM) ./CMSIS-DSP/Source/TransformFunctions/TransformFunctions.d ./CMSIS-DSP/Source/TransformFunctions/TransformFunctions.o ./CMSIS-DSP/Source/TransformFunctions/TransformFunctions.su ./CMSIS-DSP/Source/TransformFunctions/TransformFunctionsF16.d ./CMSIS-DSP/Source/TransformFunctions/TransformFunctionsF16.o ./CMSIS-DSP/Source/TransformFunctions/TransformFunctionsF16.su

.PHONY: clean-CMSIS-2d-DSP-2f-Source-2f-TransformFunctions

