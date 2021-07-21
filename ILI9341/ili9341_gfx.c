/*
 * ili9341_gfx.c
 *
 *  Created on: Jan 17, 2020
 *      Author: andrew
 */

// ----------------------------------------------------------------- includes --

#include "ili9341_gfx.h"
#include "stdlib.h"
#include "string.h" // memset()

// ---------------------------------------------------------- private defines --

/* nothing */

// ----------------------------------------------------------- private macros --

/* nothing */

// ----------------------------------------------------------- private types --

/* nothing */

// ------------------------------------------------------- exported variables --

ili9341_color_t const ILI9341_BLACK        = (ili9341_color_t)0x0000;
ili9341_color_t const ILI9341_NAVY         = (ili9341_color_t)0x000F;
ili9341_color_t const ILI9341_DARKGREEN    = (ili9341_color_t)0x03E0;
ili9341_color_t const ILI9341_DARKCYAN     = (ili9341_color_t)0x03EF;
ili9341_color_t const ILI9341_MAROON       = (ili9341_color_t)0x7800;
ili9341_color_t const ILI9341_PURPLE       = (ili9341_color_t)0x780F;
ili9341_color_t const ILI9341_OLIVE        = (ili9341_color_t)0x7BE0;
ili9341_color_t const ILI9341_LIGHTGREY    = (ili9341_color_t)0xC618;
ili9341_color_t const ILI9341_DARKGREY     = (ili9341_color_t)0x7BEF;
ili9341_color_t const ILI9341_BLUE         = (ili9341_color_t)0x001F;
ili9341_color_t const ILI9341_GREEN        = (ili9341_color_t)0x07E0;
ili9341_color_t const ILI9341_CYAN         = (ili9341_color_t)0x07FF;
ili9341_color_t const ILI9341_RED          = (ili9341_color_t)0xF800;
ili9341_color_t const ILI9341_MAGENTA      = (ili9341_color_t)0xF81F;
ili9341_color_t const ILI9341_YELLOW       = (ili9341_color_t)0xFFE0;
ili9341_color_t const ILI9341_WHITE        = (ili9341_color_t)0xFFFF;
ili9341_color_t const ILI9341_ORANGE       = (ili9341_color_t)0xFD20;
ili9341_color_t const ILI9341_GREENYELLOW  = (ili9341_color_t)0xAFE5;
ili9341_color_t const ILI9341_PINK         = (ili9341_color_t)0xF81F;

// ------------------------------------------------------- private variables --

static uint16_t spi_tx_block[__SPI_TX_BLOCK_MAX__]; // default DMA TX buffer

// ------------------------------------------------------ function prototypes --

static ili9341_bool_t ili9341_clip_rect(ili9341_t *lcd,
    int16_t *x, int16_t *y, uint16_t *w, uint16_t *h);
static void ili9341_fill_quarter_circle(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y, int16_t r, uint8_t corners, int16_t delta);

// ------------------------------------------------------- exported functions --

ili9341_color_rgb_t ili9341_rgb_wheel(uint8_t *pos)
{
  ili9341_color_rgb_t rgb;
  uint8_t curr = *pos;
  *pos += 1;

  curr = 0xFF - curr;
  if (curr < 0x55) {
    rgb.red   = 0x03 * curr;
    rgb.green = 0xFF - curr * 0x03;
    rgb.blue  = 0x00;
  }
  else if (curr < 0xAA) {
    curr -= 0x55;
    rgb.red   = 0xFF - curr * 0x03;
    rgb.green = 0x00;
    rgb.blue  = 0x03 * curr;
  }
  else {
    curr -= 0xAA;
    rgb.red   = 0x00;
    rgb.green = 0x03 * curr;
    rgb.blue  = 0xFF - curr * 0x03;
  }
  return rgb;
}

ili9341_color_t ili9341_color_wheel(uint8_t *pos)
{
  ili9341_color_rgb_t rgb = ili9341_rgb_wheel(pos);
  return __ILI9341_COLOR565_RGB(rgb);
}

