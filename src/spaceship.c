#include <stdlib.h>
#include "spaceship.h"
#include "game_state.h"
#include "base_defines.h"

static void spaceship_move_left(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    spaceship->sprite.entity.pos.x -= spaceship->move_deltas.x;
}

static void spaceship_move_right(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    spaceship->sprite.entity.pos.x += spaceship->move_deltas.x;
}

static void spaceship_move_up(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    spaceship->sprite.entity.pos.y -= spaceship->move_deltas.y;
}

static void spaceship_move_down(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    spaceship->sprite.entity.pos.y += spaceship->move_deltas.y;
}


static void spaceship_update_func(entity_t* entity, game_state_t* game_state) {
    spaceship_t* spaceship = (spaceship_t*)entity;
    if (game_state_is_key_down(game_state, SDLK_a)) {
        spaceship_move_left(spaceship, game_state);
    }

    if (game_state_is_key_down(game_state, SDLK_d)) {
        spaceship_move_right(spaceship, game_state);
    }

    if (game_state_is_key_down(game_state, SDLK_w)) {
        spaceship_move_up(spaceship, game_state);
    }

    if (game_state_is_key_down(game_state, SDLK_s)) {
        spaceship_move_down(spaceship, game_state);
    }
}


spaceship_t* spaceship_new() {
    spaceship_t* spaceship = calloc(1, sizeof(spaceship));
    sprite_read(&spaceship->sprite, "assets/spaceship.pam");
    spaceship->sprite.entity.update_func = spaceship_update_func;
    spaceship->move_deltas = (vec2f_t){4, 4};
    return spaceship;
}

