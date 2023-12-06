#include "stm32l476xx.h"
#include "LED.h"
#include "Button.h"

static uint8_t IMAGE[BMP_SIZE] = {0};

static uint8_t BITMAP[BMP_SIZE * 3] = {0};

int main(void) {
	RCC->CR |= RCC_CR_MSIRGSEL;
	RCC->CR = (RCC->CR & ~RCC_CR_MSIRANGE) | RCC_CR_MSIRANGE_10;
	while (!(RCC->CR & RCC_CR_MSIRDY));
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER = (GPIOB->MODER & 0xFFFFC000u) | 0x00000001u;
	GPIOB->PUPDR = (GPIOB->PUPDR & 0xFFFFC000u) | 0x00001554u;
	
	flash_image(BITMAP, BMP_SIZE*3);
	uint8_t x = 0, y = 0;
	while(1) {
		uint8_t button = get_button_pressed();
		
		if (button) {
			set_pixel(IMAGE, x, y, button);
			x++;
			if (x == 16) {
				x = 0;
				y++;
			}
			if (y == 16) {
				y = 0;
			}
			// mastermind stuff
			make_bitmap(IMAGE, BITMAP);
			flash_image(BITMAP, BMP_SIZE*3);
		}
	}
}
