# upd-data
STM32CubeIDE project for STM32G431KB Nucleo-32 devices displaying many different effects and graphics. See [Core/Src/app_freertos.c](Core/Src/app_freertos.c) for usage.

To configure for your specific Nucleo device, from STM32CubeIDE, open the project properties and be sure to set the following:

**You must set these paths twice**. Unfortunately Eclipse can't use the same variables for both of these purposes.

Once in `Linked Resources` to allow the IDE to resolve project source paths (in .project file) dynamically - so that they show up in the `Project Explorer` navigation sideview:
```sh
# the path to wherever your firmware package is located (e.g. ~/STM32Cube/Repository/STM32Cube_FW_G4_V1.1.0)
Resource > Linked Resources > FW_LOC
# and the path to wherever you've placed the ILI9341-STM32-HAL library (e.g. ~/src/ILI9341-STM32-HAL/ILI9341)
Resource > Linked Resources > ILI9341_LOC
```

And once for the compiler+linker to know how to resolve these library paths:
```sh
# ditto, the path to your firmware package
C/C++ Build > Build Variables > FW_PATH
# and the path to the library
C/C++ Build > Build Variables > ILI9341_PATH
```

---

Careful regenerating initialization code if you load the .ioc file in STM32CubeMX/IDE, as it will probably break required configuration that was manually changed in source code. If you must, create a backup and diff it with the generated code to revert any of the unintended changes. **UNSOLICITED PRODUCT PLACEMENT:** I personally use and love [BeyondCompare](https://www.scootersoftware.com) for all diff tasks.


