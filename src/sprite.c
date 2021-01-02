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


void sprite_init(sprite_t* sprite) {
    sprite->entity.draw_func = sprite_draw_func;
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
