#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include <SDL2/SDL.h>
#include "bitmap.h"
#include "window.h"
#include "entity.h"
#include "dynarr.h"

#define GAME_STATE_NUM_KEY_STATES 346

typedef struct game_state_s {
    bool is_running;
    window_t* window;
    bitmap_t* pixel_buffer;
    recti_t screen_rect;
    float delta_t;
    dynarr_t* entities;
    bool key_states[GAME_STATE_NUM_KEY_STATES];    
} game_state_t;


game_state_t* game_state_init(size_t width, size_t height);
void game_state_destroy(game_state_t* game_state);
void game_state_present(game_state_t* game_state);
void game_state_push_entity(game_state_t* game_state, entity_t* entity);
void game_state_update(game_state_t* game_state); 
void game_state_render(game_state_t* game_state);
void game_state_process_key(game_state_t* game_state, SDL_Event event);
void game_state_process_events(game_state_t* game_state);
bool game_state_is_key_down(game_state_t* game_state, SDL_Keycode key);
#endif
