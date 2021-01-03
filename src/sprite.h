#ifndef SPRITE_H_
#define SPRITE_H_
#include "entity.h"
#include "bitmap.h"

typedef enum
{
  SPRITE_ANIMATION_NONE = 0,
  SPRITE_ANIMATION_CYCLE = 1,
  SPRITE_ANIMATION_PING_PONG = 2
} sprite_animation_t;


typedef struct
{
  entity_t entity;
  bitmap_t* bitmap;
  recti_t src_rect;
  size_t num_cell_rows;
  size_t num_cell_cols;
  vec2i_t cell_idx;
  vec2i_t cell_size;
  sprite_animation_t animation_type;
  u32 frame_time;
  s32 animation_direction;
} sprite_t;


sprite_t* sprite_alloc();
void sprite_init(sprite_t* sprite);
void sprite_read(sprite_t* sprite, const char* file_name);
void sprite_free(sprite_t* sprite);
void sprite_update_func(entity_t* entity, struct game_state_s* game_state);
#endif
