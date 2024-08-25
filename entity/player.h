#include <stdbool.h>
#include "food.h"

#define PLAYER_SPEED 50
#define PLAYER_MAX_SPEED 20
#define PLAYER_SPEED_GAIN_STEPS 5
#define PLAYER_KILL_SPEED 25
#define PLAYER_START_SIZE 8
#define PLAYER_SCORE_GAIN 100

/*
    Player object.
    A player is a queue of food, which grows when foods are eaten.
*/
typedef struct _player *player;

/* Keyboard player movements */
typedef enum _movement {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
} movement;

/* Checks if the player killed himself (yeah, this block snake is male 😁) */
bool is_dead(player player);

/* Creates the player at `(x,y)` coordinates */
player spawn_player(unsigned short x, unsigned short y);

/*
    Remove the player head, making the item next to it the new head.
    Used for the snake kill effect.
*/
void chop_player_head(player player);

/* Clears player resources */
void destroy_player(player player);

/*
    Moves the player in given `direction`, eating the given `food` if the
    player collides with it after the movement.
    Returns `true` if the player ate the food, `false` otherwise.
*/
bool move_player(player player, food food, movement direction);

/*
    Iterates over each food eaten by the player.
    If `start == true`, starts from the head.
    Each invocation returns the next eaten food until the end
    is reached (`NULL` returned).
*/
const food player_object(player player, bool start);

/* Returns the player score */
unsigned short player_score(player player);

/* Returns the number of foods which make the player */
unsigned short player_size(player player);