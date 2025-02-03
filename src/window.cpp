#include <SDL2/SDL.h>
#include "window.h"
#include <iostream>

Window::Window(int width, int height, int pixelSize) {
    size = pixelSize;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width * size, height * size, 0, &window, &renderer);
    SDL_RenderClear(renderer);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Window::updateDisplay(unsigned long long *display, int n) {
    SDL_Rect r;

    r.h = size;
    r.w = size;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < 64; col++) {
            if ((display[row] >> (64 - col)) & 1 != 0) {
                r.x = col * size;
                r.y = row * size;

                SDL_RenderFillRect(renderer, &r);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

bool Window::processInput(uint8_t* keys) {
    SDL_Event event;
    bool exit = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit = true;
            break;

        } else if (event.type == SDL_KEYDOWN) {
            std::cout << "key pressed";

			switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    exit = true;
                    break;

				case SDLK_1:
                    keys[0] = 1;
					break;

				case SDLK_2:
                    keys[1] = 1;
					break;
				
				case SDLK_3:
                    keys[2] = 1;
					break;

				case SDLK_4:
                    keys[3] = 1;
					break;

				case SDLK_q:
                    keys[4] = 1;
					break;

				case SDLK_w:
                    keys[5] = 1;
					break;
				
				case SDLK_e:
                    keys[6] = 1;
					break;

				case SDLK_r:
                    keys[7] = 1;
					break;

				case SDLK_a:
                    keys[8] = 1;
					break;

				case SDLK_s:
                    keys[9] = 1;
					break;
				
				case SDLK_d:
                    keys[10] = 1;
					break;

				case SDLK_f:
                    keys[11] = 1;
					break;

				case SDLK_z:
                    keys[12] = 1;
					break;

				case SDLK_x:
                    keys[13] = 1;
					break;

				case SDLK_c:
                    keys[14] = 1;
					break;
				
				case SDLK_v:
                    keys[15] = 1;
					break;

			}

		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    exit = true;
                    break;

				case SDLK_1:
                    keys[0] = 0;
					break;

				case SDLK_2:
                    keys[1] = 0;
					break;
				
				case SDLK_3:
                    keys[2] = 0;
					break;

				case SDLK_4:
                    keys[3] = 0;
					break;

				case SDLK_q:
                    keys[4] = 0;
					break;

				case SDLK_w:
                    keys[5] = 0;
					break;
				
				case SDLK_e:
                    keys[6] = 0;
					break;

				case SDLK_r:
                    keys[7] = 0;
					break;

				case SDLK_a:
                    keys[8] = 0;
					break;

				case SDLK_s:
                    keys[9] = 0;
					break;
				
				case SDLK_d:
                    keys[10] = 0;
					break;

				case SDLK_f:
                    keys[11] = 0;
					break;

				case SDLK_z:
                    keys[12] = 0;
					break;

				case SDLK_x:
                    keys[13] = 0;
					break;

				case SDLK_c:
                    keys[14] = 0;
					break;
				
				case SDLK_v:
                    keys[15] = 0;
					break;
			}
		}
	}

    return exit;
}