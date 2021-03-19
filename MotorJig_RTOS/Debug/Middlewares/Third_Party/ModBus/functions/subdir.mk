################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ModBus/functions/mbfunccoils.c \
../Middlewares/Third_Party/ModBus/functions/mbfuncdiag.c \
../Middlewares/Third_Party/ModBus/functions/mbfuncdisc.c \
../Middlewares/Third_Party/ModBus/functions/mbfuncholding.c \
../Middlewares/Third_Party/ModBus/functions/mbfuncinput.c \
../Middlewares/Third_Party/ModBus/functions/mbfuncother.c \
../Middlewares/Third_Party/ModBus/functions/mbutils.c 

OBJS += \
./Middlewares/Third_Party/ModBus/functions/mbfunccoils.o \
./Middlewares/Third_Party/ModBus/functions/mbfuncdiag.o \
./Middlewares/Third_Party/ModBus/functions/mbfuncdisc.o \
./Middlewares/Third_Party/ModBus/functions/mbfuncholding.o \
./Middlewares/Third_Party/ModBus/functions/mbfuncinput.o \
./Middlewares/Third_Party/ModBus/functions/mbfuncother.o \
./Middlewares/Third_Party/ModBus/functions/mbutils.o 

C_DEPS += \
./Middlewares/Third_Party/ModBus/functions/mbfunccoils.d \
./Middlewares/Third_Party/ModBus/functions/mbfuncdiag.d \
./Middlewares/Third_Party/ModBus/functions/mbfuncdisc.d \
./Middlewares/Third_Party/ModBus/functions/mbfuncholding.d \
./Middlewares/Third_Party/ModBus/functions/mbfuncinput.d \
./Middlewares/Third_Party/ModBus/functions/mbfuncother.d \
./Middlewares/Third_Party/ModBus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ModBus/functions/mbfunccoils.o: ../Middlewares/Third_Party/ModBus/functions/mbfunccoils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbfunccoils.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ModBus/functions/mbfuncdiag.o: ../Middlewares/Third_Party/ModBus/functions/mbfuncdiag.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbfuncdiag.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ModBus/functions/mbfuncdisc.o: ../Middlewares/Third_Party/ModBus/functions/mbfuncdisc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbfuncdisc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ModBus/functions/mbfuncholding.o: ../Middlewares/Third_Party/ModBus/functions/mbfuncholding.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbfuncholding.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ModBus/functions/mbfuncinput.o: ../Middlewares/Third_Party/ModBus/functions/mbfuncinput.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbfuncinput.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ModBus/functions/mbfuncother.o: ../Middlewares/Third_Party/ModBus/functions/mbfuncother.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbfuncother.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ModBus/functions/mbutils.o: ../Middlewares/Third_Party/ModBus/functions/mbutils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/ModBus/include -I../Middlewares/Third_Party/ModBus/functions -I../Middlewares/Third_Party/ModBus/rtu -I../Middlewares/Third_Party/ModBus/port -I../Middlewares/Third_Party/ModBus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/ModBus/functions/mbutils.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

