/*
    State module
*/

/* 
    Handy struct for storing the game state objects.
    Objects are saved in the `**objects` pointer array, with
    `size` set as the array size.
*/
typedef struct _state {
    void **objects;
    int size;
} state;