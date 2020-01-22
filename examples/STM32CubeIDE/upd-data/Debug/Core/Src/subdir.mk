################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/app_freertos.c \
../Core/Src/boing.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/spi.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_hal_timebase_tim.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/ucpd.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/app_freertos.o \
./Core/Src/boing.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/spi.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_hal_timebase_tim.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/ucpd.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/app_freertos.d \
./Core/Src/boing.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/spi.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_hal_timebase_tim.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/ucpd.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/adc.o: ../Core/Src/adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/app_freertos.o: ../Core/Src/app_freertos.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/app_freertos.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/boing.o: ../Core/Src/boing.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/boing.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/dma.o: ../Core/Src/dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/dma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/spi.o: ../Core/Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32g4xx_hal_msp.o: ../Core/Src/stm32g4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32g4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32g4xx_hal_timebase_tim.o: ../Core/Src/stm32g4xx_hal_timebase_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32g4xx_hal_timebase_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32g4xx_it.o: ../Core/Src/stm32g4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32g4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32g4xx.o: ../Core/Src/system_stm32g4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32g4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/ucpd.o: ../Core/Src/ucpd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/ucpd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usart.o: ../Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
