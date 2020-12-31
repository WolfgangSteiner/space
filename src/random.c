#include "random.h"
#include "stdlib.h"

double randd_uniform()
{
    return (double)rand() / ((double)(RAND_MAX) + 1);
}


float randf_uniform()
{
    return (float)randd_uniform();
}


float randf_uniform_range(float a, float b)
{
    float diff = b - a;
    if (diff == 0.0f) return a;
    return randf_uniform() * diff + a; 
}
