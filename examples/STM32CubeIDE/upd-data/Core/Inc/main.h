/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_ucpd.h"
#include "stm32g4xx_ll_usart.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_dma.h"

#include "stm32g4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include "ili9341_font.h"
#include "ili9341_gfx.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef enum
{
  false = 0, FALSE = false, no  = false, NO  = false,
  true  = 1, TRUE  = true,  yes = true,  YES = true,
}
bool_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

#define _isTRUE(x)  (0 != !!(x))
#define _isFALSE(x) (0 == !!(x))

#define _OK(x)  _isTRUE(x)
#define _NOT(x) _isFALSE(x)

// short-hand GPIO macros for named pins
#define PIN_CLR(p) HAL_GPIO_WritePin(p ## _GPIO_Port, p ## _Pin, GPIO_PIN_RESET)
#define PIN_SET(p) HAL_GPIO_WritePin(p ## _GPIO_Port, p ## _Pin, GPIO_PIN_SET)
#define PIN_TGL(p) HAL_GPIO_TogglePin(p ## _GPIO_Port, p ## _Pin)

// slightly more verbose for clarity when controlling LEDs
#define LED_ON(p) PIN_SET(p)
#define LED_OFF(p) PIN_CLR(p)
#define LED_TOGGLE(p) PIN_TGL(p)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
ili9341_device_t *screen(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VDDA_APPLI 3264
#define VSENSE_Pin GPIO_PIN_0
#define VSENSE_GPIO_Port GPIOA
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define TFT_CS_Pin GPIO_PIN_4
#define TFT_CS_GPIO_Port GPIOA
#define SPI1_TFT_SCK_Pin GPIO_PIN_5
#define SPI1_TFT_SCK_GPIO_Port GPIOA
#define SPI1_TFT_MISO_Pin GPIO_PIN_6
#define SPI1_TFT_MISO_GPIO_Port GPIOA
#define SPI1_TFT_MOSI_Pin GPIO_PIN_7
#define SPI1_TFT_MOSI_GPIO_Port GPIOA
#define TFT_DC_Pin GPIO_PIN_0
#define TFT_DC_GPIO_Port GPIOB
#define TOUCH_IRQ_Pin GPIO_PIN_8
#define TOUCH_IRQ_GPIO_Port GPIOA
#define TOUCH_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define TOUCH_CS_Pin GPIO_PIN_12
#define TOUCH_CS_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define TFT_RESET_Pin GPIO_PIN_5
#define TFT_RESET_GPIO_Port GPIOB
#define LED1_GREEN_Pin GPIO_PIN_8
#define LED1_GREEN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define VSENSE_ADC_Instance ADC1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
