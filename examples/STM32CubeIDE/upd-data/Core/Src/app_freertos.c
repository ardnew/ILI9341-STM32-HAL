/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "boing.h"
#include "ili9341.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEST_BOING
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId screenTaskHandle;
osSemaphoreId screenLockHandle;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void ScreenTask(void const * argument);
void testScreenFill(ili9341_device_t *dev);
void testScreenLines(ili9341_device_t *dev);
void testScreenRects(ili9341_device_t *dev);
void testScreenCircles(ili9341_device_t *dev);
void testScreenText(ili9341_device_t *dev);
#if defined(TEST_BOING)
void testBoing(ili9341_device_t *dev);
static ili9341_bool_t _boingInitialized;
#endif
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  osSemaphoreDef(screenLock);
  screenLockHandle = osSemaphoreCreate(osSemaphore(screenLock), 1);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  _boingInitialized = ibFalse;
  osThreadDef(screenTask, ScreenTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  screenTaskHandle = osThreadCreate(osThread(screenTask), NULL);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void ScreenTask(void const * argument)
{
  static uint8_t suite = 0;

  for (;;)
  {
    if (NULL != screenLockHandle)
    {
      if (osOK == osSemaphoreWait(screenLockHandle, osWaitForever))
      {
        ili9341_device_t *dev = screen();

        switch (suite) {
          case 0:
            testScreenFill(dev);
            testScreenLines(dev);
            osDelay(2000);
            testScreenRects(dev);
            osDelay(2000);
            testScreenCircles(dev);
            osDelay(2000);
            //testScreenText(dev);
            //osDelay(1000);
            ++suite;
            break;

          case 1:
            testBoing(dev);
            break;
        }

        osSemaphoreRelease(screenLockHandle);
      }
    }
  }
}

void testScreenFill(ili9341_device_t *dev)
{
  ili9341_fill_screen(dev, ILI9341_BLUE);
  osDelay(500);
  ili9341_fill_screen(dev, ILI9341_RED);
  osDelay(500);
  ili9341_fill_screen(dev, ILI9341_GREEN);
  osDelay(500);
}

void testScreenLines(ili9341_device_t *dev)
{
  ili9341_fill_screen(dev, ILI9341_BLACK);

  ili9341_color_t color;
  uint8_t wheel = 0U;

  for (int32_t i = 0; i < dev->screen_size.height; i += 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(dev, color, 0, 0, dev->screen_size.width, i); }
  for (int32_t i = dev->screen_size.width; i >= 0; i -= 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(dev, color, 0, 0, i, dev->screen_size.height); }

  osDelay(500);

  for (int32_t i = 0; i < dev->screen_size.height; i += 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(dev, color, dev->screen_size.width, dev->screen_size.height, 0, dev->screen_size.height - i); }
  for (int32_t i = dev->screen_size.width; i >= 0; i -= 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(dev, color, dev->screen_size.width, dev->screen_size.height, dev->screen_size.width - i, 0); }
}

void testScreenRects(ili9341_device_t *dev)
{
  ili9341_fill_screen(dev, ILI9341_BLACK);

  ili9341_color_t color;
  uint8_t wheel = 0U;

  for (uint16_t i = 0, in = 0; i < dev->screen_size.width; i += 16, ++in) {
    for (uint16_t j = 0, jn = 0; j < dev->screen_size.height; j += 16, ++jn) {
      color = ili9341_color_wheel(&wheel);
      if ((in & 1) == (jn & 1)) {
        ili9341_fill_rect(dev, color, i, j, 16, 16);
      } else {
        ili9341_draw_rect(dev, ~color, i+2, j+2, 12, 12);
      }
    }
  }
}

void testScreenCircles(ili9341_device_t *dev)
{
  ili9341_fill_screen(dev, ILI9341_BLACK);

  uint16_t x_mid = dev->screen_size.width / 2;
  uint16_t y_mid = dev->screen_size.height / 2;
  uint16_t radius = x_mid;
  if (radius < y_mid)
    { radius = y_mid; }

  ili9341_color_t color;
  uint8_t wheel = 0U;

  for (int16_t i = radius; i >= 0; i -= 6) {
    color = ili9341_color_wheel(&wheel);
    wheel += 9;
    ili9341_fill_circle(dev, color, x_mid, y_mid, i);
  }

  osDelay(500);

  for (int16_t i = 0, n = 0; i < dev->screen_size.width; i += 24, ++n) {
    for (int16_t j = 0, m = 0; j < dev->screen_size.height; j += 24, ++m) {

      color = ili9341_color_wheel(&wheel);
      wheel += 3;

      if ((n & 1) == (m & 1)) {
        ili9341_draw_circle(dev, color, i + 12, j + 12, 16);
        ili9341_draw_circle(dev, color, i + 12, j + 12, 10);
        ili9341_draw_circle(dev, color, i + 12, j + 12, 4);
      }
      else {
        ili9341_draw_circle(dev, color, i + 12, j + 12, 8);
      }
    }
  }
}

void testScreenText(ili9341_device_t *dev)
{
  ili9341_fill_screen(dev, ILI9341_BLACK);

  ili9341_text_attr_t textAttr = (ili9341_text_attr_t){
    .font = &ili9341_font_11x18,
    .fg_color = ILI9341_WHITE,
    .bg_color = ILI9341_RED,
    .origin_x = 10,
    .origin_y = 10
  };
  ili9341_draw_string(dev, textAttr, "Hello world!");

}

void testBoing(ili9341_device_t *dev)
{
  static boing_ball_t ball;

  if (ibNOT(_boingInitialized)) {
    ili9341_draw_bitmap_1b(dev, BOING_COLOR_PLOT_SHADOW, BOING_COLOR_PLOT_COLOR,
        0, 0, 320, 240, (uint8_t *)BOING_PLOT);
    _boingInitialized = ibTrue;
    boing_init(&ball);
  }
  else {
    boing(dev, &ball);
  }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
