#include <stdio.h>
#include "basetypes.h"
#include "SDL2/SDL.h"
#include <assert.h>
#include "base_defines.h"
#include "game_state.h"

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


u32 random_color()
{
    u32 r = rand() & 0xF0000000;
    u32 g = rand() & 0x00F00000;
    u32 b = rand() & 0x0000F000;
    u8 a = 0x000000ff;
    return r | g | b | a;
}


void render_game(game_state_t* game_state)
{
    bitmap_t* pixels = game_state->pixel_buffer;
    const size_t width = pixels->width;
    const size_t height = pixels->height;
    for (size_t y = 0; y < height; ++y)
    {
        u32 c = random_color();
        for (size_t x = 0; x < width; ++x)
        {
            pixels->data[y * width + x] = c;
        }
    }
}

void update_game(game_state_t* game_state)
{
    MUnused(game_state);
}


int main()
{   
    printf("SPACE!\n");

    game_state_t* game_state = game_state_init(480, 270);

    while (game_state->is_running)
    {
        game_process_events(game_state);

        update_game(game_state);
        render_game(game_state);

        game_state_present(game_state);

        SDL_Delay(16);
    }

    game_state_destroy(game_state);
}
