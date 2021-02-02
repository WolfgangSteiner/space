#ifndef CYCLOID_H_
#define CYCLOID_H_
#include "sprite.h"
#include "game_state.h"

#define CYCLOID_ID 0x3cd0f7297a6f9a02

void cycloid_load_assets(game_state_t* game_state);
sprite_t* cycloid_new(game_state_t* game_state);

#endif
