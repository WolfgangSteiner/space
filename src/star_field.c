#include <stdlib.h>
#include "star_field.h"
#include "game_state.h"
#include "color.h"
#include "base_defines.h"
#include "vec2i.h"
#include "random.h"
#include "math.h"


float clamp_value(float val, float min_val, float max_val)
{
    return MIN(MAX(val, min_val), max_val);
}

u8 clamp_color_component(float brightness, float factor)
{
    return (u8)clamp_value(255.0f * brightness * factor, 0.0f, 255.0f);
}


static void spawn_star(star_field_t* star_field, star_t* star, rangei_t y_range) {
    size_t width = rect_width(star_field->entity.bounding_box);
    star->pos.x = (float)(rand() % width);
    star->pos.y = rangei_random(y_range); 
    float distance_factor = 50.0f;
    float distance = randf_uniform_range(0.0f, 100.0f);
    float brightness = 1.0f * expf(-distance / distance_factor);
    float red_factor = randf_uniform_range(0.7f, 1.3f);
    float blue_factor = 1.0f / red_factor;
    star->color.r = clamp_color_component(brightness, red_factor);
    star->color.g = (u8)(255.0f * brightness);
    star->color.b = clamp_color_component(brightness, blue_factor);
    star->vel.y = rangef_random(star_field->velocity_range);
}


void star_field_update(entity_t* entity, game_state_t* game_state) {
    star_field_t* star_field = (star_field_t*)entity;
    size_t height = game_state->pixel_buffer->height;
    float delta_t = game_state->delta_t;

    for (size_t i = 0; i < star_field->num_stars; ++i) {
        star_t* star = &star_field->stars[i];
        vec2f_smula(&star->pos, star->vel, delta_t);

        if (star->pos.y > height - 1) spawn_star(star_field, star, rangei(0, 0));
    } 
}


void draw_star(star_t* star, game_state_t* game_state) {
    int px = ROUND_TO_INT(star->pos.x);
    int py = ROUND_TO_INT(star->pos.y);
    bitmap_set_pixel(game_state->pixel_buffer, vec2i(px,py), star->color);  
}

void star_field_draw(entity_t* entity, game_state_t* game_state) {
    star_field_t* star_field = (star_field_t*)entity;
    for (size_t i = 0; i < star_field->num_stars; ++i) {
        draw_star(&star_field->stars[i], game_state);
    }
}


star_field_t* star_field_new(
    recti_t bounding_box,
    size_t num_stars,
    rangef_t velocity_range,
    range_u32_t color_range) {
    star_field_t* star_field = calloc(1, sizeof(star_field_t));
    star_field->stars = calloc(num_stars, sizeof(star_t));
    star_field->num_stars = num_stars;
    star_field->velocity_range = velocity_range;
    star_field->color_range = color_range;
    entity_init(&star_field->entity);
    star_field->entity.bounding_box = bounding_box;
    star_field->entity.update_func = star_field_update;
    star_field->entity.draw_func = star_field_draw;
    for (size_t i = 0; i < num_stars; ++i)
    {
        star_t* star = &star_field->stars[i];
        spawn_star(star_field, star, rangei(0, bounding_box.y2 - 1));
    }

    return star_field;
}
