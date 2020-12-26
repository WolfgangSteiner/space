#include "bitmap.h"
#include <stdlib.h>

bitmap_t* bitmap_init(size_t width, size_t height)
{
    bitmap_t* bitmap = calloc(1, sizeof(bitmap_t));
    bitmap->width = width;
    bitmap->height = height;
    bitmap->data = calloc(width * height, sizeof(rgba_t));
    return bitmap;
}

void bitmap_free(bitmap_t* bitmap)
{
    free(bitmap->data);
    free(bitmap);
}

void bitmap_set_pixel(bitmap_t* bitmap, vec2i_t pos, rgba_t color)
{
    int width = bitmap->width;
    int height = bitmap->height;
    if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) { 
        bitmap->data[width * pos.y + pos.x] = color;
    }
}

