/*
 * Simple Snake game with SDL3 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>

#include "common/screen.h"
#include "common/state.h"
#include "common/utils.h"
#include "draw/draw.h"
#include "entity/player.h"
#include "entity/food.h"


/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// Timestamp of start tick
static unsigned long start_tick = 0;
static unsigned long start_score = 0;

static movement get_direction_from_keycode(const Uint8* keystates, movement current) {
    if(keystates[SDL_SCANCODE_UP] && current != TOP && current != BOTTOM) {
        return TOP;
    }

    if(keystates[SDL_SCANCODE_DOWN] && current != TOP && current != BOTTOM) {
        return BOTTOM;
    }
    
    if(keystates[SDL_SCANCODE_LEFT] && current != LEFT && current != RIGHT) {
        return LEFT;
    }
    
    if(keystates[SDL_SCANCODE_RIGHT] && current != LEFT && current != RIGHT) {
        return RIGHT;
    }

    return current;
}

static bool safe_to_spawn(player player, unsigned short x, unsigned short y) {
    food food = player_object(player, true);
    while (food != NULL) {
        if (can_reach_food(food, x, y)) {
            return false;
        }

        food = player_object(player, false);
    }

    return true;
}

static food spawn_food_random(player player) {
    const food head = player_object(player, true);

    // Try far away, reducing size after 5 tries
    for(unsigned short min_dist = 40; min_dist >= 0; min_dist -= 20) {
        for(int i=0; i<5; i++) {
            unsigned short x = normalize(get_food_x(head) + rand_range(min_dist, min_dist + 20), MAP_WIDTH);
            unsigned short y = normalize(get_food_y(head) + rand_range(min_dist, min_dist + 20), MAP_HEIGHT);

            if (safe_to_spawn(player, x, y)) {
                return spawn_food(x, y);
            }
        }
    }

    // Brute force it if too hard
    for(int i=0; i<MAP_WIDTH; i++) {
        for(int j=0;j<MAP_HEIGHT;j++) {
            if (safe_to_spawn(player, i, j)) {
                return spawn_food(i, j);
            }
        }
    }

    return NULL;
}

/* This function runs once at startup. */
int SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't initialize SDL!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer("SNAKE", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Couldn't create window/renderer!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    srand(time(NULL));

    int start_x = MAP_WIDTH / 2, start_y = MAP_HEIGHT / 2;

    player player = spawn_player(start_x, start_y);
    
    movement *movement = malloc(sizeof(movement));
    *movement = RIGHT;
    
    bool *dead = malloc(sizeof(bool));
    *dead = false;

    unsigned short *speed = malloc(sizeof(unsigned short));
    *speed = PLAYER_SPEED;

    unsigned short *score = malloc(sizeof(unsigned short));
    *score = player_score(player);

    state *state = malloc(sizeof(state));
    state->size = 6;
    state->objects = malloc(sizeof(void *) * state->size);

    state->objects[0] = player;
    state->objects[1] = movement;
    state->objects[2] = spawn_food_random(player);
    state->objects[3] = dead;
    state->objects[4] = speed;
    state->objects[5] = score;

    *appstate = state;

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

// TODO: use keyboard states
// https://stackoverflow.com/a/29382114/7363182

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
int SDL_AppEvent(void *appstate, const SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
int SDL_AppIterate(void *appstate)
{
    if (start_tick == 0) {
        start_tick = SDL_GetTicks();
    }

    if (start_score == 0) {
        start_score = SDL_GetTicks();
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    state *state = appstate;

    player player = state->objects[0];

    movement *direction = state->objects[1];
    food spawned = state->objects[2];
    bool *dead = state->objects[3];
    unsigned short *speed = state->objects[4];
    unsigned short *score = state->objects[5];

    if (SDL_GetTicks() - start_tick >= *speed) {
        *direction = get_direction_from_keycode(keystates, *direction);
        
        if(*dead) {
            chop_player_head(player);
        } else if(move_player(player, spawned, *direction)) {
            state->objects[2] = spawn_food_random(player);

            unsigned short eaten = player_size(player) - PLAYER_START_SIZE;
            if (eaten > 0 && eaten % 5 == 0 && *speed > 20) {
                *speed -= 2;
            }

        } else {
            *dead = is_dead(player);
        }

        start_tick = 0;
    }

    draw_map(renderer);

    food food = player_object(player, true);

    #ifdef DEBUG
    if (food != NULL) {
        printf("\e[1;1H\e[2J");
        printf("player -> x = %d, y = %d\n", get_food_x(food), get_food_y(food));
        printf("speed -> %d\n", *speed);
        printf("food -> x = %d, y = %d\n", get_food_x(spawned), get_food_y(spawned));
    }
    #endif

    while (food != NULL) {
        draw_object(renderer, food);
        food = player_object(player, false);
    }

    draw_object(renderer, spawned);

    if (*score < player_score(player) && SDL_GetTicks() - start_score >= SCORE_SPEED) {
        (*score)+=2;
        start_score = 0;
    }

    draw_score(renderer, *score);

    draw_time(renderer, SDL_GetTicks());

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    if (player_size(player) == 0) {
        SDL_Delay(250);
        return SDL_EVENT_QUIT;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate)
{
    state *state = appstate;

    /* SDL will clean up the window/renderer for us. */
    destroy_player(state->objects[0]);
    free(state->objects[1]);
    destroy_food(state->objects[2]);
    free(state->objects[3]);
    free(state->objects[4]);
    free(state->objects[5]);

    free(state->objects);
    free(state);
}

