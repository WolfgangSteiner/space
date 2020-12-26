#ifndef STARFIELD_H_
#define STARFIELD_H_
#include "basetypes.h"
#include "entity.h"
#include "vec2f.h"
#include "range.h"
#include "color.h"

typedef struct 
{
  vec2f_t pos;
  vec2f_t vel;
  rgba_t color;
} star_t;


typedef struct
{
  entity_t entity;
  rangef_t velocity_range;
  range_u32_t color_range;
  size_t num_stars;
  star_t* stars;
} star_field_t;


star_field_t* star_field_init(
    recti_t bounding_box,
    size_t num_stars,
    rangef_t velocity_range,
    range_u32_t color_range);


#endif
