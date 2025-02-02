#include <SDL2/SDL.h>
#include <iostream>

#include "chip8.h"

int main(int argc, char** argv) {
	// init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Event event;

	SDL_CreateWindowAndRenderer(640, 320, 0, &window, &renderer);
	SDL_RenderClear(renderer);

	// init chip-8
	Chip8 *chip8 = new Chip8();
	
	// read from file
	if (argc < 2) {
		std::cout << "error: input file expected";
		return -1;
	}

	// load program into rom
	chip8->load(argv[1]);

	// main event loop
	while (true) {
		// draw
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

		for (int i = 0; i < 16; i++) {
			for (int j = 0; i < 32; j++) {
				if (chip8->display[i] & (1 << j) > 0) {
					SDL_Rect r = {i * 10, j * 10, i * 10 + 10, j * 10 + 10};
					SDL_RenderDrawRect(renderer, &r);
				}
			}
		}

		chip8->cycle();

		SDL_Delay(5000);
		break;
	}




	// while (true) {


	// 	SDL_Delay(16);
	// }


	// // main event loop
	// while (SDL_PollEvent(&event)) {
	// 	if (event.type == SDL_KEYDOWN) {
	// 		switch (event.key.keysym.sym) {
	// 			case SDLK_1:
	// 				break;

	// 			case SDLK_2:
	// 				break;
				
	// 			case SDLK_3:
	// 				break;

	// 			case SDLK_4:
	// 				break;

	// 			case SDLK_q:
	// 				break;

	// 			case SDLK_w:
	// 				break;
				
	// 			case SDLK_e:
	// 				break;

	// 			case SDLK_r:
	// 				break;

	// 			case SDLK_a:
	// 				break;

	// 			case SDLK_s:
	// 				break;
				
	// 			case SDLK_d:
	// 				break;

	// 			case SDLK_f:
	// 				break;

	// 			case SDLK_z:
	// 				break;

	// 			case SDLK_x:
	// 				break;

	// 			case SDLK_c:
	// 				break;
				
	// 			case SDLK_v:
	// 				break;

	// 		}
	// 	}
	// }

	// cleanup
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
