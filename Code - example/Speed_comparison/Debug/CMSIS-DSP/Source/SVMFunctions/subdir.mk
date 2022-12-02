################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS-DSP/Source/SVMFunctions/SVMFunctions.c \
../CMSIS-DSP/Source/SVMFunctions/SVMFunctionsF16.c 

OBJS += \
./CMSIS-DSP/Source/SVMFunctions/SVMFunctions.o \
./CMSIS-DSP/Source/SVMFunctions/SVMFunctionsF16.o 

C_DEPS += \
./CMSIS-DSP/Source/SVMFunctions/SVMFunctions.d \
./CMSIS-DSP/Source/SVMFunctions/SVMFunctionsF16.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS-DSP/Source/SVMFunctions/%.o CMSIS-DSP/Source/SVMFunctions/%.su: ../CMSIS-DSP/Source/SVMFunctions/%.c CMSIS-DSP/Source/SVMFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../USB_Device/App -I../USB_Device/Target -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2d-DSP-2f-Source-2f-SVMFunctions

clean-CMSIS-2d-DSP-2f-Source-2f-SVMFunctions:
	-$(RM) ./CMSIS-DSP/Source/SVMFunctions/SVMFunctions.d ./CMSIS-DSP/Source/SVMFunctions/SVMFunctions.o ./CMSIS-DSP/Source/SVMFunctions/SVMFunctions.su ./CMSIS-DSP/Source/SVMFunctions/SVMFunctionsF16.d ./CMSIS-DSP/Source/SVMFunctions/SVMFunctionsF16.o ./CMSIS-DSP/Source/SVMFunctions/SVMFunctionsF16.su

.PHONY: clean-CMSIS-2d-DSP-2f-Source-2f-SVMFunctions

