#ifndef DYNARR_H_
#define DYNARR_H_

#include <stddef.h>

#define DYNARR_DEFAULT_ALLOC_SIZE 16

typedef struct
{
    size_t size;
    size_t alloc_size;
    void** data;
} dynarr_t;


#define dynarr_at(TYPE, ARR, IDX) ((TYPE*)ARR->data[IDX])

dynarr_t* dynarr_alloc();
void dynarr_init(dynarr_t* arr);
dynarr_t* dynarr_new();

void dynarr_push(dynarr_t* arr, void* value);

void dynarr_free(dynarr_t* arr, void(*free_callback)(void*));

void dynarr_swap(dynarr_t* arr, size_t idxa, size_t idxb);


#define DYNARR_INIT(ARR) \
    ARR.size = 0; \
    ARR.alloc_size = DYNARR_DEFAULT_ALLOC_SIZE; \
    ARR.arr = calloc(ARR.alloc_size, sizeof(*ARR.arr));


#define DYNARR_DECL(TYPE) \
    struct { \
        size_t size; \
        size_t alloc_size; \
        TYPE* arr; \
    }


#define DYNARR_CHECK_RESIZE(ARR) \
if (ARR.size == ARR.alloc_size) { \
    ARR.alloc_size *= 2; \
    ARR.arr = realloc(ARR.arr, ARR.alloc_size * sizeof(*ARR.arr)); \
    assert(ARR.arr); \
}

#define DYNARR_PUSH(ARR, ELMNT) \
    DYNARR_CHECK_RESIZE(ARR); \
    ARR.arr[ARR->size++] = ELMNT;

#endif
