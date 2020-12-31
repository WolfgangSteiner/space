#include "game_state.h"
#include "base_defines.h"

game_state_t* game_state_init(size_t width, size_t height)
{
    game_state_t* game_state = calloc(1, sizeof(game_state_t));
    game_state->is_running = true;
    SDL_Init(SDL_INIT_VIDEO);
    game_state->window = window_create("SPACE!", width, height);
    game_state->pixel_buffer = bitmap_init(width, height);
    game_state->entities = dynarr_init(512);
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
    window_destroy(game_state->window);
    SDL_Quit();
}


void game_state_update(game_state_t* game_state) {
    for (size_t i = 0; i < game_state->entities->size; ++i) {
        entity_t* e = dynarr_at(entity_t, game_state->entities, i);
        e->update_func(e, game_state);
    }
}


void game_state_render(game_state_t* game_state) {
    memset(game_state->pixel_buffer->data, 0, sizeof(u32) * game_state->pixel_buffer->width * game_state->pixel_buffer->height);
    for (size_t i = 0; i < game_state->entities->size; ++i) {
        entity_t* e = dynarr_at(entity_t, game_state->entities, i);
        e->draw_func(e, game_state);
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
    dynarr_push(game_state->entities, entity);
}
