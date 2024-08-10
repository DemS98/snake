#include "utils.h"
#include <stdlib.h>

unsigned short normalize(short num, unsigned short max) {
    if (num < 0) {
        return num + max;
    }

    return num % max;
}

int rand_range(int minimum_number, int max_number) {
    return rand() % (max_number + 1 - minimum_number) + minimum_number;
}