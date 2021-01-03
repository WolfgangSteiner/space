#ifndef ENTITY_H_
#define ENTITY_H_
#include "basetypes.h"
#include "vec2f.h"
#include "recti.h"
//#include "game_state.h"

struct game_state_s;

typedef enum
{
  ENTITY_STATUS_ALIVE = 0,
  ENTITY_STATUS_REMOVE = 1
} entity_status_t;


typedef struct entity_s
{
  size_t type_id;
  size_t id;
  vec2f_t pos;
  vec2f_t velocity;
  recti_t bounding_box;
  u32 time_stamp;
  entity_status_t status;

  void(*update_func)(struct entity_s*, struct game_state_s*);
  void(*draw_func)(struct entity_s*, struct game_state_s*);
  void(*free_func)(struct entity_s*);
} entity_t;


void entity_init(entity_t* entity);
void entity_align_in_rect(entity_t* entity, recti_t rect, alignment_t x_align, alignment_t y_align);
void entity_translate(entity_t* entity, vec2f_t translation);
void entity_free_func(entity_t* entity);

#endif
