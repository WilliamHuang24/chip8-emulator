#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
    SDL_Window * window;
    SDL_Renderer * renderer;
    int size;

    public:
        Window(int width, int height, int pixelSize);
        ~Window();
        void updateDisplay(unsigned long long *display, int n);
        bool processInput(uint8_t* keys);

};

#endif