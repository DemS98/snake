#include <stdio.h>
#include <string.h>
#include "draw.h"
#include "../common/color.h"
#include "../common/screen.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"

TTF_Font *pixel = NULL;

void draw_map(SDL_Renderer *renderer) {
    // black background
    SDL_Color black;
    BLACK(black);

    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);

    SDL_RenderClear(renderer);

    // blue map
    SDL_Color light_blue;
    LIGHT_BLUE(light_blue);

    SDL_SetRenderDrawColor(renderer, light_blue.r, light_blue.g, light_blue.b, light_blue.a);

    SDL_FRect map;
    map.x = MAP_X;
    map.y = MAP_Y;
    map.w = MAP_WIDTH * PX_SIZE;
    map.h = MAP_HEIGHT * PX_SIZE;

    SDL_RenderFillRect(renderer, &map);
}

void draw_object(SDL_Renderer *renderer, food object) {
    const SDL_Color *color = get_food_color(object);

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    SDL_FRect obj = {.x = MAP_X + get_food_x(object) * PX_SIZE, .y = MAP_Y + get_food_y(object) * PX_SIZE, .w=PX_SIZE, .h=PX_SIZE};

    SDL_RenderFillRect(renderer, &obj);
}

void draw_score(SDL_Renderer *renderer, unsigned short score) {
    if (pixel == NULL) {
        TTF_Init();
        pixel = TTF_OpenFont("resources/NovaMono.ttf", FONT_SIZE);
    }

    SDL_Color white;
    WHITE(white);

    char str[20];
    snprintf(str, sizeof(str), "SCORE: %09d", score);

    SDL_Surface* surface_message = TTF_RenderText_Blended(pixel, str, white);

    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, surface_message);
    SDL_FRect container = {.x = MAP_X, .y = MAP_Y - FONT_SIZE - 10, .w = FONT_SIZE * strlen(str), .h = FONT_SIZE + 15};

    SDL_RenderTexture(renderer, score_texture, NULL, &container);

    SDL_DestroySurface(surface_message);
    SDL_DestroyTexture(score_texture);
}

void draw_time(SDL_Renderer *renderer, unsigned long time) {
    if (pixel == NULL) {
        TTF_Init();
        pixel = TTF_OpenFont("resources/NovaMono.ttf", FONT_SIZE);
    }

    SDL_Color white;
    WHITE(white);

    char str[20];
    
    snprintf(str, sizeof(str), "TIME: %02d:%02d", (int) time / 1000 / 60, (int) (time / 1000) % 60);

    SDL_Surface* surface_message = TTF_RenderText_Blended(pixel, str, white);
    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, surface_message);
    SDL_FRect container = {.x = MAP_X + (MAP_WIDTH * PX_SIZE) - (strlen(str) * FONT_SIZE), .y = MAP_Y - FONT_SIZE - 10, .w = FONT_SIZE * strlen(str), .h = FONT_SIZE + 15};
    
    SDL_RenderTexture(renderer, score_texture, NULL, &container);
    
    SDL_DestroySurface(surface_message);
    SDL_DestroyTexture(score_texture);
}