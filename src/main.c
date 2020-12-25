#include <stdio.h>
#include "basetypes.h"
#include "SDL2/SDL.h"


typedef struct {
    SDL_Window* sdl_window;
} window_t;


window_t* window_create(char* title)
{
    window_t* win = calloc(1, sizeof(window_t));
    win->sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_RESIZABLE);
    return win;
}

void window_destroy(window_t* win)
{
    SDL_DestroyWindow(win->sdl_window);
    free(win);
}


typedef struct {
    bool is_running;
} game_state_t;


game_state_t* game_state_init()
{
    game_state_t* game_state = calloc(1, sizeof(game_state_t));
    game_state->is_running = true;
    return game_state;
}


int main()
{   
    printf("SPACE!\n");
    SDL_Init(SDL_INIT_VIDEO);

    game_state_t* game_state = game_state_init();
    window_t* win = window_create("test");
    SDL_Event event;

    while (game_state->is_running)
    {
        while (SDL_PollEvent(&event))
        {   
           if (event.type == SDL_QUIT)
           {
              game_state->is_running = false;
           } 
        }
    }

    window_destroy(win);
    SDL_Quit();

}
