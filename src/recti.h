#ifndef RECTI_H_
#define RECTI_H_
#include "basetypes.h"
#include "alignment.h"
#include "range.h"

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

rangei_t recti_get_x_range(recti_t rect);
rangei_t recti_get_y_range(recti_t rect);

void recti_set_x_range(recti_t* rect, rangei_t x_range);
void recti_set_y_range(recti_t* rect, rangei_t y_range);

recti_t recti_align(recti_t rect, recti_t relative_to_rect, alignment_t x_align, alignment_t y_align);

#endif
