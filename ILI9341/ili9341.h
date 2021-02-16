/*
 * ili9341.h
 *
 *  Created on: Nov 28, 2019
 *      Author: andrew
 */

#ifndef __ILI9341_H
#define __ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------- includes --

#if defined (STM32L4)
#include "stm32l4xx_hal.h"
#elif defined(STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32G4)
#include "stm32g4xx_hal.h"
#elif defined(STM32G0)
#include "stm32g0xx_hal.h"
#endif

// ------------------------------------------------------------------ defines --

#define __GPIO_PIN_CLR__     GPIO_PIN_RESET
#define __GPIO_PIN_SET__     GPIO_PIN_SET

#define __SPI_MAX_DELAY__    HAL_MAX_DELAY
#define __SPI_TX_BLOCK_MAX__ (1U * 1024U) // 1024 16-bit words (2 KiB)

// ------------------------------------------------------------------- macros --

#define __MSBYTEu16(u) (uint8_t)(((uint16_t)(u) >> 8U) & 0xFF)
#define __LSBYTEu16(u) (uint8_t)(((uint16_t)(u)      ) & 0xFF)

// convert value at addr to little-endian (16-bit)
#define __LEu16(addr)                                      \
    ( ( (((uint16_t)(*(((uint8_t *)(addr)) + 1)))      ) | \
        (((uint16_t)(*(((uint8_t *)(addr)) + 0))) << 8U) ) )

// convert value at addr to little-endian (32-bit)
#define __LEu32(addr)                                       \
    ( ( (((uint32_t)(*(((uint8_t *)(addr)) + 3)))       ) | \
        (((uint32_t)(*(((uint8_t *)(addr)) + 2))) <<  8U) | \
        (((uint32_t)(*(((uint8_t *)(addr)) + 1))) << 16U) | \
        (((uint32_t)(*(((uint8_t *)(addr)) + 0))) << 24U) ) )

#define __SWAP(t, a, b) { t s; s = a; a = b; b = s; }

// resulting integer width given as t, e.g. __FROUND(uint16_t, -1.3)
#define __FROUND(t, x) ((x) < 0.0F ? -((t)((-(x)) + 0.5F)) : (t)((x) + 0.5F))
#define __FABS(v) ((v) < 0.0F ? -(v) : (v))

#define ibOK(x)  (0 != !!(x))
#define ibNOT(x) (0 == !!(x))

// ----------------------------------------------------------- exported types --

typedef struct ili9341 ili9341_t;

typedef enum
{
  ibFalse = 0, ibNo  = ibFalse,
  ibTrue  = 1, ibYes = ibTrue,
}
ili9341_bool_t;

typedef ili9341_bool_t ibool_t; // short-hand alias

typedef struct
{
  union
  {
    uint16_t x;
    uint16_t width;
  };
  union
  {
    uint16_t y;
    uint16_t height;
  };
}
ili9341_two_dimension_t;

typedef enum
{
  // orientation is based on position of board pins when looking at the screen
  isoNONE                     = -1,
  isoDown,   isoPortrait      = isoDown,  // = 0
  isoRight,  isoLandscape     = isoRight, // = 1
  isoUp,     isoPortraitFlip  = isoUp,    // = 2
  isoLeft,   isoLandscapeFlip = isoLeft,  // = 3
  isoCOUNT                                // = 4
}
ili9341_screen_orientation_t;

typedef enum
{
  itsNONE = -1,
  itsNotSupported, // = 0
  itsSupported,    // = 1
  itsCOUNT         // = 2
}
ili9341_touch_support_t;

typedef enum
{
  itpNONE = -1,
  itpNotPressed, // = 0
  itpPressed,    // = 1
  itpCOUNT       // = 2
}
ili9341_touch_pressed_t;

typedef enum
{
  itnNONE = -1,
  itnNotNormalized, // = 0
  itnNormalized,    // = 1
  itnCOUNT          // = 2
}
ili9341_touch_normalize_t;

typedef enum
{
  itcNONE = -1,
  itcScalar, // = 0
  itc3Point, // = 1
  itcCOUNT,
}
ili9341_touch_calibration_t;

typedef struct
{
  ili9341_two_dimension_t min;
  ili9341_two_dimension_t max;
}
ili9341_scalar_calibrator_t;

typedef struct
{
  ili9341_two_dimension_t scale;
  int32_t delta_x;
  int32_t delta_y;
  float   alpha_x;
  float   beta_x;
  float   alpha_y;
  float   beta_y;
}
ili9341_3point_calibrator_t;

