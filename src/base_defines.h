#ifndef BASE_DEFINES_H_
#define BASE_DEFINES_H_

#include <assert.h>
#include <stdbool.h>
#include "basetypes.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ROUND_TO_INT(X) ((int)(X + 0.5f))
#define MImplies(a, b) assert(((a) && (b)) || !(a))
#define MUnused(A) (void)(A)
#define MInvalid() assert(false);

#define SHIFT_BYTE(TYPE, VAL, SHIFT) (((TYPE)(VAL)) << SHIFT)
#define U16_CONSTANT(A, B) (SHIFT_BYTE(u16, B, 8) | ((u16)A))
#define U32_CONSTANT(A, B, C, D) (SHIFT_BYTE(u32, D, 24) | SHIFT_BYTE(u32, C, 16) | SHIFT_BYTE(u32, B, 8) | (u32) A)

#endif
