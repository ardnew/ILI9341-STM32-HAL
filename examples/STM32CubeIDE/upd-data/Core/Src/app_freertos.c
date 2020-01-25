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

#include <stdlib.h>
#include <stdio.h>

#include "boing.h"
#include "ili9341_gfx.h"
#include "ili9341.h"
#include "ina260.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define TEST_BOING
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
void testScreenFill(ili9341_t *lcd);
void testScreenLines(ili9341_t *lcd);
void testScreenRects(ili9341_t *lcd);
void testScreenCircles(ili9341_t *lcd);
void testScreenText(ili9341_t *lcd);
void testVoltageCurrentText(ili9341_t *lcd, ina260_t *pow);
#if defined(TEST_BOING)
void testBoing(ili9341_t *lcd);
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
#if defined(TEST_BOING)
  _boingInitialized = ibFalse;
#endif
  osThreadDef(screenTask, ScreenTask, osPriorityNormal, 0, 1024);
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
  static uint8_t suite = 1;

  for (;;)
  {
    if (NULL != screenLockHandle)
    {
      if (osOK == osSemaphoreWait(screenLockHandle, osWaitForever))
      {
        ili9341_t *lcd = display();
        ina260_t *pow = power();

        switch (suite) {

          case 0:
            testScreenFill(lcd);
            testScreenLines(lcd);
            osDelay(2000);
            testScreenRects(lcd);
            osDelay(2000);
            testScreenCircles(lcd);
            osDelay(2000);
            //testScreenText(lcd);
            //osDelay(1000);
#if defined(TEST_BOING)
            ++suite;
#endif
            break;

          case 1:
#if defined(TEST_BOING)
            testBoing(lcd);
#endif
            break;

          case 2:
            testVoltageCurrentText(lcd, pow);
            osDelay(250);
            break;

        }

        osSemaphoreRelease(screenLockHandle);
      }
    }
  }
}

void testScreenFill(ili9341_t *lcd)
{
  ili9341_fill_screen(lcd, ILI9341_BLUE);
  osDelay(500);
  ili9341_fill_screen(lcd, ILI9341_RED);
  osDelay(500);
  ili9341_fill_screen(lcd, ILI9341_GREEN);
  osDelay(500);
}

void testScreenLines(ili9341_t *lcd)
{
  ili9341_fill_screen(lcd, ILI9341_BLACK);

  ili9341_color_t color;
  uint8_t wheel = 0U;

  for (int32_t i = 0; i < lcd->screen_size.height; i += 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(lcd, color, 0, 0, lcd->screen_size.width, i); }
  for (int32_t i = lcd->screen_size.width; i >= 0; i -= 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(lcd, color, 0, 0, i, lcd->screen_size.height); }

  osDelay(500);

  for (int32_t i = 0; i < lcd->screen_size.height; i += 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(lcd, color, lcd->screen_size.width, lcd->screen_size.height, 0, lcd->screen_size.height - i); }
  for (int32_t i = lcd->screen_size.width; i >= 0; i -= 10)
    { color = ili9341_color_wheel(&wheel); wheel += 3;
      ili9341_draw_line(lcd, color, lcd->screen_size.width, lcd->screen_size.height, lcd->screen_size.width - i, 0); }
}

void testScreenRects(ili9341_t *lcd)
{
  ili9341_fill_screen(lcd, ILI9341_BLACK);

  ili9341_color_t color;
  uint8_t wheel = 0U;

  for (uint16_t i = 0, in = 0; i < lcd->screen_size.width; i += 16, ++in) {
    for (uint16_t j = 0, jn = 0; j < lcd->screen_size.height; j += 16, ++jn) {
      color = ili9341_color_wheel(&wheel);
      if ((in & 1) == (jn & 1)) {
        ili9341_fill_rect(lcd, color, i, j, 16, 16);
      } else {
        ili9341_draw_rect(lcd, ~color, i+2, j+2, 12, 12);
      }
    }
  }
}

void testScreenCircles(ili9341_t *lcd)
{
  ili9341_fill_screen(lcd, ILI9341_BLACK);

  uint16_t x_mid = lcd->screen_size.width / 2;
  uint16_t y_mid = lcd->screen_size.height / 2;
  uint16_t radius = x_mid;
  if (radius < y_mid)
    { radius = y_mid; }

  ili9341_color_t color;
  uint8_t wheel = 0U;

  for (int16_t i = radius; i >= 0; i -= 6) {
    color = ili9341_color_wheel(&wheel);
    wheel += 9;
    ili9341_fill_circle(lcd, color, x_mid, y_mid, i);
  }

  osDelay(500);

  for (int16_t i = 0, n = 0; i < lcd->screen_size.width; i += 24, ++n) {
    for (int16_t j = 0, m = 0; j < lcd->screen_size.height; j += 24, ++m) {

      color = ili9341_color_wheel(&wheel);
      wheel += 3;

      if ((n & 1) == (m & 1)) {
        ili9341_draw_circle(lcd, color, i + 12, j + 12, 16);
        ili9341_draw_circle(lcd, color, i + 12, j + 12, 10);
        ili9341_draw_circle(lcd, color, i + 12, j + 12, 4);
      }
      else {
        ili9341_draw_circle(lcd, color, i + 12, j + 12, 8);
      }
    }
  }
}

void testScreenText(ili9341_t *lcd)
{
  ili9341_fill_screen(lcd, ILI9341_BLACK);

  ili9341_text_attr_t textAttr = (ili9341_text_attr_t){
    .font = &ili9341_font_11x18,
    .fg_color = ILI9341_WHITE,
    .bg_color = ILI9341_RED,
    .origin_x = 10,
    .origin_y = 10
  };
  ili9341_draw_string(lcd, textAttr, "Hello world!");

}

void testVoltageCurrentText(ili9341_t *lcd, ina260_t *pow)
{
  ili9341_text_attr_t textAttr = (ili9341_text_attr_t){
    .font = &ili9341_font_11x18,
    .fg_color = ILI9341_WHITE,
    .bg_color = ILI9341_BLACK,
    .origin_x = 10,
    .origin_y = 10
  };

  ili9341_fill_rect(lcd, ILI9341_BLACK, 10, 10, lcd->screen_size.width - 20, textAttr.font->height);

  float v, c, p;
  (void)ina260_get_voltage(pow, &v);
  (void)ina260_get_current(pow, &c);
  (void)ina260_get_power(pow, &p);

  {
    char vsenseStr[64] = { '\0' };
    snprintf(vsenseStr, 64, "%dmV, %dmA, %dmW", (int16_t)v, (int16_t)c, (int16_t)p);
    ili9341_draw_string(lcd, textAttr, vsenseStr);
  }
}

#if defined(TEST_BOING)
void testBoing(ili9341_t *lcd)
{
  static boing_ball_t ball;

  if (ibNOT(_boingInitialized)) {
    ili9341_draw_bitmap_1b(lcd, BOING_COLOR_PLOT_SHADOW, BOING_COLOR_PLOT_COLOR,
        0, 0, 320, 240, (uint8_t *)BOING_PLOT);
    _boingInitialized = ibTrue;
    boing_init(&ball);
  }
  else {
    boing(lcd, &ball);
  }
}
#endif
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
