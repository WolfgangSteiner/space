#ifndef ENTITY_H_
#define ENTITY_H_
#include "basetypes.h"
#include "vec2f.h"
#include "recti.h"
//#include "game_state.h"

struct game_state_s;

typedef struct entity_s
{
  size_t id;
  vec2f_t pos;
  recti_t bounding_box;
  
  void(*update_func)(struct entity_s*, struct game_state_s*);
  void(*draw_func)(struct entity_s*, struct game_state_s*);
} entity_t;



#endif
