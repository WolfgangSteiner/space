cmake_minimum_required(VERSION 3.18)

project(space)
include_directories(src)
add_compile_options(-Wall -Wextra -pedantic -Werror)


add_library(citrine STATIC 
    src/random.c
    src/range.c
    src/recti.c
    src/vec2f.c
    src/dynarr.c
    src/color.c 
    src/bitmap.c
    src/window.c
    src/game_state.c
)

set_property(TARGET citrine PROPERTY C_STANDARD 11)

add_executable(space src/main.c src/star_field.c)
target_link_libraries(space citrine SDL2 m)
set_property(TARGET space PROPERTY C_STANDARD 11)

