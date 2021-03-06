#include <stdlib.h>
#include <string.h>
#include "entity.h"


void entity_init(entity_t* entity) {
    memset(entity, 0, sizeof(entity_t));
    entity->free_func = entity_free_func;
}

void entity_align_in_rect(entity_t* entity, recti_t rect, alignment_t x_align, alignment_t y_align)
{
    recti_t aligned_rect = recti_align(entity->bounding_box, rect, x_align, y_align);
    entity->pos = (vec2f_t) {aligned_rect.x1, aligned_rect.y1};
}

void entity_translate(entity_t* entity, vec2f_t translation) {
    vec2f_add(&entity->pos, translation);
}


void entity_free_func(entity_t* entity) {
    free(entity);
}
