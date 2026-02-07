#ifndef ELEMENTSBUILDER_H
#define ELEMENTSBUILDER_H

#include <gb/gb.h>
#include <stdint.h>
#include "global.h"


//////////////////////////////////// ENEMIES /////////////////////////////////

//CREATE ENEMY IN THE ELEMENT COLLECTION
void createEnemyElement(int index, int pos_x_enemy, int pos_y_enemy, int stop,  int enemy, int type_enemy, int index_id, int frame_id) BANKED;

//SET ENEMIES DATA FROM WORLD CONFIGURATION TO LEVEL.
void processEnemiesLevel(UINT8 currentStopFrame) BANKED;

//CLEAN ENEMIES
void cleanElementData() BANKED;

//CLEAN ELEMENTS x STOP
void cleanEnemyDataByStop(UINT8 currentStopFrame) BANKED;

//MOVE ENEMIES
void moveEnemies() BANKED;


///////////////////////////////// BULLETS ////////////////////////////////////

//MOVE BULLETS, DETECT COLLISIONS
void moveBullets(INT16 scroll_x) BANKED;

//CREATE BULLET INTO ELEMENTS COLLECTION
void createShootInternal(UINT8 index, UINT16 x, UINT16 y, UINT8 width, INT16 scroll_x, INT8 inc,  UINT8 type, UINT8 type_shoot, UINT8 frame_id, UINT8 indexVRAM) BANKED;

//FIND ELEMENT BUCKET FREE FOR A NEW BULLET INTO ELEMENTS COLLECTION
void createShootElement(UINT16 x, UINT16 y, UINT8 width, INT16 scroll_x, INT8 inc, UINT8 type, UINT8 type_shoot) BANKED;

//CREATE BULLET
void createShoot(INT16 scroll_x) BANKED;

//DEFINE A DELAY BETWEEN BULLETS
void timeCreateShoot(INT16 scroll_x) BANKED;


///////////////////////// PLAYER /////////////////////////////////

//ACTION (MOVEMENT/SHOOT) PLAYER
UINT8 actionPlayer(INT16 scroll_x) BANKED;

//MOVE PLAYER + COLLISIONS
BYTE movePlayer(INT16 scroll_x) BANKED;

//CREATE PLAYER
void createPlayer() BANKED;

//BACK MOVEMENT
void rebootPlayer() BANKED;
/////////////////////// GENERAL TOOLS //////////////////////////////////

////////////////////////// COLLISIONS BETWEEN ELEMENTS //////////////////
//COLLIDE PLAYER VS ENEMIES/ENEMIES SHOOTS
BYTE collidePlayerVSElements() BANKED;

//COLLIDE ELEMENTS VS OTHERS
UINT8 collideElementVSOther(ElementType *element, UINT8 currentIndex) BANKED;

////////////////////////// SCROLLING ////////////////////////////////
//STOP SCROLLING
BYTE stopScrolling(INT16 scroll_x) BANKED;

///////////////////////// MANAGING TILES ///////////////////////////////
//MOVE TILES OF A FRAME OF AN ELEMENT
void setTilesElement(ElementType *element) BANKED;

//MOVE FRAME OF AN ELEMENT
void moveElement(ElementType *element) BANKED;

//MOVE FRAME->TILES OF A ELEMENT.
void moveTileElement(UINT8 index) BANKED;

//GET ELEMENT BY ID
ElementType *getElement(UINT8 index) BANKED;

//SET OTHER ELEMENTS INTO THE LEVEL.
void loadElementsForLevel(int level) BANKED;

//PROCESS BONUS TILES CHANGE SHOOT
//UINT8 processBonusTilesBackground(UINT8 tile, INT16 tile_x, INT16 tile_y);
UINT8 processBonusTilesBackground(UINT8 tile) BANKED;

////////////////////// CLEAN CONTEXT ///////////////////////////////
//SET EXPLOSIONS
void setExplosionData(UINT8 index) BANKED;

//PROCESS FINAL ANIMATIONS
void processFinalAnimations() BANKED;

//CLEAN ELEMENTTYPE
void deleteContent(ElementType *element) BANKED;

//CLEAN DATA OF VRAM
void deleteTiles(int index) BANKED;

//CLEAN ALL CONTENT OF A LEVEL
void deleteAllContent() BANKED;

//CLEAN PLAYER
void deletePlayerContent() BANKED;

#endif