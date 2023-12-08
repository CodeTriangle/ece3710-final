#include <string.h>

#include "LED.h"

void make_bitmap(const uint8_t *image, uint8_t *bitmap) {
	size_t offset;
	uint8_t *color, *dst;

	for (offset = 0; offset < BMP_SIZE; offset++) {
		color = colors[image[offset]];
		dst = bitmap + offset * 3;
		dst[0] = color[0];
		dst[1] = color[1];
		dst[2] = color[2];
	}
}

void set_pixel(uint8_t *image, const uint8_t x, const uint8_t y, const uint8_t color) {
	uint8_t yoffset = x % 2 ? (15 - y) : y;
    uint8_t xoffset = (15 - x) * 16;
    uint8_t idx = xoffset + yoffset;

    image[idx] = color;
}

void clear_screen(uint8_t *image, uint8_t *bitmap) {
	memset(image, 0, BMP_SIZE);
	memset(bitmap, 0, BMP_SIZE * 3);
}
