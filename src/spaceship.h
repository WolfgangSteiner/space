#ifndef SPACESHIP_H_
#define SPACESHIP_H_
#include "sprite.h"

typedef struct {
  sprite_t sprite;
  vec2f_t move_deltas;
} spaceship_t;


spaceship_t* spaceship_new();


#endif
