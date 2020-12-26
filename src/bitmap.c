#include "bitmap.h"
#include <stdlib.h>

bitmap_t* bitmap_init(size_t width, size_t height)
{
    bitmap_t* bitmap = calloc(1, sizeof(bitmap_t));
    bitmap->width = width;
    bitmap->height = height;
    bitmap->data = calloc(width * height, sizeof(u32));
    return bitmap;
}

void bitmap_free(bitmap_t* bitmap)
{
    free(bitmap->data);
    free(bitmap);
}

