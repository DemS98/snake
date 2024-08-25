/*
    Utility functions module
*/

/*
    Resets `num` to:

    - `0` if `num == max`
    - `max` if `num == -1`

    Used to make a "portal" map on the edges.
*/
unsigned short normalize(short num, unsigned short max);

/* 
    Helper function to return a random integer between `minimum_number`
    and `maximum_number`
*/
int rand_range(int minimum_number, int max_number);