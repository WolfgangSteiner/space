#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include "base_defines.h"
#include <string.h>
#include "vec2i.h"


static const u16 MAGIC_P7 = U16_CONSTANT('P', '7');

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
    if (bitmap)
    {
        free(bitmap->data);
        free(bitmap);
    }
}

void bitmap_set_pixel(bitmap_t* bitmap, vec2i_t pos, rgba_t color)
{
    int width = bitmap->width;
    int height = bitmap->height;
    if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) { 
        bitmap->data[width * pos.y + pos.x] = color;
    }
}


static bool bitmap_read_magic_u16(FILE* fp, u16* magic)
{
    size_t num_words_read = fread(magic, sizeof(u16), 1, fp);
    return (num_words_read == 1);
} 


typedef struct
{
    size_t size;
    void* data;
} blob_t;


blob_t* read_file(FILE* fp)
{
    size_t buffer_size = 1024;
    void* buffer = malloc(buffer_size);
    blob_t* blob = calloc(1, sizeof(blob_t));
    blob->data = calloc(1, buffer_size);
    size_t pos = 0;

    while (true)
    {
        size_t bytes_read = fread(buffer, sizeof(u8), buffer_size, fp);
        if (bytes_read == 0) break;
        blob->size += bytes_read;
        if (blob->data == 0) {
            blob->data = malloc(bytes_read);
        } else {
            blob->data = realloc(blob->data, blob->size);
        }
        memcpy(blob->data + pos, buffer, bytes_read);
        pos += bytes_read;
    }

    return blob;
}


static bitmap_t* bitmap_read_pam(FILE* fp)
{
    u16 magic;
    bool success = bitmap_read_magic_u16(fp, &magic);
    if (success == false || magic != MAGIC_P7) return NULL;
    rewind(fp);

    u32 width = 0;
    u32 height = 0;
    u32 max_val = 0;
    u32 depth = 0;

    char line[512];

    while (true) {
        if (fgets(line, 512, fp)) {
            if (strstr(line, "P7")) {
                continue; 
            } else if (line[0] == '#') {
                continue; 
            } else if (strstr(line, "ENDHDR")) {
                break;
            } else if (strstr(line, "WIDTH")) {
                width = atoi(line + sizeof("WIDTH"));
            } else if (strstr(line, "HEIGHT")) {
                height = atoi(line + sizeof("HEIGHT"));
            } else if (strstr(line, "DEPTH")) {
                depth = atoi(line + sizeof("DEPTH"));
            } else if (strstr(line, "MAXVAL")) {
                max_val = atoi(line + sizeof("MAXVAL"));
            } else if (strstr(line, "TUPLTYPE")) {
                assert(strstr(line, "RGB_ALPHA"));
            }
        }
    }

    if (width == 0 || height == 0 || depth != 4 || max_val != 255) {
        return NULL;
    }

    bitmap_t* bitmap = bitmap_init(width, height);
    size_t num_pixels = width * height;
    size_t num_pixels_read = fread(bitmap->data, sizeof(rgba_t), num_pixels, fp);
    
    if (num_pixels_read != num_pixels) {
        bitmap_free(bitmap);
        bitmap = NULL;
    }

    return bitmap;
}


bitmap_t* bitmap_read(const char* file_name)
{
    FILE* fp = fopen(file_name, "rb");
    bitmap_t* bitmap = NULL;

    u16 magic16;
    bool success = bitmap_read_magic_u16(fp, &magic16);
    if (!success) goto error;

    assert(magic16 == MAGIC_P7);
    
    if (magic16 == MAGIC_P7) {
        fseek(fp, 0, SEEK_SET);
        bitmap = bitmap_read_pam(fp);
        if (bitmap) goto end;
    }

error:
    bitmap_free(bitmap);
    bitmap = NULL;

end:    
    fclose(fp);

    return bitmap;
} 


#define BITMAP_BLEND_COMPONENT(COMP) (((u32)src.COMP * (u32)src.a * 255) + ((u32)dst.COMP * (u32)dst.a * (0xff - src.a))) / res.a / 255

#define BITMAP_BLEND_COMPONENT_ONE(COMP) (((u32)src.COMP * (u32)src.a) + ((u32)dst.COMP * (0xff - src.a))) / 255

rgba_t alpha_blend(rgba_t dst, rgba_t src)
{
    rgba_t res;
    res.a = (((u32)src.a * 255) + (dst.a * (0xff - src.a))) / 255;
    if (res.a == 0) {
        res.val = 0x0;
    } else {
        res.r = BITMAP_BLEND_COMPONENT(r);
        res.g = BITMAP_BLEND_COMPONENT(g);
        res.b = BITMAP_BLEND_COMPONENT(b);
    }

    return res;
}

rgba_t alpha_blend_one(rgba_t dst, rgba_t src)
{
    rgba_t res;
    res.r = BITMAP_BLEND_COMPONENT_ONE(r);
    res.g = BITMAP_BLEND_COMPONENT_ONE(g);
    res.b = BITMAP_BLEND_COMPONENT_ONE(b);
    res.a = 0xff;

    return res;
}

void bitmap_blit(bitmap_t* dst, vec2i_t pos, bitmap_t* src, recti_t src_rect)
{
    size_t src_x1 = MAX(0, src_rect.x1);
    size_t src_x2 = MIN((s32)src->width, src_rect.x2);
    size_t src_y1 = MAX(0, src_rect.y1);
    size_t src_y2 = MIN((s32)src->height, src_rect.y2);
    size_t src_width = src_x2 - src_x1;
    size_t src_height = src_y2 - src_y1;

    size_t dst_x1 = MAX(0, pos.x);
    size_t dst_x2 = MIN(dst->width, pos.x + src_width);
    size_t dst_y1 = MAX(0, pos.y);
    size_t dst_y2 = MIN(dst->height, pos.y + src_height);

    size_t src_offset_x = pos.x < 0 ? (size_t)(-pos.x) : 0;
    size_t src_offset_y = pos.y < 0 ? (size_t)(-pos.y) : 0;

    src_x1 += src_offset_x;
    src_y1 += src_offset_y;

    rgba_t* dst_row_ptr = dst->data + dst->width * dst_y1 + dst_x1;
    rgba_t* src_row_ptr = src->data + src->width * src_y1 + src_x1; 

    for (size_t y = dst_y1; y < dst_y2; ++y) {
        rgba_t* dst_ptr = dst_row_ptr;
        rgba_t* src_ptr = src_row_ptr;
        for (size_t x = dst_x1; x < dst_x2; ++x) {
            *dst_ptr = alpha_blend_one(*dst_ptr, (*src_ptr++));
            dst_ptr++;
        }

        src_row_ptr += src->width;
        dst_row_ptr += dst->width;
    }
}

void bitmap_mul_alpha(bitmap_t* bitmap, u8 alpha)
{
    rgba_t* dst = bitmap->data;
    size_t num_pixels = bitmap->width * bitmap->height;
    for (size_t i = 0; i < num_pixels; ++i) {
        (*dst).a = ((*dst).a * alpha) / 255;
        dst++;
    }
}
