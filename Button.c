#include "Button.h"

uint8_t get_button_pressed(void) {
		uint32_t idr = GPIOB->IDR;
		for (int i = 0; i < 32; i++);
		uint32_t idr_new = GPIOB->IDR;
		if (idr != idr_new) {
			return 0;
		}
		uint8_t result = 0;
	
		if ((idr & 0x007Eu) == 0x007Eu) {
			return 0;
		}
		
		for (uint8_t i = 1; i <= 6; i++) {
			if (!(idr & (0x1 << i))) {
				result = i;
			}
		}
		
		while ((GPIOB->IDR & 0x007Eu) != 0x007Eu);
		
		return result;
}
