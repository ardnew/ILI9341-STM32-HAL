################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ILI9341/ili9341.c \
../Core/ILI9341/ili9341_font.c \
../Core/ILI9341/ili9341_gfx.c 

OBJS += \
./Core/ILI9341/ili9341.o \
./Core/ILI9341/ili9341_font.o \
./Core/ILI9341/ili9341_gfx.o 

C_DEPS += \
./Core/ILI9341/ili9341.d \
./Core/ILI9341/ili9341_font.d \
./Core/ILI9341/ili9341_gfx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ILI9341/ili9341.o: ../Core/ILI9341/ili9341.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/ILI9341/ili9341.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/ILI9341/ili9341_font.o: ../Core/ILI9341/ili9341_font.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/ILI9341/ili9341_font.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/ILI9341/ili9341_gfx.o: ../Core/ILI9341/ili9341_gfx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DUSBPD_PORT_COUNT=1' -DSTM32G431xx -DUSE_HAL_DRIVER -D_RTOS -DUSE_FULL_LL_DRIVER -D_SNK -DDEBUG -DUSBPDCORE_LIB_PD3_FULL -c -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/STM32G4xx_HAL_Driver/Inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Drivers/CMSIS/Include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Devices/STM32G4XX/inc" -I"/Users/andrew/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0/Middlewares/ST/STM32_USBPD_Library/Core/inc" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/USBPD/App" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/ILI9341" -I"/Users/andrew/Development/STM32CubeIDE/git/upd-data/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/ILI9341/ili9341_gfx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

