#include "food.h"
#include <stdbool.h>

#define PLAYER_SPEED 50
#define PLAYER_START_SIZE 8
#define PLAYER_SCORE_GAIN 100


typedef struct _player *player;

typedef enum _movement {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
} movement;

bool is_dead(player player);

player spawn_player(unsigned short x, unsigned short y);

void destroy_player(player player);

bool move_player(player player, food food, movement direction);

const food player_object(player player, bool start);

unsigned short player_score(player player);

unsigned short player_size(player player);

void chop_player_head(player player);