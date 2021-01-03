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
#include "cycloid_wave.h"


int main()
{   
    game_state_t* game_state = game_state_new(480 * 2, 270 * 2);
    star_field_t* star_field = star_field_new(
        game_state->screen_rect,
        100,
        rangef(1, 8),
        range_u32(0xddddddff, 0xffffffff));

    game_state_push_entity(game_state, (entity_t*)star_field);
    spaceship_t* spaceship = spaceship_new();
    entity_align_in_rect((entity_t*)spaceship, game_state->screen_rect, ALIGNMENT_CENTER, ALIGNMENT_BOTTOM);
    entity_translate((entity_t*)spaceship, (vec2f_t){0.0f, -rect_height(spaceship->sprite.entity.bounding_box)});

    game_state_push_behavior(game_state, (game_behavior_t*)cycloid_wave_new());
    game_state_push_entity(game_state, (entity_t*)spaceship);

    while (game_state->is_running)
    {
        game_state_process_events(game_state);
        game_state_update(game_state);
        game_state_render(game_state);
        game_state_present(game_state);
        game_state_clean_up(game_state);

        //SDL_Delay(16);
    }

    game_state_destroy(game_state);
}
