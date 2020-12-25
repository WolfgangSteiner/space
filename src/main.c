#include <stdio.h>
#include "basetypes.h"
#include "SDL2/SDL.h"
#include <assert.h>

typedef struct {
    SDL_Window* sdl_window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} window_t;


window_t* window_create(char* title)
{
    window_t* win = calloc(1, sizeof(window_t));
    win->sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0);

    win->renderer = SDL_CreateRenderer(
        win->sdl_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    return win;

}

void window_destroy(window_t* win)
{
    SDL_DestroyWindow(win->sdl_window);
    free(win);
}


typedef struct
{
    size_t width;
    size_t height;
    u32* data;
} bitmap_t;


bitmap_t* bitmap_init(size_t width, size_t height)
{
    bitmap_t* bitmap = calloc(1, sizeof(bitmap_t));
    bitmap->width = width;
    bitmap->height = height;
    bitmap->data = calloc(width * height, sizeof(u32));
    return bitmap;
}


void bitmap_free(bitmap_t* bitmap)
{
    free(bitmap->data);
    free(bitmap);
}


typedef struct {
    bool is_running;
    window_t* window;
    bitmap_t* pixel_buffer;
} game_state_t;


game_state_t* game_state_init()
{
    game_state_t* game_state = calloc(1, sizeof(game_state_t));
    game_state->is_running = true;
    size_t width = 320;
    size_t height = 240;
    SDL_Init(SDL_INIT_VIDEO);
    game_state->window = window_create("SPACE!");
    game_state->pixel_buffer = bitmap_init(width, height);

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

void game_process_events(game_state_t* game_state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {   
       if (event.type == SDL_QUIT)
       {
          game_state->is_running = false;
       } 
       else if (event.type == SDL_KEYDOWN)
       {
           if (event.key.keysym.sym == SDLK_q)
           {
               game_state->is_running = false;
           }
       }
    }
}


u32 random_color()
{
    u32 r = rand() & 0xF0000000;
    u32 g = rand() & 0x00F00000;
    u32 b = rand() & 0x0000F000;
    u8 a = 0x000000ff;
    return r | g | b | a;
}


void render_game(game_state_t* game_state)
{
    bitmap_t* pixels = game_state->pixel_buffer;
    const size_t width = pixels->width;
    const size_t height = pixels->height;
    for (size_t y = 0; y < height; ++y)
    {
        u32 c = random_color();
        for (size_t x = 0; x < width; ++x)
        {
            pixels->data[y * width + x] = c;
        }
    }
}


int main()
{   
    printf("SPACE!\n");

    game_state_t* game_state = game_state_init();

    while (game_state->is_running)
    {
        game_process_events(game_state);

        render_game(game_state);

        game_state_present(game_state);

        SDL_Delay(16);
    }

    game_state_destroy(game_state);
}
