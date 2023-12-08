/*********************************
Pseudocode
Game logic
**********************************

loop 1
	random number generator 1-6
	end loop when array = 4

loop line number starting at 1
	loop 2 array
		input color from input button
		end loop when array = 4

	loop 3
		check array (compare to initial numbers)
		add 1 if color is a match
		end loop after array = 4

	use values from loop 3
		display number of leds
end loop



*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LED.h"
#include "Button.h"
#include "game.h"

//int generate_random_number() {
//	// Generate a random number between 1 and 6
//	return (rand() % 6) + 1;
//}

#define LINES 16

static uint8_t IMAGE[BMP_SIZE] = {0};

static uint8_t BITMAP[BMP_SIZE * 3] = {0};

void mastermind() {
	while(1) {
		mastermind_once();
		while (!get_button_pressed());
		clear_screen(IMAGE, BITMAP);
	}
}
	
void mastermind_once() {
	flash_image(BITMAP, BMP_SIZE * 3);
	
	uint8_t secret[4] = {0}, guesses[16][4] = {0}, results[16][4] = {0};
	//loop 1 from pseudocode
	for (int i = 0; i < 4; i++) {
		secret[i] = (uint8_t) rand() % 6 + 1;
//		set_pixel(IMAGE, 0, i, secret[i]);
	}
	
//	make_bitmap(IMAGE, BITMAP);
//	flash_image(BITMAP, BMP_SIZE * 3);

	//loop 2 from pseudocode
	for (uint8_t line = 0; line < LINES; line++) {		//line input
		for (uint8_t button = 0; button < 4; button++) {	//Array input to line
			
			while (1) {
				uint8_t color = get_button_pressed();
				
				if (color) {
					guesses[line][button] = color;
					set_pixel(IMAGE, 3 + button, line, color);
					make_bitmap(IMAGE, BITMAP);
					flash_image(BITMAP, BMP_SIZE * 3);
					break;
				}
			}
		}
		
		int white_amt = 0, red_amt = 0;
		uint8_t guess_mask = 0, used_mask = 0;
		
		// white loop
		for (uint8_t button = 0; button < 4; button++) {
			if (secret[button] == guesses[line][button]) {
				white_amt++;
				guess_mask |= 1 << button;
				used_mask |= 1 << button;
			}
		}
		
		// red loop
		for (uint8_t button = 0; button < 4; button++) {
			for (uint8_t compare = 0; compare < 4; compare++) {
				if (guess_mask & (1 << button)) {
					break;
				}
				
				if (button == compare) {
					continue;
				}
				
				if (!(used_mask & (1 << compare)) && secret[compare] == guesses[line][button]) {
					red_amt++;
					used_mask |= 1 << compare;
					break;
				}
			}
		}
		
		int won = white_amt == 4;
		int lost = line == 15 && !won;
		
		for (uint8_t display = 0; display < 4; display++) {
			if (white_amt > 0) {
				results[line][display] = WHITE;			//display white in guesses section if correct number is same position
				set_pixel(IMAGE, display + 9, line, WHITE);
				white_amt--;
				continue;
			} else if (red_amt > 0) {
				results[line][display] = RED;			//display red in guesses section if number is correct on led board
				set_pixel(IMAGE, display + 9, line, RED);
				red_amt--;
				continue;
			}
		}

		if (won || lost) {
			uint8_t color = won ? GREEN : RED;
			for (uint8_t row = 0; row < 16; row++) {
				for (uint8_t col = 0; col < 2; col++) {
					set_pixel(IMAGE, col, row, color);
					set_pixel(IMAGE, 15 - col, row, color);
				}
			}
		}
			
		make_bitmap(IMAGE, BITMAP);
		flash_image(BITMAP, BMP_SIZE * 3);
		
		if (won || lost) {
			return;
		}
	}
}
