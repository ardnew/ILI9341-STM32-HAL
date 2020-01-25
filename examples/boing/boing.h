/*
 * boing.h
 *
 *  Created on: Jan 21, 2020
 *      Author: andrew
 */

#ifndef SRC_BOING_H_
#define SRC_BOING_H_

// --

#include <stdint.h>

#include "ili9341_gfx.h"
#include "ili9341.h"

// --

#define __BOING_PLOT_WIDTH__  320
#define __BOING_PLOT_HEIGHT__ 240
#define __BOING_PLOT_BPP__      1
extern const uint8_t BOING_PLOT[__BOING_PLOT_HEIGHT__][__BOING_PLOT_WIDTH__ / (8U / __BOING_PLOT_BPP__)];

#define __BOING_BALL_WIDTH__  136
#define __BOING_BALL_HEIGHT__ 100
#define __BOING_BALL_BPP__      4
extern const uint8_t BOING_BALL[__BOING_BALL_HEIGHT__][__BOING_BALL_WIDTH__ / (8U / __BOING_BALL_BPP__)];

#define __BOING_BALL_PANEL_NB__ 16
#define __BOING_BALL_FRAME_NB__ (__BOING_BALL_PANEL_NB__ - 2)
#define __BOING_BALL_FRAME_HF__ (__BOING_BALL_FRAME_NB__ / 2)

typedef struct
{
  float x;
  float y;
}
boing_pointf_t;

typedef struct
{
  int16_t x;
  int16_t y;
}
boing_point_t;

typedef struct
{
  float x;
  float y;
}
boing_velocity_t;

typedef struct
{
  boing_pointf_t pos;
  boing_pointf_t pre;
  boing_velocity_t vel;
  int16_t frame;

  ili9341_color_t color[__BOING_BALL_PANEL_NB__];
  uint16_t spi_tx[2][__BOING_BALL_WIDTH__ * 2];
}
boing_ball_t;

extern ili9341_color_t const BOING_COLOR_PLOT_COLOR;
extern ili9341_color_t const BOING_COLOR_PLOT_SHADOW;
extern ili9341_color_t const BOING_COLOR_BG_COLOR;
extern ili9341_color_t const BOING_COLOR_BG_SHADOW;
extern ili9341_color_t const BOING_COLOR_GRID_COLOR;
extern ili9341_color_t const BOING_COLOR_GRID_SHADOW;
extern ili9341_color_t const BOING_COLOR_BALL_P1;
extern ili9341_color_t const BOING_COLOR_BALL_P2;

extern boing_pointf_t const BOING_EDGE_MIN;
extern boing_pointf_t const BOING_EDGE_MAX;

extern float const BOING_ROTATION_FX;
extern float const BOING_VELOCITY_DY;  // per-frame change in Y velocity
extern float const BOING_BOUNCE_VEL_Y; // Y velocity on ball bounce

void boing_init(boing_ball_t *ball);
void boing(ili9341_t *lcd, boing_ball_t *ball);

// --

#endif /* SRC_BOING_H_ */
