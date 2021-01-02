#include <stdio.h>
#include "basetypes.h"
#include "SDL2/SDL.h"
#include <assert.h>
#include "base_defines.h"
#include "game_state.h"
#include "color.h"
#include "star_field.h"
#include "range.h"
#include "spaceship.h"



int main()
{   
    bitmap_t* spaceship = bitmap_read("assets/spaceship.pam");

    game_state_t* game_state = game_state_init(480 * 2, 270 * 2);
    star_field_t* star_field = star_field_init(
        game_state->screen_rect,
        100,
        rangef(1, 8),
        range_u32(0xddddddff, 0xffffffff));

    game_state_push_entity(game_state, (entity_t*)star_field);
    game_state_push_entity(game_state, (entity_t*)spaceship_new());

    while (game_state->is_running)
    {
        game_state_process_events(game_state);
        game_state_update(game_state);
        game_state_render(game_state);
        game_state_present(game_state);

        //SDL_Delay(16);
    }

    game_state_destroy(game_state);
    bitmap_free(spaceship);
}
