#include <stdio.h>
#include "basetypes.h"
#include "SDL2/SDL.h"
#include <assert.h>
#include "base_defines.h"
#include "game_state.h"
#include "color.h"
#include "star_field.h"
#include "range.h"

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


rgba_t random_color()
{
    rgba_t min_color = rgba(0x10, 0x10, 0x10, 0xff);
    rgba_t max_color = rgba(0xf0, 0xf0, 0xf0, 0xff);
    return rgba_random(min_color, max_color);
}


void render_game(game_state_t* game_state)
{
    bitmap_t* pixels = game_state->pixel_buffer;
    const size_t width = pixels->width;
    const size_t height = pixels->height;
    for (size_t y = 0; y < height; ++y)
    {
        rgba_t c = random_color();
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
    game_state_t* game_state = game_state_init(480, 270);
    star_field_t* star_field = star_field_init(
        game_state->screen_rect,
        100,
        rangef(1, 8),
        range_u32(0xddddddff, 0xffffffff));

    game_state_push_entity(game_state, (entity_t*)star_field);


    while (game_state->is_running)
    {
        game_process_events(game_state);

        game_state_update(game_state);
        game_state_render(game_state);

        game_state_present(game_state);

        SDL_Delay(16);
    }

    game_state_destroy(game_state);
}
