#ifndef GAME_BEHAVIOR_H_
#define GAME_BEHAVIOR_H_

struct game_state_s;

typedef struct game_behavior_s
{
  void(*free_func)(struct game_behavior_s*);
  void(*update_func)(struct game_behavior_s*, struct game_state_s*);

} game_behavior_t;


void game_behavior_free(game_behavior_t* behavior);

#endif