void ili9341_spi_tft_set_address_rect(ili9341_t *lcd,
    uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
  ili9341_spi_tft_select(lcd);

  // column address set
  ili9341_spi_write_command_data(lcd, issNONE,
      0x2A, 4, (uint8_t[]){ (x0 >> 8) & 0xFF, x0 & 0xFF,
                            (x1 >> 8) & 0xFF, x1 & 0xFF });

  // row address set
  ili9341_spi_write_command_data(lcd, issNONE,
      0x2B, 4, (uint8_t[]){ (y0 >> 8) & 0xFF, y0 & 0xFF,
                            (y1 >> 8) & 0xFF, y1 & 0xFF });

  // write to RAM
  ili9341_spi_write_command(lcd, issNONE, 0x2C);

  ili9341_spi_tft_release(lcd);
}

void ili9341_transmit_wait(ili9341_t *lcd)
{
  if (NULL == lcd)
    { return; }

  while (HAL_DMA_STATE_BUSY == HAL_DMA_GetState(lcd->spi_hal->hdmatx))
    { continue; }
}

void ili9341_transmit_color(ili9341_t *lcd, uint16_t size,
    uint16_t color[]/* already byte-swapped (LE) */, ili9341_bool_t wait)
{
  if ((NULL == lcd) || (0 == size) || (NULL == color))
    { return; }

  HAL_SPI_Transmit_DMA(lcd->spi_hal, (uint8_t *)color, size);

  if (ibOK(wait))
    { ili9341_transmit_wait(lcd); }
}

void ili9341_draw_pixel(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y)
{
  if (ibNOT(ili9341_clip_rect(lcd, &x, &y, NULL, NULL)))
    { return; }

  uint16_t color_le = __LEu16(&color);

  // select target region
  ili9341_spi_tft_set_address_rect(lcd, x, y, x + 1, y + 1);

  ili9341_spi_tft_select(lcd);

  HAL_GPIO_WritePin(lcd->data_command_port, lcd->data_command_pin, __GPIO_PIN_SET__);
  HAL_SPI_Transmit(lcd->spi_hal, (uint8_t *)&color_le, 2U, __SPI_MAX_DELAY__);

  ili9341_spi_tft_release(lcd);
}

void ili9341_draw_line(ili9341_t *lcd, ili9341_color_t color,
    int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;

  int16_t x, y;
  int16_t err;
  int16_t step;

  if (0 == dx) {
    // vertical line
    if (0 == dy)
      { return; } // distance = 0, no line to draw
    ili9341_fill_rect(lcd, color, x0, y0, 1, abs(dy));
    return;
  }
  else if (0 == dy) {
    // horizontal line
    if (0 == dx)
      { return; } // distance = 0, no line to draw
    ili9341_fill_rect(lcd, color, x0, y0, abs(dx), 1);
    return;
  }

  ili9341_bool_t is_steep = abs(dy) > abs(dx);
  if (is_steep) {
    __SWAP(int16_t, x0, y0);
    __SWAP(int16_t, x1, y1);
  }

  if (x0 > x1) {
    __SWAP(int16_t, x0, x1);
    __SWAP(int16_t, y0, y1);
  }

  dx = x1 - x0;
  dy = abs(y1 - y0);
  err = dx >> 1;

  if (y0 < y1)
    { step = 1; }
  else
    { step = -1; }

  while (x0 <= x1) {

    if (is_steep)
      { x = y0; y = x0; }
    else
      { x = x0; y = y0; }

    // continue algorithm even if current pixel is outside of screen
    // bounds, so that the line is drawn at correct position once
    // it actually enters screen bounds (if ever).
    if ( (x >= 0) && (x <= lcd->screen_size.width) &&
         (y >= 0) && (y <= lcd->screen_size.height) ) {
      ili9341_draw_pixel(lcd, color, x, y);
    }

    err -= dy;
    if (err < 0) {
      y0 += step;
      err += dx;
    }

    ++x0;
  }
}

