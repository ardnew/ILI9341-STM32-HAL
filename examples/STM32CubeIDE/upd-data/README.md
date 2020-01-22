# upd-data
STM32CubeIDE project for STM32G431KB Nucleo-32 devices displaying many different effects and graphics. See [Core/Src/app_freertos.c](Core/Src/app_freertos.c) for usage.

To configure for your specific Nucleo device, from STM32CubeIDE, open the project properties and be sure to set the following:

    # the path to wherever your firmware package is located (e.g. ~/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0)
    Resource > Linked Resources > FW_LOC   

    # ditto, the path to your firmware package
    C/C++ Build > Build Variables > FW_PATH

Careful regenerating initialization code if you load the .ioc file in CubeMX, as it will probably break required configuration.
