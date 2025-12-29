#ifndef ELEMENTSBUILDER_H
#define ELEMENTSBUILDER_H

#include <gb/gb.h>
#include <stdint.h>
#include "global.h"

//SET OTHER ELEMENTS INTO THE LEVEL.
void loadElementsForLevel(int level);

//SET ENEMIES INTO THE LEVEL.
void processEnemiesLevel();

//PLAYER ACTIONS (MOVE/SHOOT)
BYTE movePlayer(INT16 scroll_x);

//CLEAN ENEMIES
void cleanElementData();

//MOVE ENEMIES
void moveEnemies();

//COLLIDE PLAYER VS ENEMIES/ENEMIES SHOOTS
BYTE collideElements();



//STOP SCROLLING
BYTE stopScrolling(INT16 scroll_x);

//MOVE TILES OF A FRAME OF AN ELEMENT
void setTilesElement(ElementType *element);

//MOVE FRAME OF AN ELEMENT
void moveElement(ElementType *element);

//MOVE FRAME->TILES OF A ELEMENT.
void moveTileElement(UINT8 index);

//CREATE PLAYER
void setupPlayer();

//GET ELEMENT BY ID
ElementType *getElement(UINT8 index);


#endif