void ili9341_draw_rect(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y, uint16_t w, uint16_t h)
{
  ili9341_draw_line(lcd, color,     x,     y,   x+w,     y );
  ili9341_draw_line(lcd, color,     x, y+h-1,   x+w, y+h-1 );
  ili9341_draw_line(lcd, color,     x,     y,     x,   y+h );
  ili9341_draw_line(lcd, color, x+w-1,     y, x+w-1,   y+h );
}

void ili9341_fill_rect(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y, uint16_t w, uint16_t h)
{
  // verify we have something within screen dimensions to be drawn
  if (ibNOT(ili9341_clip_rect(lcd, &x, &y, &w, &h)))
    { return; }

  uint32_t num_pixels = w * h;
  uint32_t rect_wc    = num_pixels;

  uint32_t block_wc = rect_wc;
  if (block_wc > __SPI_TX_BLOCK_MAX__)
    { block_wc = __SPI_TX_BLOCK_MAX__; }

  // fill entire block with ordered color data
  uint16_t color_le = __LEu16(&color);
  for (uint16_t i = 0; i < block_wc; ++i)
    { spi_tx_block[i] = color_le; }

  // select target region
  ili9341_spi_tft_set_address_rect(lcd, x, y, (x + w - 1), (y + h - 1));
  ili9341_spi_tft_select(lcd);

  HAL_GPIO_WritePin(lcd->data_command_port, lcd->data_command_pin, __GPIO_PIN_SET__);

  // repeatedly send MIN(remaining-words, block-words) words of color data until
  // all rect words have been sent.
  uint32_t curr_wc;
  while (rect_wc > 0) {
    curr_wc = rect_wc;
    if (curr_wc > block_wc)
      { curr_wc = block_wc; }
    ili9341_transmit_color(lcd, curr_wc * 2/*16-bit words*/, spi_tx_block, ibYes);
    rect_wc -= curr_wc;
  }

  ili9341_spi_tft_release(lcd);
}

void ili9341_draw_circle(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y, int16_t r)
{
  int16_t f = 1 - r;
  int16_t fx = 1;
  int16_t fy = -2 * r;
  int16_t ix = 0;
  int16_t iy = r;

  ili9341_draw_pixel(lcd, color, x, y + r);
  ili9341_draw_pixel(lcd, color, x, y - r);
  ili9341_draw_pixel(lcd, color, x + r, y);
  ili9341_draw_pixel(lcd, color, x - r, y);

  while (ix < iy) {

    if (f >= 0) {
      iy--;
      fy += 2;
      f += fy;
    }

    ix++;
    fx += 2;
    f += fx;

    ili9341_draw_pixel(lcd, color, x + ix, y + iy);
    ili9341_draw_pixel(lcd, color, x - ix, y + iy);
    ili9341_draw_pixel(lcd, color, x + ix, y - iy);
    ili9341_draw_pixel(lcd, color, x - ix, y - iy);
    ili9341_draw_pixel(lcd, color, x + iy, y + ix);
    ili9341_draw_pixel(lcd, color, x - iy, y + ix);
    ili9341_draw_pixel(lcd, color, x + iy, y - ix);
    ili9341_draw_pixel(lcd, color, x - iy, y - ix);
  }
}

void ili9341_fill_circle(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y, int16_t r)
{
  ili9341_draw_line(lcd, color, x, y - r, x, (y - r) + (2 * r) + 1);
  ili9341_fill_quarter_circle(lcd, color, x, y, r, 3, 0);
}

void ili9341_fill_screen(ili9341_t *lcd, ili9341_color_t color)
{
  ili9341_fill_rect(lcd, color,
      0, 0, lcd->screen_size.width, lcd->screen_size.height);
}

