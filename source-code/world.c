
#include <gb/gb.h>
#include <string.h>
#include "global.h"
#include "level_1.h"
#include "Movements.h"

#define MAP_W 160
#define MAP_H 20

static LevelType level_1;

unsigned char background_map_cpy[MAP_W * MAP_H];

//SET LEVEL FROM INDEX
unsigned char *getLevelFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        memcpy(background_map_cpy, background_map_levelone, MAP_W * MAP_H); 
        return background_map_cpy;
    } else {
        return NULL;
    }
}

//SET ENEMIES LEVEL ONE
LevelType *buildLevelEnemiesLevelOne () {
    
    level_1.id = LEVEL_1_INDEX;
    //level_1.numstops = 2;
    level_1.numstops = 5;

    level_1.stops[0].stop = 327;
    level_1.stops[0].processed = FALSE;
    level_1.stops[0].processedEnemies = FALSE;
    level_1.stops[0].enemiesByStop.num_enemies = 4;
    level_1.stops[0].enemiesByStop.type_enemy = TYPE_ENEMY_OVNI;
    level_1.stops[0].enemiesByStop.num_frames = 4;
    level_1.stops[0].enemiesByStop.steps = NUMSTEPS;
    level_1.stops[0].enemiesByStop.iniposx = ENEMY_POS_X_INI;
    level_1.stops[0].enemiesByStop.iniposy = ENEMY_POS_Y_INI;
    level_1.stops[0].enemiesByStop.behav_enemy = movementMountainUp;

    level_1.stops[1].stop = 327;
    level_1.stops[1].processed = FALSE;
    level_1.stops[1].processedEnemies = FALSE;
    level_1.stops[1].enemiesByStop.num_enemies = 4;
    level_1.stops[1].enemiesByStop.type_enemy = TYPE_ENEMY_OVNI;
    level_1.stops[1].enemiesByStop.num_frames = 4;
    level_1.stops[1].enemiesByStop.steps = NUMSTEPS;
    level_1.stops[1].enemiesByStop.iniposx = ENEMY_POS_X_INI;
    level_1.stops[1].enemiesByStop.iniposy = ENEMY_POS_Y_INI;
    level_1.stops[1].enemiesByStop.behav_enemy = movementMountainDown;


    level_1.stops[2].stop = 327;
    level_1.stops[2].processed = FALSE;
    level_1.stops[2].processedEnemies = FALSE;
    level_1.stops[2].enemiesByStop.num_enemies = 4;
    level_1.stops[2].enemiesByStop.type_enemy = TYPE_ENEMY_STAR;
    level_1.stops[2].enemiesByStop.num_frames = 4;
    level_1.stops[2].enemiesByStop.steps = NUMSTEPS;
    level_1.stops[2].enemiesByStop.iniposx = ENEMY_POS_X_INI;
    level_1.stops[2].enemiesByStop.iniposy = ENEMY_POS_Y_INI;
    level_1.stops[2].enemiesByStop.behav_enemy = movementShawUp;

    level_1.stops[3].stop = 327;
    level_1.stops[3].processed = FALSE;
    level_1.stops[3].processedEnemies = FALSE;
    level_1.stops[3].enemiesByStop.num_enemies = 4;
    level_1.stops[3].enemiesByStop.type_enemy = TYPE_ENEMY_STAR;
    level_1.stops[3].enemiesByStop.num_frames = 4;
    level_1.stops[3].enemiesByStop.steps = NUMSTEPS;
    level_1.stops[3].enemiesByStop.iniposx = ENEMY_POS_X_INI;
    level_1.stops[3].enemiesByStop.iniposy = ENEMY_POS_Y_INI;
    level_1.stops[3].enemiesByStop.behav_enemy = movementShawDown;

    
    level_1.stops[4].stop = 800;
    level_1.stops[4].processed = FALSE;
    level_1.stops[4].processedEnemies = FALSE;
    level_1.stops[4].enemiesByStop.num_enemies = 4;
    level_1.stops[4].enemiesByStop.type_enemy = TYPE_ENEMY_PLANET;
    level_1.stops[4].enemiesByStop.num_frames = 4;
    level_1.stops[4].enemiesByStop.steps = NUMSTEPS_1;
    level_1.stops[4].enemiesByStop.iniposx = ENEMY_POS_X_INI;
    level_1.stops[4].enemiesByStop.iniposy = ENEMY_POS_Y_INI;
    level_1.stops[4].enemiesByStop.behav_enemy = movementUpRotationDown;
    


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


