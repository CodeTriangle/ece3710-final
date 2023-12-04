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

static uint8_t image[BMP_SIZE] = {0};

static uint8_t bitmap[BMP_SIZE * 3] = {0};

static uint8_t colors[8][3] = {
	//            GRN   RED   BLU
	[BLACK]  = { 0x00, 0x00, 0x00 },
	[WHITE]  = { 0xFF, 0xFF, 0xFF },
	[RED]    = { 0x00, 0xFF, 0x00 },
	[GREEN]  = { 0xFF, 0x00, 0x00 },
	[BLUE]   = { 0x00, 0x00, 0xFF },
	[YELLOW] = { 0xFF, 0xFF, 0x00 },
	[PURPLE] = { 0x00, 0xFF, 0x7F },
	[ORANGE] = { 0x7F, 0xFF, 0x00 },
};

void make_bitmap(void);

extern void flash_image(const uint8_t *bitmap, size_t length);

void set_pixel(const uint8_t x, const uint8_t y, const uint8_t color);

#endif // _LED_H