typedef enum
{
  issNONE = -1,
  issDisplayTFT,  // = 0
  issTouchScreen, // = 1
  issCOUNT        // = 2
}
ili9341_spi_slave_t;

typedef void (*ili9341_touch_callback_t)(ili9341_t *, uint16_t, uint16_t);

typedef HAL_StatusTypeDef ili9341_status_t;

struct ili9341
{
  SPI_HandleTypeDef *spi_hal;

  GPIO_TypeDef *reset_port;
  uint16_t      reset_pin;
  GPIO_TypeDef *tft_select_port;
  uint16_t      tft_select_pin;
  GPIO_TypeDef *data_command_port;
  uint16_t      data_command_pin;

  ili9341_screen_orientation_t orientation;
  ili9341_two_dimension_t      screen_size;

  GPIO_TypeDef *touch_select_port;
  uint16_t      touch_select_pin;
  GPIO_TypeDef *touch_irq_port;
  uint16_t      touch_irq_pin;

  ili9341_touch_support_t   touch_support;
  ili9341_touch_normalize_t touch_normalize;
  ili9341_two_dimension_t   touch_coordinate;
  ili9341_touch_calibration_t touch_calibration;
  ili9341_scalar_calibrator_t touch_scalar;
  ili9341_3point_calibrator_t touch_3point;

  ili9341_touch_pressed_t  touch_pressed;
  ili9341_touch_callback_t touch_pressed_begin;
  ili9341_touch_callback_t touch_pressed_end;
};

// ------------------------------------------------------- exported variables --

/* nothing */

// ------------------------------------------------------- exported functions --

ili9341_t *ili9341_new(

    SPI_HandleTypeDef *spi_hal,

    GPIO_TypeDef *reset_port,        uint16_t reset_pin,
    GPIO_TypeDef *tft_select_port,   uint16_t tft_select_pin,
    GPIO_TypeDef *data_command_port, uint16_t data_command_pin,

    ili9341_screen_orientation_t orientation,

    GPIO_TypeDef *touch_select_port, uint16_t touch_select_pin,
    GPIO_TypeDef *touch_irq_port,    uint16_t touch_irq_pin,

    ili9341_touch_support_t   touch_support,
    ili9341_touch_normalize_t touch_normalize);

void ili9341_touch_interrupt(ili9341_t *lcd);
ili9341_touch_pressed_t ili9341_touch_pressed(ili9341_t *lcd);

void ili9341_set_touch_pressed_begin(ili9341_t *lcd,
    ili9341_touch_callback_t callback);
void ili9341_set_touch_pressed_end(ili9341_t *lcd,
    ili9341_touch_callback_t callback);

ili9341_touch_pressed_t ili9341_touch_coordinate(ili9341_t *lcd,
    uint16_t *x_pos, uint16_t *y_pos);
void ili9341_calibrate_scalar(ili9341_t *lcd,
    uint16_t min_x, uint16_t min_y, uint16_t max_x, uint16_t max_y);
void ili9341_calibrate_3point(ili9341_t *lcd,
    uint16_t scale_width, uint16_t scale_height,
    int32_t screen_a_x, int32_t screen_a_y,
    int32_t screen_b_x, int32_t screen_b_y,
    int32_t screen_c_x, int32_t screen_c_y,
    int32_t touch_a_x,  int32_t touch_a_y,
    int32_t touch_b_x,  int32_t touch_b_y,
    int32_t touch_c_x,  int32_t touch_c_y);

void ili9341_spi_tft_select(ili9341_t *lcd);
void ili9341_spi_tft_release(ili9341_t *lcd);
void ili9341_spi_touch_select(ili9341_t *lcd);
void ili9341_spi_touch_release(ili9341_t *lcd);
void ili9341_spi_slave_select(ili9341_t *lcd,
    ili9341_spi_slave_t spi_slave);
void ili9341_spi_slave_release(ili9341_t *lcd,
    ili9341_spi_slave_t spi_slave);

void ili9341_spi_write_command(ili9341_t *lcd,
    ili9341_spi_slave_t spi_slave, uint8_t command);
void ili9341_spi_write_data(ili9341_t *lcd,
    ili9341_spi_slave_t spi_slave, uint16_t data_sz, uint8_t data[]);
void ili9341_spi_write_data_read(ili9341_t *lcd,
    ili9341_spi_slave_t spi_slave,
    uint16_t data_sz, uint8_t tx_data[], uint8_t rx_data[]);
void ili9341_spi_write_command_data(ili9341_t *lcd,
    ili9341_spi_slave_t spi_slave, uint8_t command, uint16_t data_sz, uint8_t data[]);

#ifdef __cplusplus
}
#endif

#endif /* __ILI9341_H */
