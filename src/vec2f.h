#ifndef VEC2I_H_
#define VEC2I_H_
#include "basetypes.h"


typedef struct
{
  float x;
  float y;
} vec2f_t; 


#define vec2f(X,Y) ((vec2f_t) {X, Y})
#define vec2f_zeros() ((vect2i_t) {0.0f, 0.0f})
#define vec2f_ones() ((vec2f_t) {1.0f, 1.0f})


#endif
