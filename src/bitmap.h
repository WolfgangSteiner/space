#ifndef BITMAP_H_
#define BITMAP_H_
#include "basetypes.h"
#include "color.h"
#include "vec2i.h"

typedef struct
{
    size_t width;
    size_t height;
    rgba_t* data;
} bitmap_t;

bitmap_t* bitmap_init(size_t width, size_t height);
void bitmap_free(bitmap_t* bitmap);
void bitmap_set_pixel(bitmap_t* bitmap, vec2i_t pos, rgba_t color);


#endif
