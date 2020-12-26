#ifndef COLOR_H_
#define COLOR_H_
#include "basetypes.h"
#include "range.h"

typedef union
{
  u32 val;
  struct 
  {
    u8 a;
    u8 b;
    u8 g;
    u8 r;
  };
} rgba_t;


typedef struct
{
  rgba_t start;
  rgba_t end;
} range_rgba_t;


rgba_t rgba(u8 red, u8 gree, u8 blue, u8 alpha);
rgba_t rgba_red();
rgba_t rgba_green();
rgba_t rgba_blue();
rgba_t rgba_white();
rgba_t rgba_black();
rgba_t rgba_random(rgba_t c_min, rgba_t cmax);

#endif
