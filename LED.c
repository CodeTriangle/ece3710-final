#include "LED.h"

void make_bitmap(const uint8_t *image, uint8_t *bitmap, size_t length) {
	size_t offset;
	uint8_t *color, *dst;

	for (offset = 0; offset < length; offset++) {
		color = colors[image[offset]];
		dst = bitmap + offset * 3;
		dst[0] = color[0];
		dst[1] = color[1];
		dst[2] = color[2];
	}
}
