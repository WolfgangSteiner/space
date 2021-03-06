#include "vec2f.h"

void vec2f_add(vec2f_t* a, vec2f_t b);
void vec2f_sub(vec2f_t* a, vec2f_t b);
void vec2f_smul(vec2f_t* a, float b); 
void vec2f_smula(vec2f_t* a, vec2f_t b, float c);
vec2i_t vec2f_round(vec2f_t v) { return (vec2i_t){ roundf(v.x), roundf(v.y) }; }
