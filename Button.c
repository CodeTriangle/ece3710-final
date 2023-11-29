#include "Button.h"

uint8_t get_button_pressed(void) {
		uint32_t idr = GPIOB->IDR;
		if ((idr & 0x007Eu) == 0x007Eu) {
			return 0;
		}
		
		for (uint8_t i = 1; i <= 6; i++) {
			if (!(idr & 0x1 << i)) {
				return 1;
			}
		}
		
		return 0;
}
