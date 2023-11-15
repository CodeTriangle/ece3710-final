#ifndef _LED_H
#define _LED_H
#include <stddef.h>

#include "stm32l476xx.h"

#define BLACK  0
#define WHITE  1
#define RED    2
#define GREEN  3
#define BLUE   4
#define YELLOW 5

static uint8_t colors[8][3] = {
	//            GRN   RED   BLU
	[BLACK]  = { 0x00, 0x00, 0x00 },
	[WHITE]  = { 0xFF, 0xFF, 0xFF },
	[RED]    = { 0x00, 0xFF, 0x00 },
	[GREEN]  = { 0xFF, 0x00, 0x00 },
	[BLUE]   = { 0x00, 0x00, 0xFF },
	[YELLOW] = { 0xFF, 0xFF, 0x00 },
};

void flash_image(const uint8_t *bitmap, size_t length);

#endif // _LED_H
