#include "LED.h"

#define SEND_BIT(bit, offset) { \
	volatile int x; \
	if (bit) { \
		for (x = 0; x < 32 - offset; x++); \
		for (x = 0; x < 15 - offset; x++); \
	} else { \
		for (x = 0; x < 12 - offset; x++); \
		for (x = 0; x < 33 - offset; x++); \
	} \
}

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

void flash_image(const uint8_t *bitmap, size_t length) {
	size_t offset;

	for (offset = 0; offset < length; offset++) {
		const uint8_t *color = bitmap + offset * 3;

		uint8_t byte = color[0];

		SEND_BIT(byte & 0x80, 0);
		SEND_BIT(byte & 0x40, 0);
		SEND_BIT(byte & 0x20, 0);
		SEND_BIT(byte & 0x10, 0);
		SEND_BIT(byte & 0x08, 0);
		SEND_BIT(byte & 0x04, 0);
		SEND_BIT(byte & 0x02, 0);
		SEND_BIT(byte & 0x01, 0);

		byte = color[1];

		SEND_BIT(byte & 0x80, 0);
		SEND_BIT(byte & 0x40, 0);
		SEND_BIT(byte & 0x20, 0);
		SEND_BIT(byte & 0x10, 0);
		SEND_BIT(byte & 0x08, 0);
		SEND_BIT(byte & 0x04, 0);
		SEND_BIT(byte & 0x02, 0);
		SEND_BIT(byte & 0x01, 0);

		byte = color[2];

		SEND_BIT(byte & 0x80, 0);
		SEND_BIT(byte & 0x40, 0);
		SEND_BIT(byte & 0x20, 0);
		SEND_BIT(byte & 0x10, 0);
		SEND_BIT(byte & 0x08, 0);
		SEND_BIT(byte & 0x04, 0);
		SEND_BIT(byte & 0x02, 0);
		SEND_BIT(byte & 0x01, 0);
	}
}
