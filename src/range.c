#include "range.h"
#include "stdlib.h"
#include "random.h"
#include "base_defines.h"

s32 rangei_random(rangei_t r)
{
    if (range_size(r) == 0) return r.start;
    return rand() % range_size(r) + r.start;
}

float rangef_random(rangef_t r)
{
    return randf_uniform_range(r.start, r.end);
}


rangei_t rangei_align(rangei_t range, rangei_t relative_to_range, alignment_t alignment)
{
    rangei_t result;
    if (alignment == ALIGNMENT_LEFT) {
        result.start = relative_to_range.start;
        result.end = result.start + range_size(range);
    } else if (alignment == ALIGNMENT_RIGHT) {
        result.end = relative_to_range.end;
        result.start = result.end - range_size(range);
    } else if (alignment == ALIGNMENT_CENTER) {
        result.start = (range_size(relative_to_range) - range_size(range)) / 2;
        result.end = result.start + range_size(range);
    } else if (alignment == ALIGNMENT_NONE) {
        result = range;
    } else {
        result = range;
        MInvalid();
    }

    return result;
}
