#ifndef ELEMENTSBUILDER_H
#define ELEMENTSBUILDER_H

#include <gb/gb.h>
#include <stdint.h>
#include "global.h"


//SET 
void setCollisionBoundaries(int level);
//MOVE BUTTON PLAYER
BYTE movePlayer(UINT16 scroll_x);
//TILES ELEMENT
void setTilesElement(ElementType *element);
//MOVE ELEMENT
void moveElement(ElementType *element);
//MOVE PLAYER
void moveTilePlayer();
//MOVE SHIP
void setupPlayer();
//GET ELEMENT BY ID
ElementType *getElement(UINT8 index);


#endif