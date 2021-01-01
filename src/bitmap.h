#ifndef BITMAP_H_
#define BITMAP_H_
#include "basetypes.h"
#include "color.h"
#include "vec2i.h"
#include "recti.h"

typedef struct
{
    size_t width;
    size_t height;
    rgba_t* data;
} bitmap_t;

bitmap_t* bitmap_init(size_t width, size_t height);
bitmap_t* bitmap_read(const char* file_name);
void bitmap_free(bitmap_t* bitmap);
void bitmap_set_pixel(bitmap_t* bitmap, vec2i_t pos, rgba_t color);
void bitmap_blit(bitmap_t* dst, vec2i_t pos, bitmap_t* src, recti_t src_rect);
void bitmap_mul_alpha(bitmap_t* dst, u8 alpha);



#endif
