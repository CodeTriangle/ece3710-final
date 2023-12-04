#include "stm32l476xx.h"
#include "LED.h"
#include "Button.h"

int main(void) {
	RCC->CR |= RCC_CR_MSIRGSEL;
	RCC->CR = (RCC->CR & ~RCC_CR_MSIRANGE) | RCC_CR_MSIRANGE_10;
	while (!(RCC->CR & RCC_CR_MSIRDY));
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER = (GPIOB->MODER & 0xFFFFC000u) | 0x00000001u;
	GPIOB->PUPDR = (GPIOB->PUPDR & 0xFFFFC000u) | 0x00001554u;

	for (size_t i = 0; i < BMP_SIZE; i++) {
		bitmap[3*i] = (uint8_t)0x20;
		bitmap[3*i+1] = (uint8_t)0x18;
		bitmap[3*i+2] = (uint8_t)0xFC;
	}
	
	flash_image(bitmap, BMP_SIZE * 3);
	
	while(1) {
//		uint8_t button = get_button_pressed();
//		if (button) {
//			// mastermind stuff
//			make_bitmap();
//			flash_image(bitmap, BMP_SIZE);
//		}
	}
}
