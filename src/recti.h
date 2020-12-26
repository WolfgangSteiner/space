#ifndef RECTI_H_
#define RECTI_H_
#include "basetypes.h"

typedef struct 
{
  s32 x1;
  s32 y1;
  s32 x2;
  s32 y2;
} recti_t;


#define recti(X1,Y1,X2,Y2) ((recti_t){X1, Y1, X2, Y2})

#endif
