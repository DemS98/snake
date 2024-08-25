/*
    Screen draw module
*/
#include <SDL3/SDL_render.h>
#include "../entity/food.h"

/* Inits resources needed for drawing the map objects */
void init_draw();

/* Draws the map */
void draw_map(SDL_Renderer *renderer);

/* Draws a food object */
void draw_object(SDL_Renderer *renderer, food object);

/* Draws the score */
void draw_score(SDL_Renderer *renderer, unsigned short score);

/* Draws a chronometer with minute precision */
void draw_time(SDL_Renderer *renderer, unsigned long time);

/* Destroys resources initialized by `init_draw()` */
void destroy_draw();