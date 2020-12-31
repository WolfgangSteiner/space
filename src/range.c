#include "range.h"
#include "stdlib.h"
#include "random.h"

s32 rangei_random(rangei_t r)
{
    if (range_size(r) == 0) return r.start;
    return rand() % range_size(r) + r.start;
}

float rangef_random(rangef_t r)
{
    return randf_uniform_range(r.start, r.end);
}

