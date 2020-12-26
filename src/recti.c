#include "recti.h"

s32 recti_width(recti_t r) {
    return r.x2 - r.x1;
}


s32 recti_height(recti_t r) {
    return r.y2 - r.y1;
}



