/**
 * @file world.h
 * @author your name (you@domain.com)
 * @brief storage of the different levels of the game 
 */

#include <gb/gb.h>

#ifndef WORLD_H
#define WORLD_H

#define NUMLEVELS 5

struct Level {
    UINT8 id;
};

typedef struct Level LevelType;
extern LevelType levels[NUMLEVELS];

unsigned char *getLevelFromIndex(int index);
#endif