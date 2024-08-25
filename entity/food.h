/*
    Food object module
 */

#include "SDL3/SDL_pixels.h"
#include <stdbool.h>

/* Food object */
typedef struct _object *food;

/*
    Creates a food object at the given coordinates.
*/
food spawn_food(unsigned short x, unsigned short y);

/*
    Clears food resources
 */
void destroy_food(food food);

/*
    Returns `true` if the object at coordinates `(x,y)` collides with
    the given food
*/
bool food_collision(food food, unsigned short x, unsigned short y);

/* Get the food color */
const SDL_Color *get_food_color(food food);

/* Get the food `x` position */
unsigned short get_food_x(food food);

/* Get the food `y` position */
unsigned short get_food_y(food food);

/* Move the food at the given `(x,y)` coordinates */
void move_food(food food, short x, short y);