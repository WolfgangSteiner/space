#include "window.h"

window_t* window_create(char* title, size_t width, size_t height)
{
    window_t* win = calloc(1, sizeof(window_t));
    win->sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        0);

    win->renderer = SDL_CreateRenderer(
        win->sdl_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    return win;

}

void window_destroy(window_t* win)
{
    SDL_DestroyWindow(win->sdl_window);
    free(win);
}


