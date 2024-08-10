#include "SDL3/SDL_pixels.h"
#include <stdbool.h>

typedef struct _object *food;

food spawn_food(unsigned short x, unsigned short y);

void destroy_food(food food);

bool can_reach_food(food food, unsigned short x, unsigned short y);

const SDL_Color *get_food_color(food food);

unsigned short get_food_x(food food);

unsigned short get_food_y(food food);

void move_food(food food, short x, short y);