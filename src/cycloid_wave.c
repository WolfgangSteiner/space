#include <stdlib.h>
#include "cycloid_wave.h"
#include "game_state.h"
#include "cycloid.h"
#include "random.h"

void cycloid_wave_free_func(game_behavior_t* behavior) {
    game_behavior_free(behavior);
}

void cycloid_wave_update_func(game_behavior_t* behavior, game_state_t* game_state) {
    cycloid_wave_t* wave = (cycloid_wave_t*)behavior;
    size_t num_cycloids = game_state_count_entities_of_type(game_state, CYCLOID_ID); 

    if (num_cycloids < wave->max_num_cycloids) {
        s32 d100 = randi_uniform(100);
        if (d100 > 95) {
            s32 x = randi_uniform(rect_width(game_state->screen_rect));
            sprite_t* cycloid = cycloid_new(game_state);
            cycloid->entity.pos.x = x;
            cycloid->entity.pos.y = -cycloid->cell_size.y;
            game_state_push_entity(game_state, (entity_t*)cycloid);
        }
    } 
} 

cycloid_wave_t* cycloid_wave_new() {
    cycloid_wave_t* wave = calloc(1, sizeof(cycloid_wave_t));
    wave->max_num_cycloids = 16;
    wave->behavior.update_func = cycloid_wave_update_func;
    wave->behavior.free_func = cycloid_wave_free_func;

    return wave;
}