void ili9341_draw_bitmap_1b(ili9341_t *lcd,
    ili9341_color_t fg_color, ili9341_color_t bg_color,
    int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t *bmp)
{
  if ((NULL == lcd) || (NULL == bmp))
    { return; }

  int16_t  _x = x, _y = y;
  uint16_t _w = w, _h = h;

  if (ibNOT(ili9341_clip_rect(lcd, &_x, &_y, &_w, &_h)))
    { return; }

  int16_t byteWidth = (w + 7) / 8;
  uint8_t byte = 0;

  uint16_t fg_le = __LEu16(&(fg_color));
  uint16_t bg_le = __LEu16(&(bg_color));

  // select target region
  ili9341_spi_tft_set_address_rect(lcd, x, y, w, h);
  ili9341_spi_tft_select(lcd);

  HAL_GPIO_WritePin(lcd->data_command_port, lcd->data_command_pin, __GPIO_PIN_SET__);

  for (int16_t j = 0; j < h; ++j, ++y) {
    for (int16_t i = 0; i < w; ++i) {

      if (i & 7)
        { byte <<= 1; }
      else
        { byte = bmp[j * byteWidth + i / 8]; }

      if (byte & 0x80)
        { spi_tx_block[((j&1) * w) + i] = fg_le; }
      else
        { spi_tx_block[((j&1) * w) + i] = bg_le; }
    }

    ili9341_transmit_wait(lcd);
    ili9341_transmit_color(lcd, w * 2, &(spi_tx_block[(j&1) * w]), ibNo);
  }

  ili9341_spi_tft_release(lcd);
  ili9341_transmit_wait(lcd);
}

void ili9341_draw_char(ili9341_t *lcd, ili9341_text_attr_t attr, char ch)
{
  // verify we have something within screen dimensions to be drawn
  int16_t  _x = attr.origin_x;
  int16_t  _y = attr.origin_y;
  uint16_t _w = attr.font->width;
  uint16_t _h = attr.font->height;
  if (ibNOT(ili9341_clip_rect(lcd, &_x, &_y, &_w, &_h)))
    { return; }

  // 16-bit color, so need 2 bytes for each pixel being filled
  uint32_t num_pixels = attr.font->width * attr.font->height;
  uint32_t rect_wc    = num_pixels;

  uint16_t fg_le = __LEu16(&(attr.fg_color));
  uint16_t bg_le = __LEu16(&(attr.bg_color));

  uint32_t block_wc = rect_wc;
  if (block_wc > __SPI_TX_BLOCK_MAX__)
    { block_wc = __SPI_TX_BLOCK_MAX__; }

  // initialize the buffer with glyph from selected font
  uint8_t ch_index = glyph_index(ch);
  for (uint32_t yi = 0; yi < attr.font->height; ++yi) {
    uint32_t gl = (uint32_t)attr.font->glyph[ch_index * attr.font->height + yi];
    for (uint32_t xi = 0; xi < attr.font->width; ++xi) {
      if ((gl << xi) & 0x8000)
        { spi_tx_block[yi * attr.font->width + xi] = fg_le; }
      else
        { spi_tx_block[yi * attr.font->width + xi] = bg_le; }
    }
  }

  // select target region
  ili9341_spi_tft_set_address_rect(lcd,
      attr.origin_x, attr.origin_y,
      attr.origin_x + attr.font->width - 1, attr.origin_y + attr.font->height - 1);
  ili9341_spi_tft_select(lcd);

  HAL_GPIO_WritePin(lcd->data_command_port, lcd->data_command_pin, __GPIO_PIN_SET__);

  // repeatedly send MIN(remaining-words, block-words) words of color data until
  // all rect words have been sent.
  uint32_t curr_wc;
  while (rect_wc > 0) {
    curr_wc = rect_wc;
    if (curr_wc > block_wc)
      { curr_wc = block_wc; }
    ili9341_transmit_color(lcd, curr_wc * 2/*16-bit words*/, spi_tx_block, ibYes);
    rect_wc -= curr_wc;
  }

  ili9341_spi_tft_release(lcd);
}

