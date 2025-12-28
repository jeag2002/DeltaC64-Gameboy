
#include <gb/gb.h>
#include "global.h"
#include "level_1.h"
#include "Movements.h"

static LevelType level_1;

//SET LEVEL FROM INDEX
unsigned char *getLevelFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        return background_map_levelone;
    } else {
        return NULL;
    }
}

//SET ENEMIES LEVEL ONE
LevelType *buildLevelEnemiesLevelOne () {
    
    level_1.id = LEVEL_1_INDEX;
    level_1.numstops = 1;
    level_1.stops[0].stop = 132;
    level_1.stops[0].groupEnemiesByStop = 1;
    level_1.stops[0].enemiesByStop[0].num_enemies = 4;
    level_1.stops[0].enemiesByStop[0].type_enemy = TYPE_ENEMY_PLANET;
    level_1.stops[0].enemiesByStop[0].num_frames = 4;
    level_1.stops[0].enemiesByStop[0].steps = NUMSTEPS;
    level_1.stops[0].enemiesByStop[0].behav_enemy = movementShawUp;
    return &level_1;
}


//SET ENEMIES FOR EVERY MAP
LevelType *buildLevelEnemiesFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        return buildLevelEnemiesLevelOne();
    } else {
        return NULL;
    }
}

