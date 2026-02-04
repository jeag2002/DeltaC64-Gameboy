
#include <gb/gb.h>
#include <string.h>
#include "global.h"
#include "level_1.h"
#include "level_1_tiles_2.h"
#include "Sprites.h"

#include "Movements.h"

#define MAP_W 160
#define MAP_H 20

#define TILE_W 8
#define TILE_H 246

#define SPRITE_W 8
#define SPRITE_H 184


static LevelType level_1;

unsigned char background_map_cpy[MAP_W * MAP_H];

unsigned char background_map_cpy_tiles[TILE_W * TILE_H];

unsigned char sprites_cpy[SPRITE_W * SPRITE_H];



//SET SPRITES FROM INDEX
unsigned char *getSpritesFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        UINT8 OLD = _current_bank;
        SWITCH_ROM(3);
        memcpy(sprites_cpy, sprites_videogame, SPRITE_W * SPRITE_H);
        SWITCH_ROM(OLD); 
        return sprites_cpy;
    } else {
        return NULL;
    }
}



//SET TILE_SET FROM INDEX
unsigned char *getLevelTilesFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        UINT8 OLD = _current_bank;
        SWITCH_ROM(5);
        memcpy(background_map_cpy_tiles, tile_background_map, TILE_W * TILE_H);
        SWITCH_ROM(OLD); 
        return background_map_cpy_tiles;
    } else {
        return NULL;
    }
}

//SET LEVEL FROM INDEX
unsigned char *getLevelFromIndex(int index) {
    if (index == LEVEL_1_INDEX) {
        UINT8 OLD = _current_bank;
        //BACKGROUND 
        //SWITCH_ROM(BANK(background_map_levelone));
        SWITCH_ROM(5);
        memcpy(background_map_cpy, background_map_levelone, MAP_W * MAP_H);
        SWITCH_ROM(OLD); 

        return background_map_cpy;
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

    
    level_1.stops[2].stop = 800;
    level_1.stops[2].processed = FALSE;
    level_1.stops[2].processedEnemies = FALSE;
    level_1.stops[2].enemiesByStop.num_enemies = 4;
    level_1.stops[2].enemiesByStop.type_enemy = TYPE_ENEMY_PLANET;
    level_1.stops[2].enemiesByStop.num_frames = 4;
    level_1.stops[2].enemiesByStop.steps = NUMSTEPS_1;
    level_1.stops[2].enemiesByStop.iniposx = ENEMY_POS_X_INI;
    level_1.stops[2].enemiesByStop.iniposy = ENEMY_POS_Y_INI;
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


