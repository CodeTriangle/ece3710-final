#ifndef _LED_H
#define _LED_H
#include <stddef.h>

#include "stm32l476xx.h"

#define BMP_SIZE 256

#define BLACK  0
#define RED    1
#define YELLOW 2
#define BLUE   3
#define GREEN  4
#define PURPLE 5
#define ORANGE 6
#define WHITE  7

static uint8_t colors[8][3] = {
	//            GRN   RED   BLU
	[BLACK]  = { 0x00, 0x00, 0x00 },
	[WHITE]  = { 0x10, 0x10, 0x10 },
	[RED]    = { 0x00, 0x20, 0x00 },
	[GREEN]  = { 0x2A, 0x00, 0x03 },
	[BLUE]   = { 0x0A, 0x00, 0x2A },
	[YELLOW] = { 0x25, 0x2A, 0x00 },
	[PURPLE] = { 0x00, 0x15, 0x20 },
	[ORANGE] = { 0x08, 0x35, 0x00 },
};

void make_bitmap(const uint8_t *image, uint8_t *bitmap);

void set_pixel(uint8_t *image, const uint8_t x, const uint8_t y, const uint8_t color);

void clear_screen(uint8_t *image, uint8_t *bitmap);

extern void flash_image(const uint8_t *bitmap, size_t length);

#endif // _LED_H
