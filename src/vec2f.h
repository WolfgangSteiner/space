#ifndef VEC2F_H_
#define VEC2F_H_
#include "basetypes.h"
#include "vec2i.h"
#include "math.h"

typedef struct
{
  float x;
  float y;
} vec2f_t; 


#define vec2f(X,Y) ((vec2f_t) {X, Y})
#define vec2f_zeros() ((vect2i_t) {0.0f, 0.0f})
#define vec2f_ones() ((vec2f_t) {1.0f, 1.0f})

inline void vec2f_add(vec2f_t* a, vec2f_t b) { a->x += b.x; a->y += b.y; }
inline void vec2f_sub(vec2f_t* a, vec2f_t b) { a->x -= b.x; a->y -= b.y; }
inline void vec2f_smul(vec2f_t* a, float b) { a->x *= b; a->y *= b; }
inline void vec2f_smula(vec2f_t* a, vec2f_t b, float c) { a->x += b.x * c; a->y += b.y * c; }
vec2i_t vec2f_round(vec2f_t v);

#endif

