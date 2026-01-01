
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
    //level_1.numstops = 2;
    level_1.numstops = 3;

    level_1.stops[0].stop = 327;
    level_1.stops[0].processed = FALSE;
    level_1.stops[0].processedEnemies = FALSE;
    level_1.stops[0].enemiesByStop.num_enemies = 4;
    level_1.stops[0].enemiesByStop.type_enemy = TYPE_ENEMY_OVNI;
    level_1.stops[0].enemiesByStop.num_frames = 4;
    level_1.stops[0].enemiesByStop.steps = NUMSTEPS;
    level_1.stops[0].enemiesByStop.behav_enemy = movementMountainUp;

    level_1.stops[1].stop = 327;
    level_1.stops[1].processed = FALSE;
    level_1.stops[1].processedEnemies = FALSE;
    level_1.stops[1].enemiesByStop.num_enemies = 4;
    level_1.stops[1].enemiesByStop.type_enemy = TYPE_ENEMY_PLANET;
    level_1.stops[1].enemiesByStop.num_frames = 4;
    level_1.stops[1].enemiesByStop.steps = NUMSTEPS;
    level_1.stops[1].enemiesByStop.behav_enemy = movementMountainDown;

    
    level_1.stops[2].stop = 800;
    level_1.stops[2].processed = FALSE;
    level_1.stops[2].processedEnemies = FALSE;
    level_1.stops[2].enemiesByStop.num_enemies = 4;
    level_1.stops[2].enemiesByStop.type_enemy = TYPE_ENEMY_SQUARE;
    level_1.stops[2].enemiesByStop.num_frames = 4;
    level_1.stops[2].enemiesByStop.steps = NUMSTEPS_1;
    level_1.stops[2].enemiesByStop.behav_enemy = movementUpRotationDown;
    


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

