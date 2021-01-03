#include "sprite.h"
#include "game_state.h"
#include "base_defines.h"

static void sprite_draw_func(entity_t* entity, game_state_t* game_state)
{
    sprite_t* sprite = (sprite_t*)(entity);
    vec2i_t pos = { entity->pos.x, entity->pos.y };
    bitmap_blit(game_state->pixel_buffer, pos, sprite->bitmap, sprite->src_rect); 
}


sprite_t* sprite_alloc() {
    return calloc(1, sizeof(sprite_t));
}

static void sprite_free_func(entity_t* entity) {
    sprite_t* sprite = (sprite_t*)entity;
    bitmap_free(sprite->bitmap);
    free(entity);
}


void sprite_update_func(entity_t* entity, struct game_state_s* game_state) {
    sprite_t* sprite = (sprite_t*)entity;
    vec2f_smula(&entity->pos, entity->velocity, game_state->delta_ticks);

    if (sprite->animation_type == SPRITE_ANIMATION_NONE || sprite->num_cell_cols <= 1) {
        return;
    }

    size_t delta_ticks = game_state->current_tick - entity->time_stamp;

    if (delta_ticks > sprite->frame_time) {
        if (sprite->animation_type == SPRITE_ANIMATION_PING_PONG) {
            sprite->cell_idx.x += sprite->animation_direction;
            if (sprite->cell_idx.x == 0) {
                sprite->animation_direction = 1;
            } else if (sprite->cell_idx.x == (s32)sprite->num_cell_cols - 1) {
                sprite->animation_direction = -1;
            }
        } else if (sprite->animation_type == SPRITE_ANIMATION_CYCLE) {
            sprite->cell_idx.x 
                = (sprite->cell_idx.x + sprite->num_cell_cols + sprite->animation_direction) % sprite->num_cell_cols;
        }
        entity->time_stamp = game_state->current_tick;
        vec2i_t offset = vec2i_zeros(); 
        vec2i_vmula(&offset, sprite->cell_idx, sprite->cell_size); 
        sprite->src_rect = recti_make_with_position_and_size(offset, sprite->cell_size);
    }
}


void sprite_init(sprite_t* sprite) {
    entity_init(&sprite->entity);
    sprite->entity.update_func = sprite_update_func;
    sprite->entity.draw_func = sprite_draw_func;
    sprite->entity.free_func = sprite_free_func;
    sprite->animation_direction = 1;
}


void sprite_read(sprite_t* sprite, const char* file_name)
{
    sprite_init(sprite);
    sprite->bitmap = bitmap_read(file_name);
    assert(sprite->bitmap);
    if (sprite->bitmap) {
        sprite->src_rect = (recti_t){ 0, 0, sprite->bitmap->width, sprite->bitmap->height };
        sprite->entity.bounding_box = sprite->src_rect;
    }
}
