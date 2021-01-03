#include <stdlib.h>
#include "spaceship.h"
#include "game_state.h"
#include "base_defines.h"

static void spaceship_move_left(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    s32 px = spaceship->sprite.entity.pos.x;
    spaceship->sprite.entity.pos.x = MAX(0, px - spaceship->move_deltas.x);
}

static void spaceship_move_right(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    entity_t* entity = (entity_t*)spaceship;
    s32 width = rect_width(entity->bounding_box);
    s32 screen_width = rect_width(game_state->screen_rect);
    s32 px = entity->pos.x + spaceship->move_deltas.x;
    entity->pos.x = MIN(px, screen_width - width);
}

static void spaceship_move_up(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    s32 py = spaceship->sprite.entity.pos.y;
    spaceship->sprite.entity.pos.y = MAX(0, py - spaceship->move_deltas.y);
}

static void spaceship_move_down(spaceship_t* spaceship, game_state_t* game_state) {
    MUnused(game_state);
    entity_t* entity = (entity_t*)spaceship;
    s32 height = rect_height(entity->bounding_box);
    s32 screen_height = rect_height(game_state->screen_rect);
    s32 py = entity->pos.y + spaceship->move_deltas.y;
    entity->pos.y = MIN(py, screen_height - height);
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
    spaceship_t* spaceship = calloc(1, sizeof(spaceship_t));
    sprite_read(&spaceship->sprite, "assets/spaceship.pam");
    spaceship->sprite.entity.update_func = spaceship_update_func;
    spaceship->move_deltas = (vec2f_t){8, 8};
    return spaceship;
}

