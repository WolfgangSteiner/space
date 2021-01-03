#ifndef CYCLOID_WAVE_H_
#define CYCLOID_WAVE_H_

#include "game_behavior.h"
#include "basetypes.h"


typedef struct
{
  game_behavior_t behavior;
  size_t max_num_cycloids;

} cycloid_wave_t;


cycloid_wave_t* cycloid_wave_new();


#endif
