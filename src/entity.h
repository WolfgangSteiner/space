#ifndef ENTITY_H_
#define ENTITY_H_
#include "basetypes.h"
#include "vec2f.h"
#include "recti.h"

typedef struct
{
  size_t id;
  vec2f_t pos;
  recti_t bounding_box;
  
  void(*update_func)(game_state_t*);
  void(*draw_func)(game_state_t*);
} entity_t;





#endif
