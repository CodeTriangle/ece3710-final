# Mastermind

This project implements a digital version classic 2-player board game [Mastermind](https://en.wikipedia.org/wiki/Mastermind_(board_game)). It requires:
* The STM32L476RG microcontroller
* a 16x16 pixel WS2812B LED array
* six push buttons (as currently written, the code assumes they will be red, yellow, green, blue, orange, and purple, in that order)

The project is a direct copy of the Keil uVision project (the IDE and build system used for the class). As such, the majority of the files here were created by Keil.

Notable files I authored:
* `main.c`: Startup procedure that creates the game context.
* `asm_procs.s`: An optimized assembly procedure to print to the board within the very strict time limits imposed by the LED array.
* `LED.c`: A low-level graphics API for the LED array.
* `Button.c`: Functions to get input from the buttons.

Notable files authored by my partner:
* `game.c`: Game logic for Mastermind.

All other files are generated or were not made specifically for this project.
