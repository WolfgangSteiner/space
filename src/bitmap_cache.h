#ifndef BITMAP_CACHE_H_
#define BITMAP_CACHE_H_

#include "bitmap.h"
#include "dynarr.h"
#include <stddef.h>


typedef struct {
  size_t id;
  bitmap_t* bitmap;
} bitmap_cache_bucket_t;


typedef struct {
  DYNARR_DECL(bitmap_cache_bucket_t) bitmaps;
} bitmap_cache_t;


bitmap_cache_t* bitmap_cache_new();
void bitmap_cache_free(bitmap_cache_t* bitmap_cache);
void bitmap_cache_insert(bitmap_cache_t* bitmap_cache, char* file_name, size_t id);
bitmap_t* bitmap_cache_get(bitmap_cache_t* bitmap_cache, size_t id);
void bitmap_cache_clear(bitmap_cache_t* cache);
#endif
