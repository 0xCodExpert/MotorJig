################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ModBus/ascii/mbascii.c 

OBJS += \
./Middlewares/Third_Party/ModBus/ascii/mbascii.o 

C_DEPS += \
./Middlewares/Third_Party/ModBus/ascii/mbascii.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ModBus/ascii/mbascii.o: ../Middlewares/Third_Party/ModBus/ascii/mbascii.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/ascii/mbascii.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

