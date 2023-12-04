#include "LED.h"

void make_bitmap(void) {
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

void set_pixel(const uint8_t x, const uint8_t y, const uint8_t color) {
    uint8_t yoffset = x % 16 ? (16 - y) : y;
    uint8_t xoffset = x * 16;
    uint8_t idx = xoffset + yoffset;

    image[idx] = color;
}
