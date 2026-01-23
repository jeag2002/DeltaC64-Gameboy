/**
 * @file world.h
 * @author your name (you@domain.com)
 * @brief storage of the different levels of the game 
 */

#include <gb/gb.h>
#include "global.h"

#ifndef WORLD_H
#define WORLD_H

LevelType *buildLevelEnemiesFromIndex(int index);
unsigned char *getLevelFromIndex(int index);
#endif