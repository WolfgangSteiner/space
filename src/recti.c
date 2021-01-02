#include "recti.h"

s32 recti_width(recti_t r) {
    return r.x2 - r.x1;
}


s32 recti_height(recti_t r) {
    return r.y2 - r.y1;
}

rangei_t recti_get_x_range(recti_t rect)
{
    return (rangei_t){rect.x1, rect.x2};
}

rangei_t recti_get_y_range(recti_t rect)
{
    return (rangei_t){rect.y1, rect.y2};
}

void recti_set_x_range(recti_t* rect, rangei_t x_range)
{
    rect->x1 = x_range.start;
    rect->x2 = x_range.end;
}

void recti_set_y_range(recti_t* rect, rangei_t y_range)
{
    rect->y1 = y_range.start;
    rect->y2 = y_range.end;
}

recti_t recti_align(recti_t rect, recti_t relative_to_rect, alignment_t x_align, alignment_t y_align)
{
    rangei_t x_range = rangei_align(recti_get_x_range(rect), recti_get_x_range(relative_to_rect), x_align);    
    rangei_t y_range = rangei_align(recti_get_y_range(rect), recti_get_y_range(relative_to_rect), y_align);    
    return (recti_t){ x_range.start, y_range.start, x_range.end, y_range.end };
}
