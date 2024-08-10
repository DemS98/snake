#define RED(color) {color.r = 255; color.g = 0; color.b = 0; color.a = 255;}
#define LIGHT_BLUE(color) {color.r = 0; color.g = 128; color.b = 255; color.a = 255;}
#define GREEN(color) {color.r = 0; color.g = 255; color.b = 0; color.a = 255;}
#define BLACK(color) {color.r = 0; color.g = 0; color.b = 0; color.a = 255;}
#define WHITE(color) {color.r = 255; color.g = 255; color.b = 255; color.a = 255;}
#define ORANGE(color) {color.r = 255; color.g = 165; color.b = 0; color.a = 255;}
#define YELLOW(color) {color.r = 255; color.g = 255; color.b = 0; color.a = 255;}

#define pick_color(color, i) \
    switch(i) { \
        case 0: \
            RED(color); \
            break; \
        case 1: \
            GREEN(color); \
            break; \
        case 2: \
            WHITE(color); \
            break; \
        case 3: \
            ORANGE(color); \
            break; \
        case 4: \
            YELLOW(color); \
            break; \
        default: \
            break; \
    }
