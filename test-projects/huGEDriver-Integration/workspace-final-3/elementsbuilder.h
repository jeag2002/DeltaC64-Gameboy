#ifndef ELEMENTSBUILDER_H
#define ELEMENTSBUILDER_H

#include <gb/gb.h>
#include <stdint.h>
#include "global.h"


//////////////////////////////////// ENEMIES /////////////////////////////////

//CREATE ENEMY IN THE ELEMENT COLLECTION
void createEnemyElement(int index, int pos_x_enemy, int pos_y_enemy, int stop,  int enemy, int type_enemy, int index_id, int frame_id);

//SET ENEMIES DATA FROM WORLD CONFIGURATION TO LEVEL.
void processEnemiesLevel(UINT8 currentStopFrame);

//CLEAN ENEMIES
void cleanElementData();

//CLEAN ELEMENTS x STOP
void cleanEnemyDataByStop(UINT8 currentStopFrame);

//MOVE ENEMIES
void moveEnemies();


///////////////////////////////// BULLETS ////////////////////////////////////

//MOVE BULLETS, DETECT COLLISIONS
void moveBullets(INT16 scroll_x);

//CREATE BULLET INTO ELEMENTS COLLECTION
void createShootInternal(UINT8 index, UINT16 x, UINT16 y, UINT8 width, INT16 scroll_x, INT8 inc,  UINT8 type, UINT8 type_shoot, UINT8 frame_id, UINT8 indexVRAM);

//FIND ELEMENT BUCKET FREE FOR A NEW BULLET INTO ELEMENTS COLLECTION
void createShootElement(UINT16 x, UINT16 y, UINT8 width, INT16 scroll_x, INT8 inc, UINT8 type, UINT8 type_shoot);

//CREATE BULLET
void createShoot(INT16 scroll_x);

//DEFINE A DELAY BETWEEN BULLETS
void timeCreateShoot(INT16 scroll_x);


///////////////////////// PLAYER /////////////////////////////////

//ACTION (MOVEMENT/SHOOT) PLAYER
UINT8 actionPlayer(INT16 scroll_x);

//MOVE PLAYER + COLLISIONS
BYTE movePlayer(INT16 scroll_x);

//CREATE PLAYER
void createPlayer();

//BACK MOVEMENT
void rebootPlayer();
/////////////////////// GENERAL TOOLS //////////////////////////////////

////////////////////////// COLLISIONS BETWEEN ELEMENTS //////////////////
//COLLIDE PLAYER VS ENEMIES/ENEMIES SHOOTS
BYTE collidePlayerVSElements();

//COLLIDE ELEMENTS VS OTHERS
UINT8 collideElementVSOther(ElementType *element, UINT8 currentIndex);

////////////////////////// SCROLLING ////////////////////////////////
//STOP SCROLLING
BYTE stopScrolling(INT16 scroll_x);

///////////////////////// MANAGING TILES ///////////////////////////////
//MOVE TILES OF A FRAME OF AN ELEMENT
void setTilesElement(ElementType *element);

//MOVE FRAME OF AN ELEMENT
void moveElement(ElementType *element);

//MOVE FRAME->TILES OF A ELEMENT.
void moveTileElement(UINT8 index);

//GET ELEMENT BY ID
ElementType *getElement(UINT8 index);

//SET OTHER ELEMENTS INTO THE LEVEL.
void loadElementsForLevel(int level);

//PROCESS BONUS TILES CHANGE SHOOT
//UINT8 processBonusTilesBackground(UINT8 tile, INT16 tile_x, INT16 tile_y);
UINT8 processBonusTilesBackground(UINT8 tile);

////////////////////// CLEAN CONTEXT ///////////////////////////////
//SET EXPLOSIONS
void setExplosionData(UINT8 index);

//PROCESS FINAL ANIMATIONS
void processFinalAnimations();

//CLEAN ELEMENTTYPE
void deleteContent(ElementType *element);

//CLEAN DATA OF VRAM
void deleteTiles(int index);

//CLEAN ALL CONTENT OF A LEVEL
void deleteAllContent();

//CLEAN PLAYER
void deletePlayerContent();

#endif