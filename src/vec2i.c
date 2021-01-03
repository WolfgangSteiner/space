#include "vec2i.h"


void vec2i_add(vec2i_t* a, vec2i_t b) {
    a->x += b.x;
    a->y += b.y;
}


void vec2i_sub(vec2i_t* a, vec2i_t b) {
    a->x -= b.x;
    a->y -= b.y;
}


void vec2i_smul(vec2i_t* a, s32 c) {
    a->x *= c;
    a->y *= c;
}


void vec2i_smula(vec2i_t* a, vec2i_t b, s32 c) {
    a->x += c * b.x;
    a->y += c * b.y;
}


void vec2i_vmula(vec2i_t* a, vec2i_t b, vec2i_t c) {
    a->x += c.x * b.x;
    a->y += c.y * b.y;
}



