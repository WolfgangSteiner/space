#ifndef RANDOM_H_
#define RANDOM_H_
#include "basetypes.h"

double randd_uniform();
float randf_uniform();
float randf_uniform_range(float a, float b);
s32 randi_uniform(s32 max_value);

#endif
