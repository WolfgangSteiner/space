#ifndef VEC2I_H_
#define VEC2I_H_
#include "basetypes.h"


typedef struct
{
  s32 x;
  s32 y;
} vec2i_t; 


#define vec2i(X,Y) ((vec2i_t) {X, Y})
#define vec2i_zeros() ((vec2i_t) {0, 0})
#define vec2i_ones() ((vec2i_t) {1, 1})
void vec2i_add(vec2i_t* a, vec2i_t b);
void vec2i_sub(vec2i_t* a, vec2i_t b);
void vec2i_smul(vec2i_t* a, s32 c);
void vec2i_smula(vec2i_t* a, vec2i_t b, s32 c);
void vec2i_vmula(vec2i_t* a, vec2i_t b, vec2i_t c);


#endif
