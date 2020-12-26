#ifndef BITMAP_H_
#define BITMAP_H_
#include "basetypes.h"

typedef struct
{
    size_t width;
    size_t height;
    u32* data;
} bitmap_t;

bitmap_t* bitmap_init(size_t width, size_t height);
void bitmap_free(bitmap_t* bitmap);

#endif
