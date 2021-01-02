#ifndef SPRITE_H_
#define SPRITE_H_
#include "entity.h"
#include "bitmap.h"

typedef struct
{
  entity_t entity;
  bitmap_t* bitmap;
  recti_t src_rect;
} sprite_t;


sprite_t* sprite_alloc();
void sprite_init(sprite_t* sprite);
void sprite_read(sprite_t* sprite, const char* file_name);
void sprite_free(sprite_t* sprite);
#endif