void ili9341_draw_string(ili9341_t *lcd, ili9341_text_attr_t attr, char str[])
{
  int16_t curr_x = attr.origin_x;
  int16_t curr_y = attr.origin_y;
  int16_t start_x = attr.origin_x;

  while ('\0' != *str) {
    if('\r' == *str)
    {
      curr_x = start_x;
    }
    else if('\n' == *str)
    {
      curr_y += attr.font->height;
      curr_x = start_x;
    }
    else
    {
      if ( (curr_x > lcd->screen_size.width) ||
          (curr_y > lcd->screen_size.height) )
        { break; }

      attr.origin_x = curr_x;
      attr.origin_y = curr_y;

      ili9341_draw_char(lcd, attr, *str);

      curr_x += attr.font->width;
    }
    ++str;
  }
}

// ------------------------------------------------------- private functions --

static ili9341_bool_t ili9341_clip_rect(ili9341_t *lcd,
    int16_t *x, int16_t *y, uint16_t *w, uint16_t *h)
{
  // must have an origin to do anything
  if ((NULL == x) || (NULL == y))
    { return ibFalse; }

  //  1. rect origin beyond screen dimensions, nothing to draw
  if ((*x >= lcd->screen_size.width) || (*y >= lcd->screen_size.height))
    { return ibFalse; }

  //  2. rect width or height is 0, nothing to draw
  if ((NULL != w) && (NULL != h)) {
    if ((0U == *w) || (0U == *h))
      { return ibFalse; }
  }

  // 3. rect origin has negative component, adjust origin and dimensions
  if (*x < 0) {
    if (NULL != w)
      { *w -= *x; }
    *x = 0;
  }
  if (*y < 0) {
    if (NULL != h)
      { *h -= *y; }
    *y = 0;
  }

  if ((NULL != w) && (NULL != h)) {

    //  4. rect width beyond screen width, reduce rect width
    if ((*x + *w - 1) >= lcd->screen_size.width)
      { *w = lcd->screen_size.width - *x; }

    //  5. rect height beyond screen height, reduce rect height
    if ((*y + *h - 1) >= lcd->screen_size.height)
      { *h = lcd->screen_size.height - *y; }

    return (*w > 0U) && (*h > 0U);
  }

  return ibTrue;
}

static void ili9341_fill_quarter_circle(ili9341_t *lcd, ili9341_color_t color,
    int16_t x, int16_t y, int16_t r, uint8_t corners, int16_t delta)
{
  int16_t f = 1 - r;
  int16_t fx = 1;
  int16_t fy = -2 * r;
  int16_t ix = 0;
  int16_t iy = r;
  int16_t px = ix;
  int16_t py = iy;
  int16_t tx;
  int16_t ty;

  delta += 1;

  while (ix < iy) {

    if (f >= 0) {
      iy--;
      fy += 2;
      f += fy;
    }

    ix++;
    fx += 2;
    f += fx;


    if (ix < (iy + 1)) {
      if (corners & 1) {
        tx = x + ix;
        ty = y - iy;
        ili9341_draw_line(lcd, color, tx, ty, tx, ty + 2 * iy + delta);
      }
      if (corners & 2) {
        tx = x - ix;
        ty = y - iy;
        ili9341_draw_line(lcd, color, tx, ty, tx, ty + 2 * iy + delta);
      }
    }

    if (iy != py) {
      if (corners & 1) {
        tx = x + py;
        ty = y - px;
        ili9341_draw_line(lcd, color, tx, ty, tx, ty + 2 * px + delta);
      }
      if (corners & 2) {
        tx = x - py;
        ty = y - px;
        ili9341_draw_line(lcd, color, tx, ty, tx, ty + 2 * px + delta);
      }
      py = iy;
    }

    px = ix;
  }
}

