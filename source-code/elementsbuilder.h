#ifndef ELEMENTSBUILDER_H
#define ELEMENTSBUILDER_H

#include <gb/gb.h>
#include <stdint.h>
#include "global.h"


//SET 
void loadElementsForLevel(int level);
//MOVE BUTTON PLAYER
BYTE processPlayer(UINT16 scroll_x);
//TILES ELEMENT
void setTilesElement(ElementType *element);
//MOVE ELEMENT
void moveElement(ElementType *element);
//TILES PLAYER ARRANGEMENT
void moveTilePlayer();
//CREATE PLAYER
void setupPlayer();
//GET ELEMENT BY ID
ElementType *getElement(UINT8 index);


#endif