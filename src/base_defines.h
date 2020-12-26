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

#endif
