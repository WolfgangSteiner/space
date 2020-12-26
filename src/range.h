#ifndef RANGE_H_
#define RANGE_H_
#include "basetypes.h"

typedef struct
{
  s32 start;
  s32 end;
} rangei_t;

typedef struct
{
  u32 start;
  u32 end;
} range_u32_t;

typedef struct
{
  float start;
  float end;
} rangef_t;

#define rangei(START, END) ((rangei_t){START, END})
#define range_u32(START, END) ((range_u32_t){START, END})
#define rangef(START, END) ((rangef_t){START, END})
#define range_size(RANGE) (RANGE.end - RANGE.start) 
s32 rangei_random(rangei_t r);
float rangef_random(rangef_t r);

#endif
