#include <stdlib.h>
#include "food.h"
#include "../common/color.h"
#include "../common/screen.h"
#include "../common/utils.h"
#include "SDL3/SDL_pixels.h"

struct _object {
    unsigned short x;
    unsigned short y;
    SDL_Color color;
};

food spawn_food(unsigned short x, unsigned short y) {
    food food = malloc(sizeof(struct _object));

    if (food == NULL) {
        return NULL;
    }

    SDL_Color color;
    pick_color(color, rand() % 5);

    food->x = x;
    food->y = y;
    food->color = color;

    return food;
}

void destroy_food(food food) {
    if (food != NULL) {
        free(food);
    }
}

bool can_reach_food(food food, unsigned short x, unsigned short y) {
    return food->x == x && food->y == y;                               
}

const SDL_Color *get_food_color(food food) {
    return &food->color;
}

unsigned short get_food_x(food food) {
    return food->x;
}

unsigned short get_food_y(food food) {
    return food->y;
}

void move_food(food food, short x, short y) {
    // normalize on map width and height
    x = normalize(x, MAP_WIDTH);
    y = normalize(y, MAP_HEIGHT);

    food->x = x;
    food->y = y;
}