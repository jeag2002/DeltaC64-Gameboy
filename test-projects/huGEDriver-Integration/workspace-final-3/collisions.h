#include <gb/gb.h>
#include "global.h"

#ifndef COLLISIONS_H
#define COLLISIONS_H

//SET MAP TO COLLISION ENGINE
void setCollBoundaries(int level);

//IS A TILE COLLIDEABLE?
BYTE isCollideElement(UINT8 tile);

//DELETE BONUS TILES FROM BACKGROUND IF PLAYER COLLISIONED 
void processBackGroundTile (UINT8 TILE, UINT16 wx, UINT16 wy);

//DETECT TILE AT WORLD
CollisionData *getTileAtWorld(UINT16 world_x, UINT16 world_y, UINT8 type);

//COLLISION BETWEEN TWO ELEMENTS
UBYTE isCollisionB2B(UINT16 elem_1_x, UINT16 elem_1_y,
                     UINT16 elem_1_w, UINT16 elem_1_h,
                     UINT16 elem_2_x, UINT16 elem_2_y,
                     UINT16 elem_2_w, UINT16 elem_2_h);

//COLL WHEN DOWN
CollisionData *downCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 height);
//COLL WHEN UP
CollisionData *upCollisionEnv(UINT16 world_x, UINT16 world_y);
//COLL WHEN LEFT
CollisionData *leftCollisionEnv(UINT16 world_x, UINT16 world_y);
//COLL WHEN RIGHT
CollisionData *rightCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width);
//COLL WHEN NO MOVE
CollisionData *noMoveCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width);
//COLL WHEN NO MOVE (BULLET)
CollisionData *noMoveCollisionShoot(UINT16 world_x, UINT16 world_y, UINT16 width, UINT8 type);







#endif

