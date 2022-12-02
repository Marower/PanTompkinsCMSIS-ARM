################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS-DSP/Source/CommonTables/CommonTables.c \
../CMSIS-DSP/Source/CommonTables/CommonTablesF16.c 

OBJS += \
./CMSIS-DSP/Source/CommonTables/CommonTables.o \
./CMSIS-DSP/Source/CommonTables/CommonTablesF16.o 

C_DEPS += \
./CMSIS-DSP/Source/CommonTables/CommonTables.d \
./CMSIS-DSP/Source/CommonTables/CommonTablesF16.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS-DSP/Source/CommonTables/%.o CMSIS-DSP/Source/CommonTables/%.su: ../CMSIS-DSP/Source/CommonTables/%.c CMSIS-DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../USB_Device/App -I../USB_Device/Target -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2d-DSP-2f-Source-2f-CommonTables

clean-CMSIS-2d-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./CMSIS-DSP/Source/CommonTables/CommonTables.d ./CMSIS-DSP/Source/CommonTables/CommonTables.o ./CMSIS-DSP/Source/CommonTables/CommonTables.su ./CMSIS-DSP/Source/CommonTables/CommonTablesF16.d ./CMSIS-DSP/Source/CommonTables/CommonTablesF16.o ./CMSIS-DSP/Source/CommonTables/CommonTablesF16.su

.PHONY: clean-CMSIS-2d-DSP-2f-Source-2f-CommonTables

