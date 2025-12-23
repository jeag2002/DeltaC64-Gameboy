
#include <gb/gb.h>
#include "global.h"
#include "level_1.h"


unsigned char *getLevelFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        return background_map_levelone;
    } else {
        return NULL;
    }
}