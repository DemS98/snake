#include "../entity/food.h"
#include "SDL3/SDL_render.h"

void draw_map(SDL_Renderer *renderer);
void draw_object(SDL_Renderer *renderer, food object);
void draw_score(SDL_Renderer *renderer, unsigned short score);
void draw_time(SDL_Renderer *renderer, unsigned long time);