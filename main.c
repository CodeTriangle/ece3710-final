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

	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			set_pixel(IMAGE, (uint8_t) i, (uint8_t) j, (i + j) % 8);
		}
	}
	
	make_bitmap(IMAGE, BITMAP);
	
	flash_image(BITMAP, BMP_SIZE*3);
	
	while(1) {
//		uint8_t button = get_button_pressed();
//		if (button) {
//			// mastermind stuff
//			make_bitmap();
//			flash_image(bitmap, BMP_SIZE);
//		}
	}
}
