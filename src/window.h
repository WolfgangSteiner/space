#ifndef WINDOW_H_
#define WINDOW_H_
#include "SDL2/SDL.h"
#include "basetypes.h"


typedef struct {
    SDL_Window* sdl_window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} window_t;


window_t* window_create(char* title, size_t width, size_t height);
void window_destroy(window_t* win);


#endif
