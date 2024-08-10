#include "player.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct _food_queue_node {
    food food;
    struct _food_queue_node* next;
};

struct _player {
    unsigned short score;
    unsigned short size;

    struct _food_queue_node *head;
    struct _food_queue_node *tail;
};

static void change_direction(food food, movement direction) {
    short delta_x = 0, delta_y = 0;

    switch (direction) {
        case TOP:
            delta_y = -1;
            break;
        case BOTTOM:
            delta_y = 1;
            break;
        case LEFT:
            delta_x = -1;
            break;
        case RIGHT:
            delta_x = 1;
            break;
    }

    move_food(food, get_food_x(food) + delta_x, get_food_y(food) + delta_y);
}

static bool eat_food(player player, food food, unsigned short x, unsigned short y) {
    if (player->head != NULL && !can_reach_food(food, get_food_x(player->head->food), get_food_y(player->head->food))) {
        return false;
    }

    struct _food_queue_node *node = malloc(sizeof(struct _food_queue_node));
        
    if (node == NULL) {
        return false;
    }

    node->food = food;
    node->next = NULL;

    if (player->head == NULL) {
        player->head = player->tail = node;
        player->size = 0;
        player->score = 0;
    } else {
        move_food(node->food, x, y);

        player->tail->next = node;
        player->tail = node;

        player->score += PLAYER_SCORE_GAIN;
    }

    player->size++;

    return true;
}

bool is_dead(player player) {
    food head = player->head->food;

    struct _food_queue_node *current = player->head->next;

    while (current != NULL) {
        if (can_reach_food(current->food, get_food_x(head), get_food_y(head))) {
            return true;
        }

        current = current->next;
    }

    return false;
}

player spawn_player(unsigned short x, unsigned short y) {
    player player = malloc(sizeof(struct _player));

    if (player == NULL) {
        return NULL;
    }

    for(int i=0; i<PLAYER_START_SIZE; i++) {
        food food = spawn_food(x, y);

        if (food == NULL || !eat_food(player, food, x-i, y)) {
            destroy_player(player);
            return NULL;
        }
    }

    player->score = 0;

    return player;
}

void destroy_player(player player) {
    struct _food_queue_node *current = player->head;

    while (current != NULL) {
        struct _food_queue_node *next = current->next;

        destroy_food(current->food);
        free(current);

        current = next;
    }

    free(player);
}

void chop_player_head(player player) {
    destroy_food(player->head->food);

    struct _food_queue_node *new_head = player->head->next;

    free(player->head);

    player->head = new_head;

    player->size--;
}

bool move_player(player player, food food, movement direction) {
    struct _food_queue_node *current = player->head->next;

    unsigned short last_x = get_food_x(player->head->food), last_y = get_food_y(player->head->food);
    unsigned short tail_x = get_food_x(player->tail->food), tail_y = get_food_y(player->tail->food);

    change_direction(player->head->food, direction);

    while (current != NULL) {
        unsigned short current_x = get_food_x(current->food), current_y = get_food_y(current->food);

        move_food(current->food, last_x, last_y);

        current = current->next;
        last_x = current_x;
        last_y = current_y;
    }

    return eat_food(player, food, tail_x, tail_y);
}

const food player_object(player player, bool start) {
    static const struct _food_queue_node *current = NULL;

    if (start) {
        current = player->head;
    }

    if (current == NULL) {
        return NULL;
    }

    const food food = current->food;

    current = current->next;

    return food;
}

unsigned short player_score(player player) {
    return player->score;
}

unsigned short player_size(player player) {
    return player->size;
}