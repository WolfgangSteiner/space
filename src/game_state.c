#include "game_state.h"
#include "base_defines.h"

game_state_t* game_state_new(size_t width, size_t height)
{
    game_state_t* game_state = calloc(1, sizeof(game_state_t));
    game_state->is_running = true;
    SDL_Init(SDL_INIT_VIDEO);
    game_state->window = window_create("SPACE!", width, height);
    game_state->pixel_buffer = bitmap_init(width, height);
    game_state->entities = dynarr_init(512);
    game_state->behaviors = dynarr_init(16);
    game_state->delta_t = 0.3f;
    game_state->screen_rect = (recti_t){ 0, 0, width, height };
    SDL_Renderer* renderer = game_state->window->renderer;

    game_state->window->texture = 
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height);

    SDL_RenderSetLogicalSize(renderer, width, height);
    SDL_RenderSetIntegerScale(renderer, 1);

    return game_state;
}

void game_state_destroy(game_state_t* game_state)
{
    for (size_t i = 0; i < game_state->entities->size; i++) {
        entity_t* entity = dynarr_at(entity_t, game_state->entities, i);
        assert(entity->free_func);
        entity->free_func(entity);
    }

    for (size_t i = 0; i < game_state->behaviors->size; i++) {
        game_behavior_t* behavior = dynarr_at(game_behavior_t, game_state->behaviors, i);
        assert(behavior->free_func);
        behavior->free_func(behavior);
    }

    free(game_state->entities);
    free(game_state->behaviors);
    bitmap_free(game_state->pixel_buffer); 
    window_destroy(game_state->window);
    SDL_Quit();
}


static void game_state_update_entities(game_state_t* game_state) {
    for (size_t i = 0; i < game_state->entities->size; ++i) {
        entity_t* e = dynarr_at(entity_t, game_state->entities, i);
        e->update_func(e, game_state);
    }
}


static void game_state_update_behaviors(game_state_t* game_state) {
    for (size_t i = 0; i < game_state->behaviors->size; ++i) {
        game_behavior_t* b = dynarr_at(game_behavior_t, game_state->behaviors, i);
        b->update_func(b, game_state);
    }
}


void game_state_update(game_state_t* game_state) {
    u32 current_tick = SDL_GetTicks();
    game_state->delta_ticks = current_tick - game_state->current_tick;
    game_state->current_tick = current_tick;
    game_state_update_behaviors(game_state);
    game_state_update_entities(game_state);
}


void game_state_render(game_state_t* game_state) {
    memset(game_state->pixel_buffer->data, 0, sizeof(u32) * game_state->pixel_buffer->width * game_state->pixel_buffer->height);
    for (size_t i = 0; i < game_state->entities->size; ++i) {
        entity_t* e = dynarr_at(entity_t, game_state->entities, i);
        if (e->status == ENTITY_STATUS_ALIVE) {
            e->draw_func(e, game_state);
        }
    }
}


void game_state_present(game_state_t* game_state)
{
    int err = SDL_UpdateTexture(
        game_state->window->texture,
        NULL,
        game_state->pixel_buffer->data,
        game_state->pixel_buffer->width * sizeof(u32));

    assert(err == 0);

    SDL_RenderClear(game_state->window->renderer);
    
    SDL_RenderCopy(
        game_state->window->renderer,
        game_state->window->texture,
        NULL,
        NULL);

    SDL_RenderPresent(game_state->window->renderer);
}

void game_state_push_entity(game_state_t* game_state, entity_t* entity)
{
    entity->id = game_state->current_id++;
    entity->time_stamp = game_state->current_tick;
    dynarr_push(game_state->entities, entity);
}


void game_state_push_behavior(game_state_t* game_state, game_behavior_t* behavior)
{
    dynarr_push(game_state->behaviors, behavior);
}


static void game_state_clean_up_entities(game_state_t* game_state)
{
    size_t insert_idx = 0;
    void** entities = game_state->entities->data;
    size_t num_deleted_entities = 0;
    for (size_t idx = 0; idx < game_state->entities->size; idx++) {
        entity_t* e = (entity_t*)entities[idx];
        if (e->status == ENTITY_STATUS_ALIVE) {
            entities[insert_idx] = entities[idx];
            insert_idx++;
        } else {
            e->free_func(e);
            num_deleted_entities++;
        }
    }
    game_state->entities->size -= num_deleted_entities;
}


void game_state_clean_up(game_state_t* game_state)
{
    game_state_clean_up_entities(game_state);
}


static u32 map_key_from_keycode(SDL_Keycode keycode)
{
    u32 code = (u32)keycode;
    if (code & 0x40000000) {
        return (code & 0xffff) - 0x39 + 127;
    }
    else {
        return code;
    }
}


void game_state_process_key(game_state_t* game_state, SDL_Event event)
{
    SDL_Keycode key = event.key.keysym.sym;

    if (key == SDLK_q)
    {
        game_state->is_running = false;
    }

    u32 mapped_key = map_key_from_keycode(key);
    bool key_state = (event.type == SDL_KEYDOWN); 

    if (mapped_key < GAME_STATE_NUM_KEY_STATES) {
        game_state->key_states[mapped_key] = key_state;
    }
}


bool game_state_is_key_down(game_state_t* game_state, SDL_Keycode key)
{
    u32 mapped_key = map_key_from_keycode(key);
    if (mapped_key < GAME_STATE_NUM_KEY_STATES) {
        return game_state->key_states[mapped_key];
    } else {
        return false;
    }
}


void game_state_process_events(game_state_t* game_state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {   
        if (event.type == SDL_QUIT)
        {
            game_state->is_running = false;
        } 
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            game_state_process_key(game_state, event);
        }
    }
}


size_t game_state_count_entities_of_type(game_state_t* game_state, size_t type_id) {
    size_t count = 0;
    for (size_t i = 0; i < game_state->entities->size; ++i) {
        entity_t* e = dynarr_at(entity_t, game_state->entities, i);
        if (e->type_id == type_id) {
            count++;
        }
    }
    return count;
}


