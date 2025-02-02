#include <SDL2/SDL.h>
#include <iostream>
#include <bitset>
#include <iomanip>

#include "chip8.h"
#include "window.h"

int main(int argc, char** argv) {
	// init SDL
	Window window(64, 32, 10);

	// init chip-8
	Chip8 chip8;
	
	// read from file
	if (argc < 2) {
		std::cout << "error: input file expected \n";
		return -1;
	}

	// load program into rom
	chip8.load(argv[1]);
	bool exit = false;

	while (!exit) {
		exit = window.processInput(chip8.input);

		chip8.cycle();
		window.updateDisplay(chip8.display, 32);

		SDL_Delay(250);
	}

	return 0;
}