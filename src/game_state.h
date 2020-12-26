#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include <SDL2/SDL.h>
#include "bitmap.h"
#include "window.h"

typedef struct {
    bool is_running;
    window_t* window;
    bitmap_t* pixel_buffer;
} game_state_t;


game_state_t* game_state_init(size_t width, size_t height);
void game_state_destroy(game_state_t* game_state);
void game_state_present(game_state_t* game_state);

#endif
