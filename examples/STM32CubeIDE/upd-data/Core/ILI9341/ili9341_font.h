/*
 * ili9341_font.h
 *
 *  Created on: Nov 28, 2019
 *      Author: andrew
 */

#ifndef __ILI9341_FONT_H
#define __ILI9341_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------- includes --

#include <stdint.h>

// ------------------------------------------------------------------ defines --

/* nothing */

// ------------------------------------------------------------------- macros --

/* nothing */

// ----------------------------------------------------------- exported types --

typedef struct
{
    const uint8_t width;
    const uint8_t height;
    const uint16_t glyph[];
}
ili9341_font_t;

// ------------------------------------------------------- exported variables --

extern ili9341_font_t const ili9341_font_7x10;
extern ili9341_font_t const ili9341_font_11x18;
extern ili9341_font_t const ili9341_font_16x26;

// ------------------------------------------------------- exported functions --

uint8_t glyph_index(unsigned char glyph);

#ifdef __cplusplus
}
#endif

#endif /* __ILI9341_FONT_H */