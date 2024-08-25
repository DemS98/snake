/*
    Sound module
*/

/*
    Initializes the sound engine.
    Should be called before playing any sound.
    To clear resources created by this function, `destroy_sound()` must be called.
 */
void init_sound();

/*
    Plays the snake eat sound.
*/
void play_eat_sound();

/*
    Plays the snake death sound.
 */
void play_death_sound();

/*
    Frees resources allocated by `init_sound()`
*/
void destroy_sound();