#include "cycloid.h"
#include "game_state.h"
#include "random.h"

static void cycloid_update_func(entity_t* entity, game_state_t* game_state)
{
    sprite_update_func(entity, game_state);
    vec2i_t pos = vec2f_round(entity->pos);
    if (pos.y >= game_state->screen_rect.y2) {
       entity->status = ENTITY_STATUS_REMOVE; 
    }
}

sprite_t* cycloid_new()
{
    sprite_t* cycloid = sprite_alloc();
    sprite_read(cycloid, "assets/cycloid.pam");
    cycloid->cell_size = (vec2i_t){16, 16};
    cycloid->src_rect = recti(0, 0, 16, 16);
    cycloid->num_cell_rows = 1;
    cycloid->num_cell_cols = 6;
    cycloid->entity.type_id = CYCLOID_ID;
    cycloid->entity.update_func = cycloid_update_func;
    cycloid->frame_time = 100;
    cycloid->animation_type = SPRITE_ANIMATION_PING_PONG;
    cycloid->entity.velocity = vec2f(0, 0.1);
    cycloid->cell_idx.x = randi_uniform(cycloid->num_cell_cols - 1);
    return cycloid;
}

