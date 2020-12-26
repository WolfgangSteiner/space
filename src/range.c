#include "range.h"
#include "stdlib.h"

s32 rangei_random(rangei_t r)
{
    if (range_size(r) == 0) return r.start;
    return rand() % range_size(r) + r.start;
}

float rangef_random(rangef_t r)
{
    if (range_size(r) == 0) return r.start;
    return rand() % (int)range_size(r) + r.start;
}
