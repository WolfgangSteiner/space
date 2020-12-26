#ifndef VEC2I_H_
#define VEC2I_H_
#include "basetypes.h"


typedef struct
{
  s32 x;
  s32 y;
} vec2i_t; 


#define vec2i(X,Y) ((vec2i_t) {X, Y})
#define vec2i_zeros() ((vect2i_t) {0, 0})
#define vec2i_ones() ((vec2i_t) {1, 1})


#endif
