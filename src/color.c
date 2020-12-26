#include "color.h"
#include "stdlib.h"

rgba_t rgba(u8 red, u8 green, u8 blue, u8 alpha)
{
    return (rgba_t){.r=red, .g=green, .b=blue, .a=alpha};
}


rgba_t rgba_red()
{
    return (rgba_t){.val=0xff0000ff};
}


rgba_t rgba_green()
{
    return (rgba_t){.val=0x00ff00ff};
}


rgba_t rgba_blue()
{
    return (rgba_t){.val=0x0000ffff};
}


rgba_t rgba_white()
{
    return (rgba_t){.val=0xffffffff};
}

rgba_t rgba_black()
{
    return (rgba_t){.val=0x000000ff};
}

rgba_t rgba_random(rgba_t c_min, rgba_t c_max)
{
    u8 r_diff = c_max.r - c_min.r;
    u8 g_diff = c_max.g - c_min.g;
    u8 b_diff = c_max.b - c_min.b;
    u8 a_diff = c_max.a - c_min.a;
    
    u8 r = r_diff == 0 ? c_min.r : rand() % r_diff + c_min.r;
    u8 g = g_diff == 0 ? c_min.g : rand() % g_diff + c_min.g;
    u8 b = b_diff == 0 ? c_min.b : rand() % b_diff + c_min.b;
    u8 a = a_diff == 0 ? c_min.a : rand() % a_diff + c_min.a;

    return (rgba_t){.r=r, .g=g, .b=b, .a=a};
}
