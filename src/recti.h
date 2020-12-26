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
#define rect_width(RECT) (RECT.x2 - RECT.x1)
#define rect_height(RECT) (RECT.y2 - RECT.y1)

#endif
