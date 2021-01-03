#include <stdlib.h>
#include "game_behavior.h"

void game_behavior_free(game_behavior_t* behavior) {
    free(behavior);
}
