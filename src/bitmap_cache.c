#include "bitmap_cache.h"
#include <stdlib.h>
#include <assert.h>

#define BITMAP_CACHE_DEFAULT_SIZE 16


bitmap_cache_t* bitmap_cache_new() {
    bitmap_cache_t* bitmap_cache = calloc(1, sizeof(bitmap_cache_t));
    DYNARR_INIT(bitmap_cache->bitmaps);
    return bitmap_cache;
}

void bitmap_cache_insert(bitmap_cache_t* cache, char* file_name, size_t id) {
    DYNARR_CHECK_RESIZE(cache->bitmaps);
    bitmap_t* bitmap = bitmap_read(file_name);
    assert(bitmap);
    cache->bitmaps.arr[cache->bitmaps.size++] = (bitmap_cache_bucket_t){id, bitmap};
}

bitmap_t* bitmap_cache_get(bitmap_cache_t* cache, size_t id) {
    for (size_t i = 0; i < cache->bitmaps.size; ++i) {
       bitmap_cache_bucket_t* bucket = &cache->bitmaps.arr[i];
       if (bucket->id == id) {
           return bucket->bitmap;
       }
    }
    assert(false);
    return NULL;
}


void bitmap_cache_free(bitmap_cache_t* cache) {
    bitmap_cache_clear(cache);
    free(cache);
}


void bitmap_cache_clear(bitmap_cache_t* cache) {
    for (size_t i = 0; i < cache->bitmaps.size; ++i) {
       bitmap_free(cache->bitmaps.arr[i].bitmap);
    } 

    cache->bitmaps.size = 0;
}


