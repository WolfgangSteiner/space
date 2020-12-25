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
    window_t* window;
} game_state_t;


game_state_t* game_state_init()
{
    game_state_t* game_state = calloc(1, sizeof(game_state_t));
    game_state->is_running = true;
    SDL_Init(SDL_INIT_VIDEO);
    game_state->window = window_create("SPACE!");
    return game_state;
}

void game_state_destroy(game_state_t* game_state)
{
    window_destroy(game_state->window);
    SDL_Quit();
}


void game_process_events(game_state_t* game_state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {   
       if (event.type == SDL_QUIT)
       {
          game_state->is_running = false;
       } 
       else if (event.type == SDL_KEYDOWN)
       {
           if (event.key.keysym.sym == SDLK_q)
           {
               game_state->is_running = false;
           }
       }
    }
}


int main()
{   
    printf("SPACE!\n");

    game_state_t* game_state = game_state_init();

    while (game_state->is_running)
    {
        game_process_events(game_state);
    }

    game_state_destroy(game_state);
}
