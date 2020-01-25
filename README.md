# ILI9341-STM32-HAL
##### ILI9341 color TFT display and XPT2046 touchscreen driver for STM32 using HAL SPI with DMA

---

#### Features include:
- [x] HAL-based SPI interface making it easy to support many STM32 devices
- [x] Modular configuration supporting STM32CubeMX-generated SPI and DMA interfaces
- [x] 16-bit color (RGB 565) with automatic handling of byte ordering
- [x] Very fast, high-level, DMA-driven drawing routines for:
  - [x] all graphics primitives: pixels, lines, rectangles (filled/hollow), circles (filled/hollow)
  - [x] 1-bit (1BPP) bitmaps, drawn with provided 16-bit foreground/background color
  - [x] Basic fonts for ASCII character strings (3 font sizes provided)
- [x] Low-level ILI9341 and XPT2046 SPI interfaces for accessing respective digital interfaces directly
- [x] Touchscreen callback support for on-touch and on-release events
- [x] Touch calibration (two methods) for automatic translation of touch coordinates to screen coordinates
  - [x] Linear interpolation for simply scaling the touch coordinate from a given domain
  - [x] 3-point calibration based on [the often-referenced TI paper from Fang & Chang](http://www.ti.com/lit/an/slyt277/slyt277.pdf)
- [x] Example applications for demonstrating usage

---

Source code for the following demo is provided as STM32Cube project and can be found at [examples/STM32CubeIDE/upd-data](examples/STM32CubeIDE/upd-data):

[![ILI9341 driver for STM32 Nucleo](https://img.youtube.com/vi/L03uCfl4xnc/0.jpg)](https://www.youtube.com/watch?v=L03uCfl4xnc "ILI9341 driver for STM32 Nucleo")

Source code for only the ported `pyportal_boing` demo using this library is here: [examples/boing](examples/boing)

---

#### Configuration:

1. Create an SPI device in STM32CubeIDE with **Format=Motorola**, **Size=8-bit**, **First=MSB**, **Polarity=Low**, **Phase=1Edge**.
   - Set the **BaudRatePrescalar** to the lowest possible your clock configuration will allow.
   - **_IMPORTANT_** The touchscreen has a maximum frequency of 2MHz, which is probably slower than you want your TFT SPI clock. So in the routine that reads touch coordinates (`ili9341_touch_pressed_t ili9341_touch_coordinate(ili9341_t *,uint16_t *,uint16_t *)` in [ILI9341/ili9341.c](ILI9341/ili9341.c)), make sure to adjust the lines that modify the SPI clock so that your baud rate is _less than 2MHz_ before communicating with the touchscreen (e.g. `MODIFY_REG(lcd->spi_hal->Instance->CR1, SPI_CR1_BR, SPI_BAUDRATEPRESCALER_128)`), and then restored to whatever setting you use here immedaitely afterwards. See the comments in that source file for both locations.
   - If using the touchscreen, you will probably want to set **Hardware NSSP=Disabled** (slave/chip-select) in favor of a software implementation, since you will need one signal for the TFT and a separate one for the touchscreen. Any two unused GPIO digital output pins will work.
2. Add a Memory->Peripheral DMA TX request for your SPI device with **PeriphInc=Disabled**, **MemInc=Enabled**, **PeriphDataAlignment=Byte**, **MemDataAlignment=Byte**, **Mode=Normal**.
   - **_IMPORTANT_** If using FreeRTOS, you will need to raise the DMA interrupt priority to something logically higher (numerically lower) than the FreeRTOS idle thread priority. For example, if FreeRTOS priority is set to **3** and SPI DMA TX is configured as **DMA1 channel 4**, set DMA IRQ priority to **2** with `HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 2, 0)`.
3. If using the touchscreen, be sure to configure the GPIO pin as external interrupt (EXTI) with rising/falling edge trigger detection (i.e. `GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING`).
4. Be sure to enable interrupts (NVIC) and generate interrupt handlers for SPI, DMA, and your touchscreen IRQ (if used).
5. If using the touchscreen, override the EXTI callback (`void HAL_GPIO_EXTI_Callback(uint16_t)`) somewhere in your application code and call `ili9341_touch_interrupt(ili9341_t *)` from inside that callback.

An example GPIO, SPI, and DMA configuration follows:

###### gpio.c

```
void MX_GPIO_Init(void)
{
  ...

  GPIO_InitStruct.Pin = TFT_CS_Pin|TOUCH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TFT_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(TFT_DC_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TFT_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TFT_RESET_GPIO_Port, &GPIO_InitStruct);

  ...
}
```

###### spi.c

```
void MX_SPI1_Init(void)
{
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
    { Error_Handler(); }
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = SPI1_TFT_SCK_Pin|SPI1_TFT_MISO_Pin|SPI1_TFT_MOSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    hdma_spi1_tx.Instance = DMA1_Channel4;
    hdma_spi1_tx.Init.Request = DMA_REQUEST_SPI1_TX;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
      { Error_Handler(); }

    __HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);

    HAL_NVIC_SetPriority(SPI1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
  }
}
```

###### dma.c

```
void MX_DMA_Init(void)
{
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3, 0));
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);

  NVIC_SetPriority(DMA1_Channel2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3, 0));
  NVIC_EnableIRQ(DMA1_Channel2_IRQn);

  NVIC_SetPriority(DMA1_Channel3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3, 0));
  NVIC_EnableIRQ(DMA1_Channel3_IRQn);

  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}
```

###### main.c

```
ili9341_t *_screen;

ili9341_t *screen(void)
{
  return _screen;
}

void screenTouchBegin(ili9341_t *lcd, uint16_t x, uint16_t y)
{
  ;
}

void screenTouchEnd(ili9341_t *lcd, uint16_t x, uint16_t y)
{
  ;
}

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();

  _screen = ili9341_new(
      &hspi1,
      TFT_RESET_GPIO_Port, TFT_RESET_Pin,
      TFT_CS_GPIO_Port,    TFT_CS_Pin,
      TFT_DC_GPIO_Port,    TFT_DC_Pin,
      isoLandscape,
      TOUCH_CS_GPIO_Port,  TOUCH_CS_Pin,
      TOUCH_IRQ_GPIO_Port, TOUCH_IRQ_Pin,
      itsSupported,
      itnNormalized);

//  ili9341_calibrate_scalar(_screen, 3763, 3931, 338, 211);
//  ili9341_calibrate_3point(_screen, 320, 240,
//       13,    30,
//      312,   113,
//      167,   214,
//     8770,  4320,
//    18240, 30262,
//    30648, 17720);

  ili9341_set_touch_pressed_begin(_screen, screenTouchBegin);
  ili9341_set_touch_pressed_end(_screen, screenTouchEnd);

  MX_FREERTOS_Init();

  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  while (1) {}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
    case TOUCH_IRQ_Pin:
      ili9341_touch_interrupt(_screen);
      break;

    default:
      // unhandled interrupt pin
      break;
  }
}

```
